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
include $(MAKEFILEDIR)/Makefile.inc

VPATH = $(MAKEFILEDIR)

LIBRARIES = $(UTILSDIR)/*.a $(TARGETDIR)/$(SERIENAME)/*.a $(DRIVERDIR)/*.a
USER_LIBRARIES = $(LIBDIR)/lwip/*.a

#EXAMPLES = $(wildcard $(MAKEFILEDIR)/examples/*/build)
EXAMPLES = $(MAKEFILEDIR)/examples/getting_started \
	$(MAKEFILEDIR)/examples/rtc \
	$(MAKEFILEDIR)/examples/gmac \
	$(MAKEFILEDIR)/examples/xdma \
	$(MAKEFILEDIR)/examples/trng

.PHONY: clean $(LIBRARIES) $(USER_LIBRARIES) $(addsuffix /build,$(EXAMPLES)) list-boards

$(LIBRARIES):
	$(MAKE) -f $(@D)/Makefile

$(USER_LIBRARIES):
	$(MAKE) -f $(@D)/Makefile

all: $(LIBRARIES) $(addsuffix /build,$(EXAMPLES))

clean:
	-rm -f $(LIBRARIES)
	-rm -f $(USER_LIBRARIES)
	-rm -rf $(UTILSDIR)/build
	-rm -rf $(TARGETDIR)/$(SERIENAME)/build
	-rm -rf $(DRIVERDIR)/build
	-rm -rf $(EXAMPLEDIR)/*/build
	-rm -rf $(LIBDIR)/*/build

$(addsuffix /build,$(EXAMPLES)): $(LIBRARIES) $(USER_LIBRARIES)
	$(MAKE) -f $(@D)/Makefile

list-boards:
	@echo List of all available boards:
	@echo $(AVAILABLE_BOARDS)
