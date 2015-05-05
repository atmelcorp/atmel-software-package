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

#-------------------------------------------------------------------------------
#        User-modifiable options
#-------------------------------------------------------------------------------

# Output directories
DRIVERSUBDIRS = av bus core crypto io net serial time mem

DRIVER_CFLAGS = $(CFLAGS)

#-------------------------------------------------------------------------------
#		Tools
#-------------------------------------------------------------------------------
DRIVER_INCLUDES = $(INCLUDE_TARGET) $(INCLUDE_UTILS) $(INCLUDE_DRIVER) $(INCLUDE_ROOTDIR) $(INCLUDE_LIB)
DRIVER_CFLAGS += $(DRIVER_INCLUDES)
ifdef TRACE_LEVEL
DRIVER_CFLAGS += -DTRACE_LEVEL=$(TRACE_LEVEL)
endif
DRIVERA_ASFLAGS = -mcpu=cortex-a5  -mfpu=vfpv4-d16 -Wall -g $(DRIVER_INCLUDES) -D$(CHIP) -D__ASSEMBLY__

DRIVER_BUILDDIR_SRAM = $(DRIVERDIR)/build/$(TARGET)/sram
DRIVER_BUILDDIR_DDRAM = $(DRIVERDIR)/build/$(TARGET)/ddram

DRIVER_OBJECTS =
DRIVER_OBJECTS_ASM =
include $(DRIVERDIR)/av/Makefile.files
include	$(DRIVERDIR)/bus/Makefile.files
include	$(DRIVERDIR)/core/Makefile.files
include $(DRIVERDIR)/crypto/Makefile.files
include $(DRIVERDIR)/io/Makefile.files
include $(DRIVERDIR)/net/Makefile.files
include $(DRIVERDIR)/serial/Makefile.files
include $(DRIVERDIR)/time/Makefile.files
include $(DRIVERDIR)/mem/Makefile.files

DRIVER_OBJECTS_SRAM = $(addprefix $(DRIVER_BUILDDIR_SRAM)/,$(DRIVER_OBJECTS))
DRIVER_OBJECTS_ASM_SRAM = $(addprefix $(DRIVER_BUILDDIR_SRAM)/,$(DRIVER_OBJECTS_ASM))
DRIVER_OBJECTS_DDRAM = $(addprefix $(DRIVER_BUILDDIR_DDRAM)/,$(DRIVER_OBJECTS))
DRIVER_OBJECTS_ASM_DDRAM = $(addprefix $(DRIVER_BUILDDIR_DDRAM)/,$(DRIVER_OBJECTS_ASM))

-include $(DRIVER_OBJECTS_SRAM:.o=.d)
-include $(DRIVER_OBJECTS_DDRAM:.o=.d)

$(DRIVER_BUILDDIR_SRAM) $(DRIVER_BUILDDIR_DDRAM):
	mkdir -p $(addprefix $@/, $(DRIVERSUBDIRS))

$(DRIVER_OBJECTS_SRAM) $(DRIVER_OBJECTS_ASM_SRAM): | $(DRIVER_BUILDDIR_SRAM)

$(DRIVER_OBJECTS_SRAM): $(DRIVER_BUILDDIR_SRAM)/%.o: %.c
	@$(CC) $(DRIVER_CFLAGS) -M $< -o $(DRIVER_BUILDDIR_SRAM)/$*.d
	@mv -f $(DRIVER_BUILDDIR_SRAM)/$*.d $(DRIVER_BUILDDIR_SRAM)/$*.d.tmp;
	@sed -e 's|.*:|$(DRIVER_BUILDDIR_SRAM)/$*.o:|' < $(DRIVER_BUILDDIR_SRAM)/$*.d.tmp > $(DRIVER_BUILDDIR_SRAM)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(DRIVER_BUILDDIR_SRAM)/$*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $(DRIVER_BUILDDIR_SRAM)/$*.d
	@rm -f $(DRIVER_BUILDDIR_SRAM)/$*.d.tmp
	$(CC) $(DRIVER_CFLAGS) $(call optimization,sram) -c $< -o $@

$(DRIVER_OBJECTS_DDRAM) $(DRIVER_OBJECTS_ASM_DDRAM): | $(DRIVER_BUILDDIR_DDRAM)

$(DRIVER_OBJECTS_DDRAM): $(DRIVER_BUILDDIR_DDRAM)/%.o: %.c
	@$(CC) $(DRIVER_CFLAGS) $(call optimization,ddram) -M $< -o $(DRIVER_BUILDDIR_DDRAM)/$*.d
	@mv -f $(DRIVER_BUILDDIR_DDRAM)/$*.d $(DRIVER_BUILDDIR_DDRAM)/$*.d.tmp;
	@sed -e 's|.*:|$(DRIVER_BUILDDIR_DDRAM)/$*.o:|' < $(DRIVER_BUILDDIR_DDRAM)/$*.d.tmp > $(DRIVER_BUILDDIR_DDRAM)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(DRIVER_BUILDDIR_DDRAM)/$*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $(DRIVER_BUILDDIR_DDRAM)/$*.d
	@rm -f $(DRIVER_BUILDDIR_DDRAM)/$*.d.tmp
	$(CC) $(DRIVER_CFLAGS) $(call optimization,ddram) -c $< -o $@

$(DRIVER_OBJECTS_ASM_SRAM): $(DRIVER_BUILDDIR_SRAM)/%.o: %.S
	$(CC) $(DRIVERA_ASFLAGS) $(call optimization,sram) -c $< -o $@

$(DRIVER_OBJECTS_ASM_DDRAM): $(DRIVER_BUILDDIR_DDRAM)/%.o: %.S
	$(CC) $(DRIVERA_ASFLAGS) $(call optimization,ddram) -c $< -o $@


$(DRIVERDIR)/libdrivers-$(TARGET)_sram.a: $(DRIVER_OBJECTS_ASM_SRAM) $(DRIVER_OBJECTS_SRAM)
	$(AR) -r $@ $^

$(DRIVERDIR)/libdrivers-$(TARGET)_ddram.a: $(DRIVER_OBJECTS_ASM_DDRAM) $(DRIVER_OBJECTS_DDRAM)
	$(AR) -r $@ $^
