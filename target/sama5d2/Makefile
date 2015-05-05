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
include $(MAKEFILEDIR)/../../Makefile.inc

VPATH = $(MAKEFILEDIR)

INCLUDES = $(INCLUDE_LIB) $(INCLUDE_TARGET) $(INCLUDE_UTILS) $(INCLUDE_DRIVER)
CFLAGS += $(INCLUDES)
ASFLAGS = -mcpu=cortex-a5  -mfpu=vfpv4-d16 -Wall -g $(INCLUDES) -D$(CHIP) -D__ASSEMBLY__

OBJECTS = board_lowlevel.o \
	board_memories.o

OBJECTS_ASM = board_cstartup_gnu.o

OBJECTS_SRAM = $(addprefix $(MAKEFILEDIR)/build/$(TARGET)/sram/,$(OBJECTS))
OBJECTS_DDRAM = $(addprefix $(MAKEFILEDIR)/build/$(TARGET)/ddram/, $(OBJECTS))

OBJECTS_ASM_SRAM = $(addprefix $(MAKEFILEDIR)/build/$(TARGET)/sram/,$(OBJECTS_ASM))
OBJECTS_ASM_DDRAM = $(addprefix $(MAKEFILEDIR)/build/$(TARGET)/ddram/, $(OBJECTS_ASM))

BUILDDIR_SRAM = $(MAKEFILEDIR)/build/$(TARGET)/sram
BUILDDIR_DDRAM = $(MAKEFILEDIR)/build/$(TARGET)/ddram

DEPS_SRAM = $(addprefix $(BUILDDIR_SRAM)/,$(OBJECTS))
DEPS_DDRAM = $(addprefix $(BUILDDIR_DDRAM)/,$(OBJECTS))

-include $(DEPS_SRAM:.o=.d)
-include $(DEPS_DDRAM:.o=.d)

#-------------------------------------------------------------------------------
# Rules
#-------------------------------------------------------------------------------
all: lib$(TARGET)_sram lib$(TARGET)_ddram

$(BUILDDIR_SRAM) $(BUILDDIR_DDRAM):
	mkdir -p $@

$(OBJECTS_SRAM): $(BUILDDIR_SRAM)/%.o: %.c
	@$(CC) $(CFLAGS) -M $< -o $(BUILDDIR_SRAM)/$*.d
	@cp -f $(BUILDDIR_SRAM)/$*.d $(BUILDDIR_SRAM)/$*.d.tmp
	@mv -f $(BUILDDIR_SRAM)/$*.d $(BUILDDIR_SRAM)/$*.d.tmp;
	@sed -e 's|.*:|$(BUILDDIR_SRAM)/$*.o:|' < $(BUILDDIR_SRAM)/$*.d.tmp > $(BUILDDIR_SRAM)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR_SRAM)/$*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR_SRAM)/$*.d
	@rm -f $(BUILDDIR_SRAM)/$*.d.tmp
	$(CC) -c $(CFLAGS) $(call optimization,sram) $< -o $@

$(OBJECTS_DDRAM): $(BUILDDIR_DDRAM)/%.o: %.c
	@$(CC) $(CFLAGS) -M $< -o $(BUILDDIR_SRAM)/$*.d
	@cp -f $(BUILDDIR_SRAM)/$*.d $(BUILDDIR_SRAM)/$*.d.tmp
	@mv -f $(BUILDDIR_SRAM)/$*.d $(BUILDDIR_SRAM)/$*.d.tmp;
	@sed -e 's|.*:|$(BUILDDIR_SRAM)/$*.o:|' < $(BUILDDIR_SRAM)/$*.d.tmp > $(BUILDDIR_SRAM)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR_SRAM)/$*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR_SRAM)/$*.d
	@rm -f $(BUILDDIR_SRAM)/$*.d.tmp
	$(CC) -c $(CFLAGS) $(call optimization,ddram) $< -o $@

$(OBJECTS_ASM_SRAM): $(BUILDDIR_SRAM)/%.o: %.S
	$(CC) -c $(CFLAGS) $(call optimization,sram) $< -o $@

$(OBJECTS_ASM_DDRAM): $(BUILDDIR_DDRAM)/%.o: %.S
	$(CC) -c $(CFLAGS) $(call optimization,ddram) $< -o $@

$(MAKEFILEDIR)/lib$(TARGET)_sram.a: $(OBJECTS_SRAM) $(OBJECTS_ASM_SRAM)
	$(AR) -r $@ $^

$(MAKEFILEDIR)/lib$(TARGET)_ddram.a: $(OBJECTS_DDRAM) $(OBJECTS_ASM_DDRAM)
	$(AR) -r $@ $^

lib$(TARGET)_sram: $(BUILDDIR_SRAM)  $(MAKEFILEDIR)/lib$(TARGET)_sram.a

lib$(TARGET)_ddram: $(BUILDDIR_DDRAM) $(MAKEFILEDIR)/lib$(TARGET)_ddram.a

.PHONY: clean
clean:
	@echo --- Cleaning $(BOARD) files [$(OUTPUT_PATH)$(SEP)*.o]
	rm -fR $(MAKEFILEDIR)/build/ 1>/dev/null 2>&1
	rm -fR $(MAKEFILEDIR)/*.a 1>/dev/null 2>&1
