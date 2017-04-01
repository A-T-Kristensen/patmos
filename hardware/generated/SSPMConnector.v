module SSPMController(
    input [2:0] io_MCmd,
    input  io_select,
    output[1:0] io_SResp
);



`ifndef SYNTHESIS
// synthesis translate_off
  assign io_SResp = {1{$random}};
// synthesis translate_on
`endif
endmodule

module SSPMConnector(
    input  io_superMode,
    input [2:0] io_ocp_M_Cmd,
    input [31:0] io_ocp_M_Addr,
    input [31:0] io_ocp_M_Data,
    input [3:0] io_ocp_M_ByteEn,
    output[1:0] io_ocp_S_Resp,
    output[31:0] io_ocp_S_Data,
    input  io_connectorSignals_select,
    input [31:0] io_connectorSignals_data_in,
    output[31:0] io_connectorSignals_data_out,
    output[15:0] io_connectorSignals_addr,
    output io_connectorSignals_we
);

  wire T0;
  wire[15:0] T1;
  wire[1:0] sspmController_io_SResp;


  assign io_connectorSignals_we = T0;
  assign T0 = io_ocp_M_ByteEn[1'h0:1'h0];
  assign io_connectorSignals_addr = T1;
  assign T1 = io_ocp_M_Addr[4'hf:1'h0];
  assign io_connectorSignals_data_out = io_ocp_M_Data;
  assign io_ocp_S_Data = io_connectorSignals_data_in;
  assign io_ocp_S_Resp = sspmController_io_SResp;
  SSPMController sspmController(
       .io_MCmd( io_ocp_M_Cmd ),
       .io_select( io_connectorSignals_select ),
       .io_SResp( sspmController_io_SResp )
  );
`ifndef SYNTHESIS
// synthesis translate_off
    assign sspmController.io_SResp = {1{$random}};
// synthesis translate_on
`endif
endmodule

