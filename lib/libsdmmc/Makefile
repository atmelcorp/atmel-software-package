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

INCLUDES = $(INCLUDE_LIB)
CFLAGS += $(INCLUDES)

OBJECTS_SRAM = $(MAKEFILEDIR)/build/$(TARGET)/sram/sdmmc.o
OBJECTS_DDRAM = $(MAKEFILEDIR)/build/$(TARGET)/ddram/sdmmc.o

BUILDDIR_SRAM = $(MAKEFILEDIR)/build/$(TARGET)/sram
BUILDDIR_DDRAM = $(MAKEFILEDIR)/build/$(TARGET)/ddram

-include $(OBJECTS_SRAM:.o=.d)
-include $(OBJECTS_DDRAM:.o=.d)

#-------------------------------------------------------------------------------
# Rules
#-------------------------------------------------------------------------------
all: libsdmmc-$(TARGET)_sram libsdmmc-$(TARGET)_ddram

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
@$(CC) $(CFLAGS) -M $< -o $(BUILDDIR_DDRAM)/$*.d
	@cp -f $(BUILDDIR_DDRAM)/$*.d $(BUILDDIR_DDRAM)/$*.d.tmp
	@mv -f $(BUILDDIR_DDRAM)/$*.d $(BUILDDIR_DDRAM)/$*.d.tmp;
	@sed -e 's|.*:|$(BUILDDIR_DDRAM)/$*.o:|' < $(BUILDDIR_DDRAM)/$*.d.tmp > $(BUILDDIR_DDRAM)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR_DDRAM)/$*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR_DDRAM)/$*.d
	@rm -f $(BUILDDIR_DDRAM)/$*.d.tmp
	$(CC) -c $(CFLAGS) $(call optimization,ddram) $< -o $@

libsdmmc-$(TARGET)_sram.a: $(OBJECTS_SRAM)
	$(AR) -r $@ $^

libsdmmc-$(TARGET)_ddram.a: $(OBJECTS_DDRAM)
	$(AR) -r $@ $^

libsdmmc-$(TARGET)_sram: $(BUILDDIR_SRAM)  libsdmmc-$(TARGET)_sram.a

libsdmmc-$(TARGET)_ddram: $(BUILDDIR_DDRAM) libsdmmc-$(TARGET)_ddram.a

clean:
	rm -fR $(MAKEFILEDIR)/build/ 1>/dev/null 2>&1
	rm -fR *.a 1>/dev/null 2>&1
