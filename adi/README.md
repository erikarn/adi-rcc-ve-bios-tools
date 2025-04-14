These are the ADI Engineering BIOS images, found in release 01.00.00.17
from https://github.com/ADIEngineering/adi_coreboot_public .

The SG-2220 is a DFF2 board and uses the DFF2 image.
The SG-4860 is an RCC-VE board and uses the RCCVE image.

Note these are the raw BIOS images, they lack two specific things
you need to make a fully working setup:

 * The "OEM" section for the serial number (eg in dmidecode); and
 * The five MRCD sections you need to ensure functionality like ACPI
   reboot works!
