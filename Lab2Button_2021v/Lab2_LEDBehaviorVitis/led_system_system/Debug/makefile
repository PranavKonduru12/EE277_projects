#
# This file was created by Xilinx Vitis tool.
#


#
# tools
#

RM = rm -f
RMDIR = rm -rf



#
# variables
#

SDCARD_GEN = sdcard_gen
GENERATE_BIF = ::scw::generate_bif

XPFM_PATH = C:/LocalWorkspace/EE277workspace/Lab2_2021v/Lab2_LEDBehaviorVitis/design_1_wrapper/export/design_1_wrapper/design_1_wrapper.xpfm
SYS_CONFIG = design_1_wrapper
DOMAINS = standalone_ps7_cortexa9_0
BIF_PATH = C:/LocalWorkspace/EE277workspace/Lab2_2021v/Lab2_LEDBehaviorVitis/led_system_system/Debug/system.bif

BITSTREAM_PATH = C:/LocalWorkspace/EE277workspace/Lab2_2021v/Lab2_LEDBehaviorVitis/led_system/_ide/bitstream/design_1_wrapper.bit
SD_FILES = --elf C:/LocalWorkspace/EE277workspace/Lab2_2021v/Lab2_LEDBehaviorVitis/led_system/Debug/led_system.elf,ps7_cortexa9_0

#
# primary build targets
#

all: package

package:
	-@echo Generating bif file for the system project
	generate_system_bif.bat 55624 ${XPFM_PATH} ${DOMAINS} ${BIF_PATH}
	${SDCARD_GEN} --xpfm ${XPFM_PATH} --sys_config ${SYS_CONFIG} --bif ${BIF_PATH} --bitstream ${BITSTREAM_PATH} ${SD_FILES}

clean:
	$(RMDIR) ./_sds
	${RMDIR} package
	${RM} system.bif

.PHONY: all package clean


