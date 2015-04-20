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
LDPATH = -L$(DRIVERDIR) -L$(UTILSDIR) -L$(TARGETDIR)/$(SERIEDIR)
LIBS = -Wl,--start-group -lgcc -lc -l$(TARGET)_sram -ldrivers-$(TARGET)_sram -lutils-$(TARGET)_sram -Wl,--end-group

#-------------------------------------------------------------------------------
#		Files
#-------------------------------------------------------------------------------

BUILDDIR_SRAM = $(MAKEFILEDIR)/build/$(TARGET)/sram
BUILDDIR_DDRAM = $(MAKEFILEDIR)/build/$(TARGET)/ddram
OBJECTS += main.o

#-------------------------------------------------------------------------------
#		Rules
#-------------------------------------------------------------------------------

$(BUILDDIR_SRAM) $(BUILDDIR_DDRAM):
	mkdir -p $@

$(addprefix $(BUILDDIR_SRAM)/,$(OBJECTS)): $(BUILDDIR_SRAM)/%.o: %.c
	$(CC) $(CFLAGS) $(call optimization,$(sram)) -c $< -o $@

$(addprefix $(BUILDDIR_DDRAM)/,$(OBJECTS)): $(BUILDDIR_DDRAM)/%.o: %.c
	$(CC) $(CFLAGS) $(call optimization,$(sram)) -c $< -o $@

getting-started-$(TARGET)_sram: $(addprefix $(BUILDDIR_SRAM)/,$(OBJECTS))
	$(CC) $(LDPATH) $(LDFLAGS) $(LD_OPTIONAL) -T"$(RESOURCEDIR)/$(TARGET)_sram.ld" -Wl,-Map,$(BUILDDIR_SRAM)/$@.map -o $(BUILDDIR_SRAM)/$@.elf $^ $(LIBS)
	$(NM) $(BUILDDIR_SRAM)/$@.elf >$(BUILDDIR_SRAM)/$@.elf.txt
	$(OBJCOPY) -O binary $(BUILDDIR_SRAM)/$@.elf $(BUILDDIR_SRAM)/$@.bin
	$(SIZE) $^ $(BUILDDIR_SRAM)/$@.elf

getting-started-$(TARGET)_ddram: $(addprefix $(BUILDDIR_SRAM)/,$(OBJECTS))
	$(CC) $(LDPATH) $(LDFLAGS) $(LD_OPTIONAL) -T"$(RESOURCEDIR)/$(TARGET)_ddram.ld" -Wl,-Map,$(BUILDDIR_SRAM)/$@.map -o $(BUILDDIR_SRAM)/$@.elf $^ $(LIBS)
	$(NM) $(BUILDDIR_SRAM)/$@.elf >$(BUILDDIR_SRAM)/$@.elf.txt
	$(OBJCOPY) -O binary $(BUILDDIR_SRAM)/$@.elf $(BUILDDIR_SRAM)/$@.bin
	$(SIZE) $^ $(BUILDDIR_SRAM)/$@.elf

debug_sram: getting-started-$(TARGET)_sram
	$(GDB) -x "$(RESOURCEDIR)/$(TARGET)_sram.gdb" -ex "reset" -readnow -se $(BUILDDIR_SRAM)/getting-started-$(TARGET)_sram.elf

all: $(BUILDDIR_SRAM) $(BUILDDIR_DDRAM) getting-started-$(TARGET)_ddram getting-started-$(TARGET)_sram

clean:
	-rm -rf build
