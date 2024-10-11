BOOT=rom                   # BOOT=rom or BOOT=ram

XPACK_DIRECTORY ?= /opt/STM32_XPACK/XPACK

OBJS +=  cold_startup.o firmware.o bp_leds.o spi_mems.o

include ${XPACK_DIRECTORY}/MAKEFILES/Makefile_common
include ${XPACK_DIRECTORY}/MAKEFILES/Makefile_${BOOT}

######################## .o rukes ##################################################

cold_startup.o: cold_startup.c cold_startup.h

firmware.o:     firmware.c cold_startup.h bp_leds.h spi_mems.h

bp_leds.o:	bp_leds.c bp_leds.h

spi_mems.o:	spi_mems.c spi_mems.h lis3dsh.h

####################################################################################

localclean:
	-rm $(OBJS) *.d *.elf *.hex
