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
TARGET_INCLUDES = $(INCLUDE_LIB) $(INCLUDE_TARGET) $(INCLUDE_UTILS) $(INCLUDE_DRIVER)
TARGET_CFLAGS += $(CFLAGS) $(TARGET_INCLUDES)
TARGET_ASFLAGS = -mcpu=cortex-a5  -mfpu=vfpv4-d16 -Wall -g $(TARGET_INCLUDES) -D$(CHIP) -D__ASSEMBLY__

TARGET_OBJECTS = board_lowlevel.o \
	board_memories.o \
	cortexa5_interrupts.o

TARGET_OBJECTS_ASM = board_cstartup_gnu.o

TARGET_OBJECTS_SRAM = $(addprefix $(TARGETDIR)/$(SERIENAME)/build/$(TARGET)/sram/,$(TARGET_OBJECTS))
TARGET_OBJECTS_DDRAM = $(addprefix $(TARGETDIR)/$(SERIENAME)/build/$(TARGET)/ddram/, $(TARGET_OBJECTS))

TARGET_OBJECTS_ASM_SRAM = $(addprefix $(TARGETDIR)/$(SERIENAME)/build/$(TARGET)/sram/,$(TARGET_OBJECTS_ASM))
TARGET_OBJECTS_ASM_DDRAM = $(addprefix $(TARGETDIR)/$(SERIENAME)/build/$(TARGET)/ddram/, $(TARGET_OBJECTS_ASM))

TARGET_BUILDDIR_SRAM = $(TARGETDIR)/$(SERIENAME)/build/$(TARGET)/sram
TARGET_BUILDDIR_DDRAM = $(TARGETDIR)/$(SERIENAME)/build/$(TARGET)/ddram

-include $(TARGET_OBJECTS_SRAM:.o=.d)
-include $(TARGET_OBJECTS_DDRAM:.o=.d)

#-------------------------------------------------------------------------------
# Rules
#-------------------------------------------------------------------------------
all: lib$(TARGET)_sram lib$(TARGET)_ddram

$(TARGET_BUILDDIR_SRAM) $(TARGET_BUILDDIR_DDRAM):
	mkdir -p $@

$(TARGET_OBJECTS_SRAM): $(TARGET_BUILDDIR_SRAM)/%.o: %.c
	@$(CC) $(TARGET_CFLAGS) -M $< -o $(TARGET_BUILDDIR_SRAM)/$*.d
	@cp -f $(TARGET_BUILDDIR_SRAM)/$*.d $(TARGET_BUILDDIR_SRAM)/$*.d.tmp
	@mv -f $(TARGET_BUILDDIR_SRAM)/$*.d $(TARGET_BUILDDIR_SRAM)/$*.d.tmp;
	@sed -e 's|.*:|$(TARGET_BUILDDIR_SRAM)/$*.o:|' < $(TARGET_BUILDDIR_SRAM)/$*.d.tmp > $(TARGET_BUILDDIR_SRAM)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(TARGET_BUILDDIR_SRAM)/$*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $(TARGET_BUILDDIR_SRAM)/$*.d
	@rm -f $(TARGET_BUILDDIR_SRAM)/$*.d.tmp
	$(CC) -c $(TARGET_CFLAGS) $(call optimization,sram) $< -o $@

$(TARGET_OBJECTS_DDRAM): $(TARGET_BUILDDIR_DDRAM)/%.o: %.c
	@$(CC) $(TARGET_CFLAGS) -M $< -o $(TARGET_BUILDDIR_SRAM)/$*.d
	@cp -f $(TARGET_BUILDDIR_SRAM)/$*.d $(TARGET_BUILDDIR_SRAM)/$*.d.tmp
	@mv -f $(TARGET_BUILDDIR_SRAM)/$*.d $(TARGET_BUILDDIR_SRAM)/$*.d.tmp;
	@sed -e 's|.*:|$(TARGET_BUILDDIR_SRAM)/$*.o:|' < $(TARGET_BUILDDIR_SRAM)/$*.d.tmp > $(TARGET_BUILDDIR_SRAM)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(TARGET_BUILDDIR_SRAM)/$*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $(TARGET_BUILDDIR_SRAM)/$*.d
	@rm -f $(TARGET_BUILDDIR_SRAM)/$*.d.tmp
	$(CC) -c $(TARGET_CFLAGS) $(call optimization,ddram) $< -o $@

$(TARGET_OBJECTS_ASM_SRAM): $(TARGET_BUILDDIR_SRAM)/%.o: %.S
	$(CC) -c $(TARGET_ASFLAGS) $(call optimization,sram) $< -o $@

$(TARGET_OBJECTS_ASM_DDRAM): $(TARGET_BUILDDIR_DDRAM)/%.o: %.S
	$(CC) -c $(TARGET_ASFLAGS) $(call optimization,ddram) $< -o $@

$(TARGETDIR)/$(SERIENAME)/lib$(TARGET)_sram.a: $(TARGET_OBJECTS_SRAM) $(TARGET_OBJECTS_ASM_SRAM)
	$(AR) -r $@ $^

$(TARGETDIR)/$(SERIENAME)/lib$(TARGET)_ddram.a: $(TARGET_OBJECTS_DDRAM) $(TARGET_OBJECTS_ASM_DDRAM)
	$(AR) -r $@ $^

lib$(TARGET)_sram: $(TARGET_BUILDDIR_SRAM)  $(TARGETDIR)/$(SERIENAME)/lib$(TARGET)_sram.a

lib$(TARGET)_ddram: $(TARGET_BUILDDIR_DDRAM) $(TARGETDIR)/$(SERIENAME)/lib$(TARGET)_ddram.a
