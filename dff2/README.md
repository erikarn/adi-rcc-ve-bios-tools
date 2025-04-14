This is a dump from a netgate SG-2220.

 * bios-vendor.bin - a dump of the BIOS from the SG-2220
 * ADI_DFF2-01.00.00.06-nodebug.rom - the vendor supplied version matching
   (hopefully!) what's in bios-vendor.bin
 * acpidump.txt - ACPI dump from the SG-2220 running bios-vendor.bin
 * dmidecode.txt - dmidecode

Dump differences:

 * 0x00000f00 -> 0x00000fff - OEM range, with the serial number
 * 0x00750000 -> 0x007522af - MRCD in bios-vendor.bin, 0xff in the vendor image
 * 0x00753000 -> 0x007552af - MRCD in bios-vendor.bin, 0xff in the vendor image
 * 0x00756000 -> 0x007582af - MRCD in bios-vendor.bin, 0xff in the vendor image
 * 0x00759000 -> 0x0075b2af - MRCD in bios-vendor.bin, 0xff in the vendor image
 * 0x0075c000 -> 0x0075e2af - MRCD in bios-vendor.bin, 0xff in the vendor image

 * (next section starts at 0x76000000), and is the microcode, don't break this!
