
* ADI_DFF2-01.00.00.17-nodebug.bin - the ADI provided BIOS image for the DFF2 platform
* ADI_RCCVE-01.00.00.17-nodebug.bin - the ADI provided BIOS image for the RCCVE platform
* bios-wifi-test1.bin - a BIOS image from a Netgate SG-4860 RCCVE platform; the bulk matching ADI_RCCVE-01.00.00.17-nodebug.bin

The flash layout, so far:

* 0x00000000 -> 0x000000ff: unknown
* 0x00000000 -> 0x00000eff: unknown
* 0x00000f00 -> 0x00000fff: oem range
* 0x00001000 -> 0x003fffff: 0xff padding
* 0x00400000 -> ? : LARCHIVE, cmos_layout.bin
* 0x00400580 -> ? : LARCHIVE, fallback_romstage
* 0x00401EC8 -> ? : LARCHIVE, CBFS
* 0x00402BCD -> ? : LARCHIVE, ?
* 0x00407640 -> ? : LARCHIVE, pci8086,1f41.rom
* 0x00418C80 -> ? : LARCHIVE, fallback/ramstage
* 0x00428440 -> ? : LARCHIVE, fallback/payload
* 0x00431AC0 -> ? : LARCHIVE, config
* 0x00432ED0 -> ? : LARCHIVE, vgaroms/Mohon
* 0x00433F00 -> ? : LARCHIVE, img/setup
* 0x00440100 -> ? : LARCHIVE, bootorder_map
... more to do
* 0x0075E2B0 -> 0x0075FFFF : all 0xFF's in both, likely unprogrammed / padding
* 0x76000000 -> end : a section starting with LARCHIVE, cpu_microcode_blob.bin ?

The range differences:

* 0x00000F00 -> 0x00000FFF : a 256 byte "OEM" partition, where the unit serial number is.
* 0x00750000 -> 0x007522AF : 0xFF in the vendor image, a section starting with MRCD on the RCCVE platform.
* 0x00753000 -> 0x007552AF : 0xFF in the vendor image, a section starting with MRCD on the RCCVE platform.
* 0x00756000 -> 0x007582AF : same as above
* 0x00759000 -> 0x0075B2AF : smae as above
* 0x0075C000 -> 0x0075E2AF : same as above
