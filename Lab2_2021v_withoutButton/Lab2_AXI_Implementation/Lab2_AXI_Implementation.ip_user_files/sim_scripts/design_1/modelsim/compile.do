vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/xilinx_vip
vlib modelsim_lib/msim/xpm
vlib modelsim_lib/msim/axi_infrastructure_v1_1_0
vlib modelsim_lib/msim/axi_vip_v1_1_10
vlib modelsim_lib/msim/processing_system7_vip_v1_0_12
vlib modelsim_lib/msim/xil_defaultlib
vlib modelsim_lib/msim/lib_cdc_v1_0_2
vlib modelsim_lib/msim/proc_sys_reset_v5_0_13
vlib modelsim_lib/msim/generic_baseblocks_v2_1_0
vlib modelsim_lib/msim/fifo_generator_v13_2_5
vlib modelsim_lib/msim/axi_data_fifo_v2_1_23
vlib modelsim_lib/msim/axi_register_slice_v2_1_24
vlib modelsim_lib/msim/axi_protocol_converter_v2_1_24

vmap xilinx_vip modelsim_lib/msim/xilinx_vip
vmap xpm modelsim_lib/msim/xpm
vmap axi_infrastructure_v1_1_0 modelsim_lib/msim/axi_infrastructure_v1_1_0
vmap axi_vip_v1_1_10 modelsim_lib/msim/axi_vip_v1_1_10
vmap processing_system7_vip_v1_0_12 modelsim_lib/msim/processing_system7_vip_v1_0_12
vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib
vmap lib_cdc_v1_0_2 modelsim_lib/msim/lib_cdc_v1_0_2
vmap proc_sys_reset_v5_0_13 modelsim_lib/msim/proc_sys_reset_v5_0_13
vmap generic_baseblocks_v2_1_0 modelsim_lib/msim/generic_baseblocks_v2_1_0
vmap fifo_generator_v13_2_5 modelsim_lib/msim/fifo_generator_v13_2_5
vmap axi_data_fifo_v2_1_23 modelsim_lib/msim/axi_data_fifo_v2_1_23
vmap axi_register_slice_v2_1_24 modelsim_lib/msim/axi_register_slice_v2_1_24
vmap axi_protocol_converter_v2_1_24 modelsim_lib/msim/axi_protocol_converter_v2_1_24

vlog -work xilinx_vip  -incr -mfcu -sv -L axi_vip_v1_1_10 -L processing_system7_vip_v1_0_12 -L xilinx_vip "+incdir+C:/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi_vip_if.sv" \
"C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/clk_vip_if.sv" \
"C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -incr -mfcu -sv -L axi_vip_v1_1_10 -L processing_system7_vip_v1_0_12 -L xilinx_vip "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+C:/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2021.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"C:/Xilinx/Vivado/2021.1/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm  -93 \
"C:/Xilinx/Vivado/2021.1/data/ip/xpm/xpm_VCOMP.vhd" \

vlog -work axi_infrastructure_v1_1_0  -incr -mfcu "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+C:/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_10  -incr -mfcu -sv -L axi_vip_v1_1_10 -L processing_system7_vip_v1_0_12 -L xilinx_vip "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+C:/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/0980/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work processing_system7_vip_v1_0_12  -incr -mfcu -sv -L axi_vip_v1_1_10 -L processing_system7_vip_v1_0_12 -L xilinx_vip "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+C:/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/f42d/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+C:/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_processing_system7_0_0/sim/design_1_processing_system7_0_0.v" \
"../../../bd/design_1/ipshared/785f/hdl/AUP_advanced_SoC_v1_0_S00_AXI.v" \
"../../../bd/design_1/ipshared/785f/hdl/AUP_advanced_SoC_v1_0.v" \
"../../../bd/design_1/ip/design_1_AUP_advanced_SoC_0_0/sim/design_1_AUP_advanced_SoC_0_0.v" \

vcom -work lib_cdc_v1_0_2  -93 \
"../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work proc_sys_reset_v5_0_13  -93 \
"../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib  -93 \
"../../../bd/design_1/ip/design_1_rst_ps7_0_50M_0/sim/design_1_rst_ps7_0_50M_0.vhd" \

vlog -work generic_baseblocks_v2_1_0  -incr -mfcu "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+C:/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work fifo_generator_v13_2_5  -incr -mfcu "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+C:/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/276e/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_5  -93 \
"../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/276e/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_5  -incr -mfcu "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+C:/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/276e/hdl/fifo_generator_v13_2_rfs.v" \

vlog -work axi_data_fifo_v2_1_23  -incr -mfcu "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+C:/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/94ec/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_24  -incr -mfcu "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+C:/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/8f68/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work axi_protocol_converter_v2_1_24  -incr -mfcu "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+C:/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/6e0d/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../Lab2_AXI_Implementation.gen/sources_1/bd/design_1/ipshared/f42d/hdl" "+incdir+C:/Xilinx/Vivado/2021.1/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_auto_pc_0/sim/design_1_auto_pc_0.v" \
"../../../bd/design_1/sim/design_1.v" \

vlog -work xil_defaultlib \
"glbl.v"

