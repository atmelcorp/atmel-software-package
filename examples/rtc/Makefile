# ----------------------------------------------------------------------------
#         SAM Software Package License
# ----------------------------------------------------------------------------
# Copyright (c) 2013, Atmel Corporation
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# - Redistributions of source code must retain the above copyright notice,
# this list of conditions and the disclaimer below.
#
# Atmel's name may not be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
# OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ----------------------------------------------------------------------------

#   Makefile for compiling the Getting Started with sama5d4x Microcontrollers project

MAKEFILEDIR := $(dir $(lastword $(MAKEFILE_LIST)))
include $(MAKEFILEDIR)/../../Makefile.inc

VPATH = $(MAKEFILEDIR)

#-------------------------------------------------------------------------------
#        User-modifiable options
#-------------------------------------------------------------------------------

# Defines which are the available memory targets for the sama5d4x-XULT board.

# Trace level used for compilation
# (can be overriden by adding TRACE_LEVEL=#number to the command-line)
# TRACE_LEVEL_DEBUG      5
# TRACE_LEVEL_INFO       4
# TRACE_LEVEL_WARNING    3
# TRACE_LEVEL_ERROR      2
# TRACE_LEVEL_FATAL      1
# TRACE_LEVEL_NO_TRACE   0
TRACE_LEVEL = 4

#-------------------------------------------------------------------------------
#		Tools
#-------------------------------------------------------------------------------

# Flags
INCLUDES = $(INCLUDE_TARGET) $(INCLUDE_UTILS) $(INCLUDE_DRIVER) $(INCLUDE_ROOTDIR) $(INCLUDE_LIB)
CFLAGS += $(INCLUDES) -DTRACE_LEVEL=$(TRACE_LEVEL)
LD_OPTIONAL = #-Wl,--print-gc-sections -Wl,--stats
LDPATH = -L$(DRIVERDIR) -L$(UTILSDIR) -L$(TARGETDIR)/$(SERIEDIRNAME)
LINKS = -Wl,--start-group -lgcc -lc -l$(TARGET)_sram -ldrivers-$(TARGET)_sram -lutils-$(TARGET)_sram -Wl,--end-group
LINKS_SRAM = -Wl,--start-group -lgcc -lc -l$(TARGET)_sram -ldrivers-$(TARGET)_sram -lutils-$(TARGET)_sram -Wl,--end-group
LINKS_DDRAM = -Wl,--start-group -lgcc -lc -l$(TARGET)_ddram -ldrivers-$(TARGET)_ddram -lutils-$(TARGET)_ddram -Wl,--end-group


#-------------------------------------------------------------------------------
#		Files
#-------------------------------------------------------------------------------

BUILDDIR_SRAM = $(MAKEFILEDIR)/build/$(TARGET)/sram
BUILDDIR_DDRAM = $(MAKEFILEDIR)/build/$(TARGET)/ddram
OBJECTS += main.o

OBJECTS_SRAM = $(addprefix $(BUILDDIR_SRAM)/,$(OBJECTS))
OBJECTS_DDRAM = $(addprefix $(BUILDDIR_DDRAM)/,$(OBJECTS))

LIBS = $(UTILSDIR)/*.a $(TARGETDIR)/$(SERIEDIRNAME)/*.a $(DRIVERDIR)/*.a

#-------------------------------------------------------------------------------
#		Rules
#-------------------------------------------------------------------------------
.PHONY: clean size_sram debug_sram

all: $(BUILDDIR_SRAM) $(BUILDDIR_DDRAM) $(LIBS) build_sram build_ddram

build_sram: $(BUILDDIR_SRAM)/rtc.elf \
	$(BUILDDIR_SRAM)/rtc.symbols \
	$(BUILDDIR_SRAM)/rtc.bin

build_ddram: $(BUILDDIR_DDRAM)/rtc.elf \
	$(BUILDDIR_DDRAM)/rtc.symbols  \
	$(BUILDDIR_DDRAM)/rtc.bin

$(BUILDDIR_SRAM) $(BUILDDIR_DDRAM):
	mkdir -p $@

$(OBJECTS_SRAM): $(BUILDDIR_SRAM)/%.o: %.c
	$(CC) $(CFLAGS) $(call optimization,$(sram)) -c $< -o $@

$(OBJECTS_DDRAM): $(BUILDDIR_DDRAM)/%.o: %.c
	$(CC) $(CFLAGS) $(call optimization,$(ddram)) -c $< -o $@

$(BUILDDIR_SRAM)/rtc.elf: $(OBJECTS_SRAM)
	$(CC) $(LDPATH) $(LDFLAGS) $(LD_OPTIONAL) -T"$(RESOURCEDIR)/$(TARGET)_sram.ld" -Wl,-Map,$(BUILDDIR_SRAM)/exportmap.map -o $@ $^ $(LINKS_SRAM)

$(BUILDDIR_SRAM)/rtc.elf: $(LIBS)

$(BUILDDIR_SRAM)/rtc.symbols: $(BUILDDIR_SRAM)/rtc.elf
	$(NM) $< >$@

$(BUILDDIR_SRAM)/rtc.bin: $(BUILDDIR_SRAM)/rtc.elf
	$(OBJCOPY) -O binary $< $@

$(BUILDDIR_DDRAM)/rtc.elf: $(OBJECTS_DDRAM)
	$(CC) $(LDPATH) $(LDFLAGS) $(LD_OPTIONAL) -T"$(RESOURCEDIR)/$(TARGET)_ddram.ld" -Wl,-Map,$(BUILDDIR_SRAM)/exportmap.map -o $@ $^ $(LINKS_DDRAM)

$(BUILDDIR_DDRAM)/rtc.elf: $(LIBS)

$(BUILDDIR_DDRAM)/rtc.symbols: $(BUILDDIR_DDRAM)/rtc.elf
	$(NM) $< >$@

$(BUILDDIR_DDRAM)/rtc.bin: $(BUILDDIR_DDRAM)/rtc.elf
	$(OBJCOPY) -O binary $< $@

$(LIBS):
	$(MAKE) -f $(@D)/Makefile

clean:
	-rm -rf $(MAKEFILEDIR)/build

size_sram:
	$(SIZE) $(OBJECTS_SRAM) $(BUILDDIR_SRAM)/rtc.elf

size_ddram:
	$(SIZE) $(OBJECTS_DDRAM) $(BUILDDIR_DDRAM)/rtc.elf

debug_sram: $(BUILDDIR_SRAM)/rtc.elf
	$(GDB) -x "$(RESOURCEDIR)/$(TARGET)_sram.gdb" -ex "reset" -readnow -se $(BUILDDIR_SRAM)/rtc.elf
