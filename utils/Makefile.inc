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

UTILS_INCLUDES = $(INCLUDE_LIB) $(INCLUDE_TARGET) $(INCLUDE_UTILS) $(INCLUDE_DRIVER)
UTILS_CFLAGS = $(CFLAGS)
UTILS_CFLAGS += $(UTILS_INCLUDES)

UTILS_OBJECTS = dbg_util.o \
	hamming.o    \
	retarget.o   \
	math.o       \
	rand.o       \
	trace.o      \
	syscalls.o

UTILS_BUILDDIR_SRAM = $(UTILSDIR)/build/$(TARGET)/sram
UTILS_BUILDDIR_DDRAM = $(UTILSDIR)/build/$(TARGET)/ddram

UTILS_OBJECTS_SRAM = $(addprefix $(UTILS_BUILDDIR_SRAM)/,$(UTILS_OBJECTS))
UTILS_OBJECTS_DDRAM = $(addprefix $(UTILS_BUILDDIR_DDRAM)/, $(UTILS_OBJECTS))

-include $(UTILS_OBJECTS_SRAM:.o=.d)
-include $(UTILS_OBJECTS_DDRAM:.o=.d)

#-------------------------------------------------------------------------------
# Rules
#-------------------------------------------------------------------------------
$(UTILS_BUILDDIR_SRAM) $(UTILS_BUILDDIR_DDRAM):
	mkdir -p $@

$(UTILS_OBJECTS_SRAM): | $(UTILS_BUILDDIR_SRAM)

$(UTILS_OBJECTS_SRAM): $(UTILS_BUILDDIR_SRAM)/%.o: %.c
	@$(CC) $(UTILS_CFLAGS) -M $< -o $(UTILS_BUILDDIR_SRAM)/$*.d
	@cp -f $(UTILS_BUILDDIR_SRAM)/$*.d $(UTILS_BUILDDIR_SRAM)/$*.d.tmp
	@mv -f $(UTILS_BUILDDIR_SRAM)/$*.d $(UTILS_BUILDDIR_SRAM)/$*.d.tmp;
	@sed -e 's|.*:|$(UTILS_BUILDDIR_SRAM)/$*.o:|' < $(UTILS_BUILDDIR_SRAM)/$*.d.tmp > $(UTILS_BUILDDIR_SRAM)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(UTILS_BUILDDIR_SRAM)/$*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $(UTILS_BUILDDIR_SRAM)/$*.d
	@rm -f $(UTILS_BUILDDIR_SRAM)/$*.d.tmp
	$(CC) -c $(UTILS_CFLAGS) $(call optimization,sram) $< -o $@

$(UTILS_OBJECTS_DDRAM): | $(UTILS_BUILDDIR_DDRAM)

$(UTILS_OBJECTS_DDRAM): $(UTILS_BUILDDIR_DDRAM)/%.o: %.c
	@$(CC) $(UTILS_CFLAGS) -M $< -o $(UTILS_BUILDDIR_DDRAM)/$*.d
	@cp -f $(UTILS_BUILDDIR_DDRAM)/$*.d $(UTILS_BUILDDIR_DDRAM)/$*.d.tmp
	@mv -f $(UTILS_BUILDDIR_DDRAM)/$*.d $(UTILS_BUILDDIR_DDRAM)/$*.d.tmp;
	@sed -e 's|.*:|$(UTILS_BUILDDIR_DDRAM)/$*.o:|' < $(UTILS_BUILDDIR_DDRAM)/$*.d.tmp > $(UTILS_BUILDDIR_DDRAM)/$*.d
	@sed -e 's/.*://' -e 's/\\$$//' < $(UTILS_BUILDDIR_DDRAM)/$*.d.tmp | fmt -1 | \
		sed -e 's/^ *//' -e 's/$$/:/' >> $(UTILS_BUILDDIR_DDRAM)/$*.d
	@rm -f $(UTILS_BUILDDIR_DDRAM)/$*.d.tmp
	$(CC) -c $(UTILS_CFLAGS) $(call optimization,ddram) $< -o $@

$(UTILSDIR)/libutils-$(TARGET)_sram.a: $(UTILS_OBJECTS_SRAM)
	$(AR) -r $@ $^

$(UTILSDIR)/libutils-$(TARGET)_ddram.a: $(UTILS_OBJECTS_DDRAM)
	$(AR) -r $@ $^
