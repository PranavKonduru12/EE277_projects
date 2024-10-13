-makelib xcelium_lib/xilinx_vip -sv \
  "C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
  "C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
  "C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
  "C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
  "C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/axi_vip_if.sv" \
  "C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/clk_vip_if.sv" \
  "C:/Xilinx/Vivado/2021.1/data/xilinx_vip/hdl/rst_vip_if.sv" \
-endlib
-makelib xcelium_lib/xpm -sv \
  "C:/Xilinx/Vivado/2021.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
  "C:/Xilinx/Vivado/2021.1/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \
-endlib
-makelib xcelium_lib/xpm \
  "C:/Xilinx/Vivado/2021.1/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib xcelium_lib/axi_infrastructure_v1_1_0 \
  "../../../../Lab2_AXILiteImplement2021.gen/sources_1/bd/AXI_Integration/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_vip_v1_1_10 -sv \
  "../../../../Lab2_AXILiteImplement2021.gen/sources_1/bd/AXI_Integration/ipshared/0980/hdl/axi_vip_v1_1_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/processing_system7_vip_v1_0_12 -sv \
  "../../../../Lab2_AXILiteImplement2021.gen/sources_1/bd/AXI_Integration/ipshared/f42d/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/AXI_Integration/ip/AXI_Integration_processing_system7_0_0/sim/AXI_Integration_processing_system7_0_0.v" \
  "../../../bd/AXI_Integration/ipshared/67b1/hdl/myip_v1_0_S00_AXI.v" \
  "../../../bd/AXI_Integration/ipshared/67b1/hdl/myip_v1_0.v" \
  "../../../bd/AXI_Integration/ip/AXI_Integration_myip_0_0/sim/AXI_Integration_myip_0_0.v" \
-endlib
-makelib xcelium_lib/lib_cdc_v1_0_2 \
  "../../../../Lab2_AXILiteImplement2021.gen/sources_1/bd/AXI_Integration/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \
-endlib
-makelib xcelium_lib/proc_sys_reset_v5_0_13 \
  "../../../../Lab2_AXILiteImplement2021.gen/sources_1/bd/AXI_Integration/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/AXI_Integration/ip/AXI_Integration_rst_ps7_0_50M_1/sim/AXI_Integration_rst_ps7_0_50M_1.vhd" \
-endlib
-makelib xcelium_lib/generic_baseblocks_v2_1_0 \
  "../../../../Lab2_AXILiteImplement2021.gen/sources_1/bd/AXI_Integration/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/fifo_generator_v13_2_5 \
  "../../../../Lab2_AXILiteImplement2021.gen/sources_1/bd/AXI_Integration/ipshared/276e/simulation/fifo_generator_vlog_beh.v" \
-endlib
-makelib xcelium_lib/fifo_generator_v13_2_5 \
  "../../../../Lab2_AXILiteImplement2021.gen/sources_1/bd/AXI_Integration/ipshared/276e/hdl/fifo_generator_v13_2_rfs.vhd" \
-endlib
-makelib xcelium_lib/fifo_generator_v13_2_5 \
  "../../../../Lab2_AXILiteImplement2021.gen/sources_1/bd/AXI_Integration/ipshared/276e/hdl/fifo_generator_v13_2_rfs.v" \
-endlib
-makelib xcelium_lib/axi_data_fifo_v2_1_23 \
  "../../../../Lab2_AXILiteImplement2021.gen/sources_1/bd/AXI_Integration/ipshared/94ec/hdl/axi_data_fifo_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_register_slice_v2_1_24 \
  "../../../../Lab2_AXILiteImplement2021.gen/sources_1/bd/AXI_Integration/ipshared/8f68/hdl/axi_register_slice_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_protocol_converter_v2_1_24 \
  "../../../../Lab2_AXILiteImplement2021.gen/sources_1/bd/AXI_Integration/ipshared/6e0d/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../bd/AXI_Integration/ip/AXI_Integration_auto_pc_0/sim/AXI_Integration_auto_pc_0.v" \
  "../../../bd/AXI_Integration/sim/AXI_Integration.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  glbl.v
-endlib

