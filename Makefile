TARGET = BatteryPatch
PSP_FW_VERSION = 500
BUILD_PRX = 1


OBJS = main.o


PRX_EXPORTS = exports.exp
USE_KERNEL_LIBC	= 1
USE_KERNEL_LIBS	= 1

CLASSG_LIBS = libs


INCDIR = $(CLASSG_LIBS)
CFLAGS = -Os -G0 -Wall -fno-strict-aliasing -fno-builtin-printf -DLNGJPN
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR			= 
LDFLAGS		=	-mno-crt0 -nostartfiles
LIBS = -lpspsystemctrl_kernel -lpspkubridge



PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build_prx.mak

all:

