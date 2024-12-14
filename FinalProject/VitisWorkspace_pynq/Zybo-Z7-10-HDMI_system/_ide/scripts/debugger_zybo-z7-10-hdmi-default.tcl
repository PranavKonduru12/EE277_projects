# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: D:\WorkRaduV\Projects\Zybo-Z7\sw\ws\Zybo-Z7-10-HDMI_system\_ide\scripts\debugger_zybo-z7-10-hdmi-default.tcl
# 
# 
# Usage with xsct:
# In an external shell use the below command and launch symbol server.
# symbol_server.bat -S -s tcp::1534
# To debug using xsct, launch xsct and run below command
# source D:\WorkRaduV\Projects\Zybo-Z7\sw\ws\Zybo-Z7-10-HDMI_system\_ide\scripts\debugger_zybo-z7-10-hdmi-default.tcl
# 
connect -path [list tcp::1534 tcp:10.113.0.78:3121]
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Zybo Z7 210351A6C768A" && level==0 && jtag_device_ctx=="jsn-Zybo Z7-210351A6C768A-13722093-0"}
fpga -file D:/WorkRaduV/Projects/Zybo-Z7/sw/ws/Zybo-Z7-10-HDMI/_ide/bitstream/design_1_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw D:/WorkRaduV/Projects/Zybo-Z7/sw/ws/design_1_wrapper/export/design_1_wrapper/hw/design_1_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source D:/WorkRaduV/Projects/Zybo-Z7/sw/ws/Zybo-Z7-10-HDMI/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow D:/WorkRaduV/Projects/Zybo-Z7/sw/ws/Zybo-Z7-10-HDMI/Debug/Zybo-Z7-10-HDMI.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
