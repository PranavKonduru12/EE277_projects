# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\Student\Desktop\code\hek\Zybo-Z7-10-HDMI_system\_ide\scripts\systemdebugger_zybo-z7-10-hdmi_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\Student\Desktop\code\hek\Zybo-Z7-10-HDMI_system\_ide\scripts\systemdebugger_zybo-z7-10-hdmi_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Zybo Z7 210351B7A984A" && level==0 && jtag_device_ctx=="jsn-Zybo Z7-210351B7A984A-13722093-0"}
fpga -file C:/Users/Student/Desktop/code/hek/Zybo-Z7-10-HDMI/_ide/bitstream/design_1_wrapper_new.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/Student/Desktop/code/hek/design_1_wrapper/export/design_1_wrapper/hw/design_1_wrapper_new.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/Users/Student/Desktop/code/hek/Zybo-Z7-10-HDMI/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow C:/Users/Student/Desktop/code/hek/Zybo-Z7-10-HDMI/Debug/Zybo-Z7-10-HDMI.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
