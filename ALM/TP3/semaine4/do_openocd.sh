#!/bin/bash
exec openocd -f /opt/STM32_XPACK//XPACK/FLASH_DEBUG/OPENOCD_CONFIG/stm32f4discovery.cfg -c "gdb_port 3333"

