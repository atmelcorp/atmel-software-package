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

INCLUDES = $(INCLUDE_LIB) $(INCLUDE_TARGET) $(INCLUDE_UTILS) $(INCLUDE_DRIVER)
CFLAGS += $(INCLUDES)

OBJECTS = $(MAKEFILEDIR)/dbg_util.o \
	$(MAKEFILEDIR)/hamming.o    \
	$(MAKEFILEDIR)/retarget.o   \
	$(MAKEFILEDIR)/math.o       \
	$(MAKEFILEDIR)/rand.o       \
	$(MAKEFILEDIR)/trace.o      \
	$(MAKEFILEDIR)/syscalls.o

OBJECTS_SRAM = $(addprefix $(MAKEFILEDIR)/build/$(TARGET)/sram/,$(OBJECTS))
OBJECTS_DDRAM = $(addprefix $(MAKEFILEDIR)/build/$(TARGET)/ddram/, $(OBJECTS))

BUILDDIR_SRAM = $(MAKEFILEDIR)/build/$(TARGET)/sram
BUILDDIR_DDRAM = $(MAKEFILEDIR)/build/$(TARGET)/ddram

#-------------------------------------------------------------------------------
# Rules
#-------------------------------------------------------------------------------
all: libutils-$(TARGET)_sram libutils-$(TARGET)_ddram

$(BUILDDIR_SRAM) $(BUILDDIR_DDRAM):
	mkdir -p $@

$(OBJECTS_SRAM): $(BUILDDIR_SRAM)/%.o: %.c
	$(CC) -c $(CFLAGS) $(call optimization,sram) $< -o $@

$(OBJECTS_DDRAM): $(BUILDDIR_DDRAM)/%.o: %.c
	$(CC) -c $(CFLAGS) $(call optimization,ddram) $< -o $@

libutils-$(TARGET)_sram.a: $(OBJECTS_SRAM)
	$(AR) -r $@ $^

libutils-$(TARGET)_ddram.a: $(OBJECTS_DDRAM)
	$(AR) -r $@ $^

libutils-$(TARGET)_sram: $(BUILDDIR_SRAM)  libutils-$(TARGET)_sram.a

libutils-$(TARGET)_ddram: $(BUILDDIR_DDRAM) libutils-$(TARGET)_ddram.a

.PHONY: clean
clean:
	@echo --- Cleaning $(BOARD) files [$(OUTPUT_PATH)$(SEP)*.o]
	rm -fR $(MAKEFILEDIR)/build/ 1>/dev/null 2>&1
	rm -fR *.a 1>/dev/null 2>&1
