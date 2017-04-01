module SSPMController(input clk, input reset,
    input [2:0] io_MCmd,
    input  io_select,
    output[1:0] io_SResp
);

  reg [1:0] sRespReg;
  wire[1:0] T6;
  wire[1:0] T0;
  wire T1;
  wire T2;
  wire T3;
  wire T4;
  wire T5;

`ifndef SYNTHESIS
// synthesis translate_off
  integer initvar;
  initial begin
    #0.002;
    sRespReg = {1{$random}};
  end
// synthesis translate_on
`endif

  assign io_SResp = sRespReg;
  assign T6 = reset ? 2'h0 : T0;
  assign T0 = T1 ? 2'h1 : 2'h0;
  assign T1 = T3 & T2;
  assign T2 = io_select == 1'h1;
  assign T3 = T5 | T4;
  assign T4 = io_MCmd == 3'h1;
  assign T5 = io_MCmd == 3'h2;

  always @(posedge clk) begin
    if(reset) begin
      sRespReg <= 2'h0;
    end else if(T1) begin
      sRespReg <= 2'h1;
    end else begin
      sRespReg <= 2'h0;
    end
  end
endmodule

module SSPMConnectorA(input clk, input reset,
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
  SSPMController sspmController(.clk(clk), .reset(reset),
       .io_MCmd( io_ocp_M_Cmd ),
       .io_select( io_connectorSignals_select ),
       .io_SResp( sspmController_io_SResp )
  );
endmodule

