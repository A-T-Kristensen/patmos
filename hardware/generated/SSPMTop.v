module SSPMConnector(
    //input  io_superMode
    //input [2:0] io_ocp_M_Cmd
    //input [31:0] io_ocp_M_Addr
    input [31:0] io_ocp_M_Data,
    //input [3:0] io_ocp_M_ByteEn
    //output[1:0] io_ocp_S_Resp
    output[31:0] io_ocp_S_Data,
    output[31:0] io_backbone_inbound,
    input [31:0] io_backbone_outbound
);



`ifndef SYNTHESIS
// synthesis translate_off
//  assign io_ocp_S_Resp = {1{$random}};
// synthesis translate_on
`endif
  assign io_backbone_inbound = io_ocp_M_Data;
  assign io_ocp_S_Data = io_backbone_outbound;
endmodule

module SSPMTop(
    input [31:0] io_in_2,
    input [31:0] io_in_1,
    input [31:0] io_in_0,
    output[31:0] io_out,
    input [1:0] io_select
);

  wire[31:0] T0;
  wire[31:0] T1;
  wire T2;
  wire[1:0] T3;
  wire T4;
  wire[31:0] SSPMConnector_io_ocp_S_Data;
  wire[31:0] SSPMConnector_io_backbone_inbound;
  wire[31:0] SSPMConnector_1_io_ocp_S_Data;
  wire[31:0] SSPMConnector_1_io_backbone_inbound;
  wire[31:0] SSPMConnector_2_io_ocp_S_Data;
  wire[31:0] SSPMConnector_2_io_backbone_inbound;


  assign io_out = T0;
  assign T0 = T4 ? SSPMConnector_2_io_ocp_S_Data : T1;
  assign T1 = T2 ? SSPMConnector_1_io_ocp_S_Data : SSPMConnector_io_ocp_S_Data;
  assign T2 = T3[1'h0:1'h0];
  assign T3 = io_select;
  assign T4 = T3[1'h1:1'h1];
  SSPMConnector SSPMConnector(
       //.io_superMode(  )
       //.io_ocp_M_Cmd(  )
       //.io_ocp_M_Addr(  )
       .io_ocp_M_Data( io_in_0 ),
       //.io_ocp_M_ByteEn(  )
       //.io_ocp_S_Resp(  )
       .io_ocp_S_Data( SSPMConnector_io_ocp_S_Data ),
       .io_backbone_inbound( SSPMConnector_io_backbone_inbound ),
       .io_backbone_outbound( SSPMConnector_io_backbone_inbound )
  );
  SSPMConnector SSPMConnector_1(
       //.io_superMode(  )
       //.io_ocp_M_Cmd(  )
       //.io_ocp_M_Addr(  )
       .io_ocp_M_Data( io_in_1 ),
       //.io_ocp_M_ByteEn(  )
       //.io_ocp_S_Resp(  )
       .io_ocp_S_Data( SSPMConnector_1_io_ocp_S_Data ),
       .io_backbone_inbound( SSPMConnector_1_io_backbone_inbound ),
       .io_backbone_outbound( SSPMConnector_1_io_backbone_inbound )
  );
  SSPMConnector SSPMConnector_2(
       //.io_superMode(  )
       //.io_ocp_M_Cmd(  )
       //.io_ocp_M_Addr(  )
       .io_ocp_M_Data( io_in_2 ),
       //.io_ocp_M_ByteEn(  )
       //.io_ocp_S_Resp(  )
       .io_ocp_S_Data( SSPMConnector_2_io_ocp_S_Data ),
       .io_backbone_inbound( SSPMConnector_2_io_backbone_inbound ),
       .io_backbone_outbound( SSPMConnector_2_io_backbone_inbound )
  );
endmodule

