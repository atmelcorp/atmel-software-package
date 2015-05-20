ROOTDIR := $(dir $(lastword $(MAKEFILE_LIST)))

all:

SOFTPACK_VERSION="2.0"
AVAILABLE_MEMORIES = sram ddram
AVAILABLE_BOARDS = sama5d4-xplained sama5d4-ek sama5d2-xplained
MEMORIES = sram ddram

eq = $(and $(findstring $(1),$(2)),$(findstring $(2),$(1)))

ifndef TARGET
$(error "No TARGET specified.")
endif

SELECTED_BOARD=$(strip $(foreach board,$(AVAILABLE_BOARDS),$(if $(call eq,$(TARGET),$(board)),$(board))))

ifeq (,$(SELECTED_BOARD))
$(info The wanted target "$(TARGET)" is not supported)
$(error Please set TARGET to one value from the list above: $(AVAILABLE_BOARDS))
endif

#-------------------------------------------------------------------------------
#		Setup cross-compilation tools
#-------------------------------------------------------------------------------
# Tool suffix when cross-compiling
CROSS_COMPILE = arm-none-eabi-

# Compilation tools
CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)ld
SIZE = $(CROSS_COMPILE)size
STRIP = $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
GDB = $(CROSS_COMPILE)gdb
NM = $(CROSS_COMPILE)nm

#-------------------------------------------------------------------------------
#		Setup compilation params
#-------------------------------------------------------------------------------

OPTIMIZE_sram = -Os
OPTIMIZE_ddram =
OPTIMIZE_perf = -O2
optimization = $(OPTIMIZE_$(1))

# C flags
CFLAGS = -Wall -Wchar-subscripts -Wcomment -Wformat=2 -Wimplicit-int
CFLAGS += -Werror-implicit-function-declaration -Wmain -Wparentheses
CFLAGS += -Wsequence-point -Wreturn-type -Wswitch -Wtrigraphs
CFLAGS += -Wuninitialized -Wunknown-pragmas -Wfloat-equal -Wundef
CFLAGS += -Wshadow -Wpointer-arith -Wbad-function-cast -Wwrite-strings
CFLAGS += -Waggregate-return -Wstrict-prototypes
CFLAGS += -Wmissing-prototypes -Wmissing-declarations
CFLAGS += -Wformat -Wmissing-format-attribute -Wno-deprecated-declarations
CFLAGS += -Wredundant-decls -Wnested-externs -Winline -Wlong-long
CFLAGS += -Wunreachable-code
CFLAGS += -mcpu=cortex-a5 -ffunction-sections -Wall -g3
CFLAGS += -D$(CHIP) -D$(BOARD) -D$(SERIE) -DSOFTPACK_VERSION="$(SOFTPACK_VERSION)"
# To reduce application size use only integer printf function.
CFLAGS += -Dprintf=iprintf

# linkker flags
LDFLAGS= -mcpu=cortex-a5 -Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=entry -Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align -Wl,--warn-unresolved-symbols

include $(ROOTDIR)/Makefile.sama5d4
include $(ROOTDIR)/Makefile.sama5d2

#-------------------------------------------------------------------------------
#		Setup paths
#-------------------------------------------------------------------------------
LIBDIR := $(ROOTDIR)/lib
TARGETDIR := $(ROOTDIR)/target
DRIVERDIR := $(ROOTDIR)/drivers
UTILSDIR := $(ROOTDIR)/utils
RESOURCEDIR := $(TARGETDIR)/resources/gcc/$(SERIENAME)
IAR_RESOURCEDIR := $(TARGETDIR)/resources/iar/$(SERIENAME)
EXAMPLEDIR := $(ROOTDIR)/examples

# include dirs
INCLUDE_TARGET = -I$(TARGETDIR) -I$(TARGETDIR)/include
INCLUDE_UTILS = -I$(UTILSDIR)
INCLUDE_LIB = -I$(LIBDIR)
INCLUDE_DRIVER = -I$(DRIVERDIR)
INCLUDE_ROOTDIR = -I$(ROOTDIR)
