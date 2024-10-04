BOOT=rom                   # BOOT=rom or BOOT=ram

XPACK_DIRECTORY ?= /opt/STM32_XPACK/XPACK

OBJS +=  cold_startup.o firmware.o bp_leds.o

include ${XPACK_DIRECTORY}/MAKEFILES/Makefile_common
include ${XPACK_DIRECTORY}/MAKEFILES/Makefile_${BOOT}

######################## .o rukes ##################################################

cold_startup.o: cold_startup.c cold_startup.h

firmware.o:     firmware.c cold_startup.h

####################################################################################

localclean:
	-rm $(OBJS) *.d *.elf *.hex
