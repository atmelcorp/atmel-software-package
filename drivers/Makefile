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

# Include common variables
MAKEFILEDIR := $(dir $(lastword $(MAKEFILE_LIST)))
include $(MAKEFILEDIR)/../Makefile.inc

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
# Output directories
DRIVERSUBDIRS = av bus core crypto io net serial time mem

#-------------------------------------------------------------------------------
#		Tools
#-------------------------------------------------------------------------------
INCLUDES = $(INCLUDE_TARGET) $(INCLUDE_UTILS) $(INCLUDE_DRIVER) $(INCLUDE_ROOTDIR) $(INCLUDE_LIB)
CFLAGS += $(INCLUDES) -DTRACE_LEVEL=$(TRACE_LEVEL)
ASFLAGS = -mcpu=cortex-a5  -mfpu=vfpv4-d16 -Wall -g $(INCLUDES) -D$(CHIP) -D__ASSEMBLY__

BUILDDIR_SRAM = $(MAKEFILEDIR)/build/$(TARGET)/sram
BUILDDIR_DDRAM = $(MAKEFILEDIR)/build/$(TARGET)/ddram

OBJECTS =
OBJECTS_ASM =
include $(MAKEFILEDIR)/av/Makefile.files
include	$(MAKEFILEDIR)/bus/Makefile.files
include	$(MAKEFILEDIR)/core/Makefile.files
include $(MAKEFILEDIR)/crypto/Makefile.files
include $(MAKEFILEDIR)/io/Makefile.files
include $(MAKEFILEDIR)/net/Makefile.files
include $(MAKEFILEDIR)/serial/Makefile.files
include $(MAKEFILEDIR)/time/Makefile.files
include $(MAKEFILEDIR)/mem/Makefile.files

OBJECTS_SRAM = $(addprefix $(BUILDDIR_SRAM)/,$(OBJECTS))
OBJECTS_DDRAM = $(addprefix $(BUILDDIR_DDRAM)/,$(OBJECTS))

-include $(OBJECTS_SRAM:.o=.d)
-include $(OBJECTS_DDRAM:.o=.d)

$(BUILDDIR_SRAM) $(BUILDDIR_DDRAM):
	mkdir -p $(addprefix $@/, $(DRIVERSUBDIRS))

$(OBJECTS_SRAM): $(BUILDDIR_SRAM)/%.o: %.c
	@$(CC) $(CFLAGS) $(call optimization,$(sram)) -MM $< -o $(BUILDDIR_SRAM)/$*.d
	@mv -f $(BUILDDIR_SRAM)/$*.d $(BUILDDIR_SRAM)/$*.d.tmp;
	@sed -e 's|.*:|$(BUILDDIR_SRAM)/$*.o:|' < $(BUILDDIR_SRAM)/$*.d.tmp > $(BUILDDIR_SRAM)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR_SRAM)/$*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR_SRAM)/$*.d
	@rm -f $(BUILDDIR_SRAM)/$*.d.tmp
	$(CC) $(CFLAGS) $(call optimization,$(sram)) -c $< -o $@


$(OBJECTS_DDRAM): $(BUILDDIR_DDRAM)/%.o: %.c
	@$(CC) $(CFLAGS) $(call optimization,$(sram)) -MM $< -o $(BUILDDIR_DDRAM)/$*.d
	@mv -f $(BUILDDIR_DDRAM)/$*.d $(BUILDDIR_DDRAM)/$*.d.tmp;
	@sed -e 's|.*:|$(BUILDDIR_DDRAM)/$*.o:|' < $(BUILDDIR_DDRAM)/$*.d.tmp > $(BUILDDIR_DDRAM)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR_DDRAM)/$*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR_DDRAM)/$*.d
	@rm -f $(BUILDDIR_DDRAM)/$*.d.tmp
	$(CC) $(CFLAGS) $(call optimization,$(sram)) -c $< -o $@

$(addprefix $(BUILDDIR_SRAM)/,$(OBJECTS_ASM)): $(BUILDDIR_SRAM)/%.o: %.S
	$(CC) $(ASFLAGS) $(call optimization,$(sram)) -c $< -o $@

$(addprefix $(BUILDDIR_DDRAM)/,$(OBJECTS_ASM)): $(BUILDDIR_DDRAM)/%.o: %.S
	$(CC) $(ASFLAGS) $(call optimization,$(sram)) -c $< -o $@


$(MAKEFILEDIR)/libdrivers-$(TARGET)_sram.a: $(addprefix $(BUILDDIR_SRAM)/,$(OBJECTS)) $(addprefix $(BUILDDIR_SRAM)/,$(OBJECTS_ASM))
	$(AR) -r $@ $^

$(MAKEFILEDIR)/libdrivers-$(TARGET)_ddram.a: $(addprefix $(BUILDDIR_DDRAM)/,$(OBJECTS)) $(addprefix $(BUILDDIR_DDRAM)/,$(OBJECTS_ASM))
	$(AR) -r $@ $^

libdrivers-$(TARGET)_sram: $(BUILDDIR_SRAM) $(MAKEFILEDIR)/libdrivers-$(TARGET)_sram.a

libdrivers-$(TARGET)_ddram: $(BUILDDIR_DDRAM) $(MAKEFILEDIR)/libdrivers-$(TARGET)_ddram.a

.PHONY = clean
clean:
	-rm -rf $(MAKEFILEDIR)/build
	-rm -f $(MAKEFILEDIR)/*.a

all: libdrivers-$(TARGET)_sram libdrivers-$(TARGET)_ddram
