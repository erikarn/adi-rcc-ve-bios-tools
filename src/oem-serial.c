#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>

/*
 * TODO: when fw_sections from the other source files is
 * broken out, use that as the OEM section size.
 */

#define	OEM_SECTION_SIZE	256

int
main(int argc, const char *argv[])
{
	const char *fn;
	const char *sn;
	ssize_t sret;
	int fd;
	char buf[OEM_SECTION_SIZE] = { 0, };

	if (argc < 3) {
		printf("usage: %s <output file> <serial number>\n",
		    argv[0]);
		exit(127);
	}
	fn = argv[1];
	sn = argv[2];

	fd = open(fn, O_WRONLY | O_CREAT, 0644);
	if (fd < 0)
		err(1, "open (%s)", fn);

	snprintf(buf, OEM_SECTION_SIZE - 1, "%s", sn);
	sret = write(fd, buf, OEM_SECTION_SIZE);
	if (sret < 0)
		err(1, "write (%s)", fn);
	else if (sret != OEM_SECTION_SIZE)
		err(1, "write (%s) size mismatch (%u != %u)",
		    fn, (unsigned int) sret, (unsigned int) OEM_SECTION_SIZE);

	close(fd);
	exit(0);

}
