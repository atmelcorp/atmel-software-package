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
include $(MAKEFILEDIR)/../Makefile.inc

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
BIN = bin
OBJ = obj
# Output directories
DRIVERSUBDIRS = av bus core crypto io net serial time wireless

#-------------------------------------------------------------------------------
#		Tools
#-------------------------------------------------------------------------------
#LIBS = -Wl,--start-group -lgcc -Wl,--end-group
INCLUDES = $(INCLUDE_TARGET) $(INCLUDE_UTILS) $(INCLUDE_DRIVER) $(INCLUDE_ROOTDIR) $(INCLUDE_LIB)
CFLAGS += $(INCLUDES) -DTRACE_LEVEL=$(TRACE_LEVEL)
ASFLAGS = -mcpu=cortex-a5 -Wall -g $(INCLUDES) -D__SAMA5D44__ -D__ASSEMBLY__


define LIBRULES
$(eval BUILDDIR = $(MAKEFILEDIR)/$(1)/build/$(TARGET)/$(2))
$(eval include $(MAKEFILEDIR)/$(1)/Makefile.files)

$(BUILDDIR)/$(BIN) $(BUILDDIR)/$(OBJ):
	mkdir -p $$@

$(1): $(BUILDDIR)/$(BIN) $(BUILDDIR)/$(BIN)/lib$(TARGET)_$(1).a
	@echo Built driver $(1)

$(BUILDDIR)/$(BIN)/lib$(TARGET)_$(1).a: $(addprefix $(BUILDDIR)/$(OBJ)/,$(OBJECTS))
	$(AR) -r $$@ $$^

$(BUILDDIR)/$(OBJ)/%.o: $(1)/%.c $(BUILDDIR)/$(OBJ)
	$(CC) $(CFLAGS) $(LDFLAGS) $(call optimization,$(2)) $(LD_OPTIONAL) -c $$< -o $$@
endef

drivers: $(DRIVERSUBDIRS)

$(foreach MEMORY, $(MEMORIES), \
$(foreach dir, $(DRIVERSUBDIRS), $(eval $(call LIBRULES,$(dir),$(MEMORY)))) \
)

$(BIN) $(OBJ):
	mkdir $@

