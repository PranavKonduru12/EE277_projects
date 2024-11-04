# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\LocalWorkspace\EE277workspace\Lab3\Lab2_2021v_lab3mod\Lab3_VitisWorkspace\design_1_wrapper_lab3\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\LocalWorkspace\EE277workspace\Lab3\Lab2_2021v_lab3mod\Lab3_VitisWorkspace\design_1_wrapper_lab3\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {design_1_wrapper_lab3}\
-hw {C:\LocalWorkspace\EE277workspace\Lab3\design_1_wrapper_lab3.xsa}\
-out {C:/LocalWorkspace/EE277workspace/Lab3/Lab2_2021v_lab3mod/Lab3_VitisWorkspace}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {design_1_wrapper_lab3}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform generate
