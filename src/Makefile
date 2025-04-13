
default: all

CFLAGS=	-O -Wall -Werror

all: assemble-sections extract-sections oem-serial

assemble-sections: assemble-sections.o

extract-sections: extract-sections.o

oem-serial: oem-serial.o

clean:
	rm -f assemble-sections
	rm -f extract-sections
	rm -f oem-serial
	rm -f *.o
