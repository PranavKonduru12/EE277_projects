-makelib xcelium_lib/xilinx_vip -sv \
  "D:/Vivado/2022.1/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
  "D:/Vivado/2022.1/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
  "D:/Vivado/2022.1/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
  "D:/Vivado/2022.1/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
  "D:/Vivado/2022.1/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
  "D:/Vivado/2022.1/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
  "D:/Vivado/2022.1/data/xilinx_vip/hdl/axi_vip_if.sv" \
  "D:/Vivado/2022.1/data/xilinx_vip/hdl/clk_vip_if.sv" \
  "D:/Vivado/2022.1/data/xilinx_vip/hdl/rst_vip_if.sv" \
-endlib
-makelib xcelium_lib/xpm -sv \
  "D:/Vivado/2022.1/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
  "D:/Vivado/2022.1/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
  "D:/Vivado/2022.1/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \
-endlib
-makelib xcelium_lib/xpm \
  "D:/Vivado/2022.1/data/ip/xpm/xpm_VCOMP.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/f822/src/SyncAsync.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/f822/src/mmcme2_drp.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/f822/src/axi_dynclk_S00_AXI.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/f822/src/axi_dynclk.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axi_dynclk_0_0/sim/design_1_axi_dynclk_0_0.vhd" \
-endlib
-makelib xcelium_lib/generic_baseblocks_v2_1_0 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/b752/hdl/generic_baseblocks_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_infrastructure_v1_1_0 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_register_slice_v2_1_26 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0a3f/hdl/axi_register_slice_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/fifo_generator_v13_2_7 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/83df/simulation/fifo_generator_vlog_beh.v" \
-endlib
-makelib xcelium_lib/fifo_generator_v13_2_7 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/83df/hdl/fifo_generator_v13_2_rfs.vhd" \
-endlib
-makelib xcelium_lib/fifo_generator_v13_2_7 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/83df/hdl/fifo_generator_v13_2_rfs.v" \
-endlib
-makelib xcelium_lib/axi_data_fifo_v2_1_25 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/5390/hdl/axi_data_fifo_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axi_crossbar_v2_1_27 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/3fa0/hdl/axi_crossbar_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_xbar_0/sim/design_1_xbar_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_xbar_1/sim/design_1_xbar_1.v" \
-endlib
-makelib xcelium_lib/lib_cdc_v1_0_2 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \
-endlib
-makelib xcelium_lib/lib_pkg_v1_0_2 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0513/hdl/lib_pkg_v1_0_rfs.vhd" \
-endlib
-makelib xcelium_lib/lib_fifo_v1_0_16 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/6c82/hdl/lib_fifo_v1_0_rfs.vhd" \
-endlib
-makelib xcelium_lib/blk_mem_gen_v8_4_5 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/25a8/simulation/blk_mem_gen_v8_4.v" \
-endlib
-makelib xcelium_lib/lib_bmg_v1_0_14 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/3a3e/hdl/lib_bmg_v1_0_rfs.vhd" \
-endlib
-makelib xcelium_lib/lib_srl_fifo_v1_0_2 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/51ce/hdl/lib_srl_fifo_v1_0_rfs.vhd" \
-endlib
-makelib xcelium_lib/axi_datamover_v5_1_28 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/1bb8/hdl/axi_datamover_v5_1_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/axi_vdma_v6_3_14 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/fc4b/hdl/axi_vdma_v6_3_rfs.v" \
-endlib
-makelib xcelium_lib/axi_vdma_v6_3_14 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/fc4b/hdl/axi_vdma_v6_3_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axi_vdma_0_0/sim/design_1_axi_vdma_0_0.vhd" \
-endlib
-makelib xcelium_lib/axis_infrastructure_v1_1_0 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/8713/hdl/axis_infrastructure_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/axis_register_slice_v1_1_26 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/aca3/hdl/axis_register_slice_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_in_0/hdl/tdata_design_1_axis_subset_converter_in_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_in_0/hdl/tuser_design_1_axis_subset_converter_in_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_in_0/hdl/tstrb_design_1_axis_subset_converter_in_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_in_0/hdl/tkeep_design_1_axis_subset_converter_in_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_in_0/hdl/tid_design_1_axis_subset_converter_in_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_in_0/hdl/tdest_design_1_axis_subset_converter_in_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_in_0/hdl/tlast_design_1_axis_subset_converter_in_0.v" \
-endlib
-makelib xcelium_lib/axis_subset_converter_v1_1_26 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/1676/hdl/axis_subset_converter_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_in_0/hdl/top_design_1_axis_subset_converter_in_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_in_0/sim/design_1_axis_subset_converter_in_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_out_0/hdl/tdata_design_1_axis_subset_converter_out_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_out_0/hdl/tuser_design_1_axis_subset_converter_out_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_out_0/hdl/tstrb_design_1_axis_subset_converter_out_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_out_0/hdl/tkeep_design_1_axis_subset_converter_out_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_out_0/hdl/tid_design_1_axis_subset_converter_out_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_out_0/hdl/tdest_design_1_axis_subset_converter_out_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_out_0/hdl/tlast_design_1_axis_subset_converter_out_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_out_0/hdl/top_design_1_axis_subset_converter_out_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axis_subset_converter_out_0/sim/design_1_axis_subset_converter_out_0.v" \
-endlib
-makelib xcelium_lib/xlconstant_v1_1_7 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/fcfc/hdl/xlconstant_v1_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_subset_converter_reset_0/sim/design_1_subset_converter_reset_0.v" \
-endlib
-makelib xcelium_lib/axi_lite_ipif_v3_0_4 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/66ea/hdl/axi_lite_ipif_v3_0_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/v_tc_v6_1_13 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/b92e/hdl/v_tc_v6_1_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/v_vid_in_axi4s_v4_0_9 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/b2aa/hdl/v_vid_in_axi4s_v4_0_vl_rfs.v" \
-endlib
-makelib xcelium_lib/v_axi4s_vid_out_v4_0_14 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/f733/hdl/v_axi4s_vid_out_v4_0_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_v_axi4s_vid_out_0_0/sim/design_1_v_axi4s_vid_out_0_0.v" \
-endlib
-makelib xcelium_lib/v_tc_v6_2_4 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/3e14/hdl/v_tc_v6_2_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_v_tc_in_0/sim/design_1_v_tc_in_0.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_v_tc_out_0/sim/design_1_v_tc_out_0.vhd" \
-endlib
-makelib xcelium_lib/v_vid_in_axi4s_v5_0_1 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/b872/hdl/v_vid_in_axi4s_v5_0_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_v_vid_in_axi4s_0_0/sim/design_1_v_vid_in_axi4s_0_0.v" \
-endlib
-makelib xcelium_lib/xlconcat_v2_1_4 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/4b67/hdl/xlconcat_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_xlconcat_0_0/sim/design_1_xlconcat_0_0.v" \
-endlib
-makelib xcelium_lib/interrupt_control_v3_1_4 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/a040/hdl/interrupt_control_v3_1_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/axi_gpio_v2_0_28 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/3ed9/hdl/axi_gpio_v2_0_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_axi_gpio_video_0/sim/design_1_axi_gpio_video_0.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_dvi2rgb_0_0/src/ila_refclk/sim/ila_refclk.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_dvi2rgb_0_0/src/ila_pixclk/sim/ila_pixclk.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0bb5/src/SyncBase.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0bb5/src/EEPROM_8b.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0bb5/src/TWI_SlaveCtl.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0bb5/src/GlitchFilter.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0bb5/src/SyncAsync.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0bb5/src/DVI_Constants.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0bb5/src/SyncAsyncReset.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0bb5/src/PhaseAlign.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0bb5/src/InputSERDES.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0bb5/src/ChannelBond.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0bb5/src/ResyncToBUFG.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0bb5/src/TMDS_Decoder.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0bb5/src/TMDS_Clocking.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/0bb5/src/dvi2rgb.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_dvi2rgb_0_0/sim/design_1_dvi2rgb_0_0.vhd" \
-endlib
-makelib xcelium_lib/proc_sys_reset_v5_0_13 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/8842/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_proc_sys_reset_0_0/sim/design_1_proc_sys_reset_0_0.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_proc_sys_reset_fclk0_0/sim/design_1_proc_sys_reset_fclk0_0.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_proc_sys_reset_fclk1_0/sim/design_1_proc_sys_reset_fclk1_0.vhd" \
-endlib
-makelib xcelium_lib/axi_vip_v1_1_12 -sv \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/1033/hdl/axi_vip_v1_1_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/processing_system7_vip_v1_0_14 -sv \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/5765/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_processing_system7_0_0/sim/design_1_processing_system7_0_0.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/d57c/src/ClockGen.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/d57c/src/OutputSERDES.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/d57c/src/TMDS_Encoder.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/d57c/src/rgb2dvi.vhd" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_rgb2dvi_1_0/sim/design_1_rgb2dvi_1_0.vhd" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/b48b/hdl/AUP_advanced_SoC_withBtn_v1_0_S00_AXI.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/b48b/hdl/AUP_advanced_SoC_withBtn_v1_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_AUP_advanced_SoC_wit_0_0/sim/design_1_AUP_advanced_SoC_wit_0_0.v" \
-endlib
-makelib xcelium_lib/axi_protocol_converter_v2_1_26 \
  "../../../../hw.gen/sources_1/bd/design_1/ipshared/90c8/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_auto_pc_0/sim/design_1_auto_pc_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_s00_regslice_0/sim/design_1_s00_regslice_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_s01_regslice_0/sim/design_1_s01_regslice_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_m00_regslice_0/sim/design_1_m00_regslice_0.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_auto_pc_1/sim/design_1_auto_pc_1.v" \
  "../../../../hw.gen/sources_1/bd/design_1/ip/design_1_auto_pc_2/sim/design_1_auto_pc_2.v" \
  "../../../../hw.gen/sources_1/bd/design_1/sim/design_1.v" \
-endlib
-makelib xcelium_lib/xil_defaultlib \
  glbl.v
-endlib

