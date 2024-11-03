# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\LocalWorkspace\EE277workspace\Lab2_2021v\VitisWorkspace\design_1_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\LocalWorkspace\EE277workspace\Lab2_2021v\VitisWorkspace\design_1_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {design_1_wrapper}\
-hw {C:\LocalWorkspace\EE277workspace\Lab2_2021v\Lab2_AXI_Implementation\design_1_wrapper.xsa}\
-out {C:/LocalWorkspace/EE277workspace/Lab2_2021v/VitisWorkspace}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {empty_application}
platform generate -domains 
platform active {design_1_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
