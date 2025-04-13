#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>

struct fw_section_entry {
	uint32_t start;
	uint32_t end;
	const char *label;
};

/*
 * Firmware sections, based on binary diffs between ADI supplied
 * vendor BIOSes and OEM versions on shipping hardware.
 *
 * The "oem" section contains a single 10 digit serial number,
 * NUL terminated, and NUL/0 padded until the end.
 *
 * The bios section and microcode sections both contain sections
 * broken up with an LARCHIVE header.  For the purposes of this
 * tool however, parsing / enumerating those are not needed.
 * Both the RCCVE and DFF2 BIOS images use the same flash layout.
 */
static struct fw_section_entry fw_sections[] = {
	{ 0x00000000, 0x00000eff, "header" },
	{ 0x00000f00, 0x00000fff, "oem" },
	{ 0x00000100, 0x0074ffff, "bios" },
	{ 0x00750000, 0x00752fff, "mrcd_1" },
	{ 0x00753000, 0x00755fff, "mrcd_2" },
	{ 0x00756000, 0x00758fff, "mrcd_3" },
	{ 0x00759000, 0x0075bfff, "mrcd_4" },
	{ 0x0075c000, 0x0075ffff, "mrcd_5" },
	{ 0x00760000, 0x007fffff, "microcode" },
	{ 0, 0, NULL },
};

static int
extract_section(struct fw_section_entry *fw, const char *pfx, int file_fd)
{
	int fd;
	char str[128] = { 0, };
	uint32_t len;
	off_t oret;
	ssize_t sret;
	char *buf;

	snprintf(str, sizeof(str) - 1, "%s.%s", pfx, fw->label);
	fd = open(str, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		err(1, "open (%s)", str);

	len = fw->end - fw->start + 1;

	printf("  extracting 0x%08x -> 0x%08x (%d bytes) to %s\n",
	    fw->start, fw->end, len, str);

	oret = lseek(file_fd, fw->start, SEEK_SET);
	if (oret < 0)
		err(1, "seek to %u", fw->start);

	buf = calloc(1, len);
	if (buf == NULL)
		err(1, "calloc (%d bytes)", len);

	sret = read(file_fd, buf, len);
	if (sret < 0)
		err(1, "read (%d bytes)", len);
	if (sret != len)
		err(1, "read (%d bytes) (expected %d bytes)",
		    (uint32_t) sret, len);

	sret = write(fd, buf, len);
	if (sret < 0)
		err(1, "write (%d bytes)", len);
	if (sret != len)
		err(1, "write (%d bytes) (expected %d bytes)",
		    (uint32_t) sret, len);

	close(fd);
	free(buf);
	return (0);
}

int
main(int argc, const char *argv[])
{
	const char *fn;
	const char *fo;
	int fd;

	if (argc < 3) {
		printf("usage: %s <input file> <output file prefix>\n",
		    argv[0]);
		exit(127);
	}
	fn = argv[1];
	fo = argv[2];

	fd = open(fn, O_RDONLY);
	if (fd < 0)
		err(1, "open (%s)", fn);

	for (int i = 0; fw_sections[i].label != NULL; i++) {
		extract_section(&fw_sections[i], fo, fd);
	}

	close(fd);
	exit(0);

}
