BOOT=rom                   # BOOT=rom or BOOT=ram   (make clean after any change)

XPACK_DIRECTORY ?= /opt/STM32_XPACK/XPACK

OBJS +=  cold_startup.o firmware.o 
OBJS +=  i2c_audio.o cs_audio_config.o               # add your other_file.o
OBJS +=  timer.o

include ${XPACK_DIRECTORY}/MAKEFILES/Makefile_common
include ${XPACK_DIRECTORY}/MAKEFILES/Makefile_${BOOT}


######################## .o rules ##################################################

cold_startup.o:	libopencm3 cold_startup.c cold_startup.h 

firmware.o:	libopencm3 firmware.c cold_startup.h

timer.o:	timer.c timer.h
                                                      ### add your other_file.o rule

####################################################################################

localclean:
	-rm $(OBJS) *.d *.elf *.hex

