#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

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
	0x00000000, 0x00000eff, "header",
	0x00000f00, 0x00000fff, "oem",
	0x00000100, 0x0074ffff, "bios",
	0x00750000, 0x00752fff, "mrcd_1",
	0x00753000, 0x00755fff, "mrcd_2",
	0x00756000, 0x00758fff, "mrcd_3",
	0x00759000, 0x0075bfff, "mrcd_4",
	0x0075c000, 0x0075ffff, "mrcd_5",
	0x00760000, 0x007fffff, "microcode",
};

int
main(int argc, const char *argv[])
{
	exit(0);
}
