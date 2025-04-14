Overview
--------

These are a collection of notes documenting the ADI DFF2 and RCC-VE boards
used in ~ 2018 era Netgate pfsense routers.

The two models I'm currently using this with are:

 * SG-4860 (RCC-VE)
 * SG-2220 (DFF2)

They are both Intel Atom C2xxx based platforms and they suffer from the
Intel Atom C2000 series hardware bugs that lead to a non-functioning
platform.

ADI Engineering put their BIOSes online at
https://github.com/ADIEngineering/adi_coreboot_public , the latest being
Version 01.00.00.17. These images fix both interrupt routing issues
on the miniPCIe slots as well as workarounds for the Intel Atom C2000
errata.

If you have DFF2 / RCC-VE boards then you should flash the latest BIOS.

The problem?  Well, what's the latest BIOS, and how do you flash it.

The ADI BIOS Images
-------------------

The ADI BIOS images contain debug and nodebug images for both platforms.
If they're flashed directly then things SEEM to work, however you'll find
two problems:

 * The OEM serial number is not set (eg via dmidecode); and
 * Weird behaviour happens, like "reboot" just powers the unit down.

After doing some binary comparisons between what ADI provided and what
Netgate shipped on their boards, it's very obvious where the two bits
are:

 * There's a 256 byte OEM section with the serial number; and
 * There are five 12288 byte sections with an "MRCD" header.

If those sections are copied into the ADI BIOS images, then everything
works just fine.

Flashing via flashrom
---------------------

Flashing a full 8 megabyte image via flashrom is pretty easy:

```
# flashrom -p internal -w bios.bin
```

However, more recent flashroms will end up finding more than one flash
chip.  I choose the first one and use -c 'flash identifier string' that
it provides to flash.

Reading the image too is easy:

```
# flashrom -p internal -r bios.bin
```

Again, you may need to use -c 'flash identifer string' to choose which
chip identifer to flash.

Disassembling and reassembling the images
-----------------------------------------

I've written some simple tools in src/ . Just do:

```
$ cd src
$ make
```

There are three tools:

 * extract-sections <input file> <prefix> - read the <input file>, output each section prefixed with <prefix>
 * assemble-sections <prefix> <output file> - read the set of bios sections, prefixed with <prefix>, and write <output file>
 * oem-serial <output file> <serial number> - write an OEM section file with the given 10 digit serial number.

Doing the image manipulation right now is intentionally tricky.
Yes the tools could be wrapped into a single tool - and I will do it if
asked! - but right now I'm focusing on just getting the pieces documented
and working.

What you should do:

 * read the file using flashrom -r, put it in a directory called "oem"
 * use extract-sections in the "oem" directory, populating all the sections
 * copy the right BIOS file from the adi/ directory into a new directory
   called "bios"
 * use extract-sections in the "bios" directory, populating all the sections
 * copy the five "mrcd" sections from the "oem" directory into the "adi"
   directory, replacing the five that you just creatd
 * use oem-serial to overwrite the oem file in the "oem" directory
   with your serial number
 * use assemble-sections in the "oem" directory to reassemble a new bios
   binary file
 * use flashrom -w to write the replacement BIOS
 * Use 'shutdown -p now' to shutdown
 * Power cycle the device

Assuming it all worked!

 * Use "dmidecode" to check the BIOS version string and OEM serial number
 * Use "reboot" to make sure the MRCD sections are populated correctly!


