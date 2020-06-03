PROJECT		= micro-sci
DEVICE		= atmega328p
CLOCK		= 8000000UL
PROGRAMMER	= usbasp
FUSES		= -Uhfuse:w:0b11011001:m -Ulfuse:w:0b11100010‬:m -Uefuse:w:0b11111101:m

SOURCEDIR 	= src
BUILDDIR 	= build
LIBDIR		= lib
SOURCES 	= ${wildcard ${SOURCEDIR}/*.cpp}
OBJECTS 	= ${patsubst ${SOURCEDIR}/%.cpp,${BUILDDIR}/%.o,${SOURCES}}
LIBS		= ${wildcard ${LIBDIR}/*.a}

CXX			= avr-gcc
OBJCOPY		= avr-objcopy
CXXFLAGS 	= -Os -DF_CPU=${CLOCK} -mmcu=${DEVICE} -std=c++2a -Wall -Wextra -pedantic -Wno-volatile

.PHONY: all docs keypad clean

all: ${BUILDDIR}/${PROJECT}.hex
	avr-size ${BUILDDIR}/${PROJECT}.elf

${OBJECTS}: $(BUILDDIR)/%.o: ${SOURCEDIR}/%.cpp
	${CXX} ${CXXFLAGS} -c $^ -o $@

${BUILDDIR}/${PROJECT}.elf: ${OBJECTS}
	${CXX} ${CXXFLAGS} -mrelax -o $@ $^ ${LIBS}

${BUILDDIR}/${PROJECT}.hex: ${BUILDDIR}/${PROJECT}.elf	
	${OBJCOPY} -j .text -j .data -O ihex $< $@

fuses:
	avrdude -c${PROGRAMMER} -p${DEVICE} ${FUSES}

flash: all
	avrdude -c${PROGRAMMER} -p${DEVICE} -Uflash:w:${BUILDDIR}/${PROJECT}.hex:i

erase:
	avrdude -c${PROGRAMMER} -p${DEVICE} -e

docs:
	@doxygen
	@start docs/index.html

keypad:
	@py tools/generate_keypad.py
	@start tools/keypad.pdf

clean:
	rm -f $(BUILDDIR)/*
	