#include "SSPMTop.h"

void SSPMTop_t::init ( val_t rand_init ) {
  this->__srand(rand_init);
  clk.len = 1;
  clk.cnt = clk.len;
  clk.values[0] = 0;
}


int SSPMTop_t::clock ( dat_t<1> reset ) {
  uint32_t min = ((uint32_t)1<<31)-1;
  if (clk.cnt < min) min = clk.cnt;
  clk.cnt-=min;
  if (clk.cnt == 0) clock_lo( reset );
  if (clk.cnt == 0) clock_hi( reset );
  if (clk.cnt == 0) clk.cnt = clk.len;
  return min;
}


void SSPMTop_t::print ( FILE* f ) {
}
void SSPMTop_t::print ( std::ostream& s ) {
}


void SSPMTop_t::dump_init ( FILE* f ) {
}


void SSPMTop_t::dump ( FILE* f, int t ) {
}




void SSPMTop_t::clock_lo ( dat_t<1> reset, bool assert_fire ) {
  { val_t __r = this->__rand_val(); SSPMTop_SSPMConnector_2__io_ocp_S_Resp.values[0] = __r;}
  SSPMTop_SSPMConnector_2__io_ocp_S_Resp.values[0] = SSPMTop_SSPMConnector_2__io_ocp_S_Resp.values[0] & 0x3L;
  { val_t __r = this->__rand_val(); SSPMTop_SSPMConnector_1__io_ocp_S_Resp.values[0] = __r;}
  SSPMTop_SSPMConnector_1__io_ocp_S_Resp.values[0] = SSPMTop_SSPMConnector_1__io_ocp_S_Resp.values[0] & 0x3L;
  { val_t __r = this->__rand_val(); SSPMTop_SSPMConnector__io_ocp_S_Resp.values[0] = __r;}
  SSPMTop_SSPMConnector__io_ocp_S_Resp.values[0] = SSPMTop_SSPMConnector__io_ocp_S_Resp.values[0] & 0x3L;
  { SSPMTop_SSPMConnector__io_ocp_M_Data.values[0] = SSPMTop__io_in_0.values[0];}
  { SSPMTop_SSPMConnector__io_backbone_inbound.values[0] = SSPMTop_SSPMConnector__io_ocp_M_Data.values[0];}
  { SSPMTop_SSPMConnector__io_backbone_outbound.values[0] = SSPMTop_SSPMConnector__io_backbone_inbound.values[0];}
  { SSPMTop_SSPMConnector__io_ocp_S_Data.values[0] = SSPMTop_SSPMConnector__io_backbone_outbound.values[0];}
  { SSPMTop_SSPMConnector_1__io_ocp_M_Data.values[0] = SSPMTop__io_in_1.values[0];}
  { SSPMTop_SSPMConnector_1__io_backbone_inbound.values[0] = SSPMTop_SSPMConnector_1__io_ocp_M_Data.values[0];}
  { SSPMTop_SSPMConnector_1__io_backbone_outbound.values[0] = SSPMTop_SSPMConnector_1__io_backbone_inbound.values[0];}
  { SSPMTop_SSPMConnector_1__io_ocp_S_Data.values[0] = SSPMTop_SSPMConnector_1__io_backbone_outbound.values[0];}
  val_t T0;
  T0 = (SSPMTop__io_select.values[0] >> 0) & 1;
  val_t T1;
  { T1 = TERNARY_1(T0, SSPMTop_SSPMConnector_1__io_ocp_S_Data.values[0], SSPMTop_SSPMConnector__io_ocp_S_Data.values[0]);}
  { SSPMTop_SSPMConnector_2__io_ocp_M_Data.values[0] = SSPMTop__io_in_2.values[0];}
  { SSPMTop_SSPMConnector_2__io_backbone_inbound.values[0] = SSPMTop_SSPMConnector_2__io_ocp_M_Data.values[0];}
  { SSPMTop_SSPMConnector_2__io_backbone_outbound.values[0] = SSPMTop_SSPMConnector_2__io_backbone_inbound.values[0];}
  { SSPMTop_SSPMConnector_2__io_ocp_S_Data.values[0] = SSPMTop_SSPMConnector_2__io_backbone_outbound.values[0];}
  val_t T2;
  T2 = (SSPMTop__io_select.values[0] >> 1) & 1;
  val_t T3;
  { T3 = TERNARY_1(T2, SSPMTop_SSPMConnector_2__io_ocp_S_Data.values[0], T1);}
  { SSPMTop__io_out.values[0] = T3;}
}


void SSPMTop_t::clock_hi ( dat_t<1> reset ) {
}


void SSPMTop_api_t::init_sim_data (  ) {
  sim_data.inputs.clear();
  sim_data.outputs.clear();
  sim_data.signals.clear();
  SSPMTop_t* mod = dynamic_cast<SSPMTop_t*>(module);
  assert(mod);
  sim_data.inputs.push_back(new dat_api<32>(&mod->SSPMTop__io_in_2));
  sim_data.inputs.push_back(new dat_api<32>(&mod->SSPMTop__io_in_1));
  sim_data.inputs.push_back(new dat_api<32>(&mod->SSPMTop__io_in_0));
  sim_data.inputs.push_back(new dat_api<2>(&mod->SSPMTop__io_select));
  sim_data.outputs.push_back(new dat_api<32>(&mod->SSPMTop__io_out));
  sim_data.signals.push_back(new dat_api<32>(&mod->SSPMTop_SSPMConnector__io_ocp_M_Data));
  sim_data.signal_map["SSPMTop.SSPMConnector.io_ocp_M_Data"] = 0;
  sim_data.signals.push_back(new dat_api<32>(&mod->SSPMTop_SSPMConnector__io_backbone_inbound));
  sim_data.signal_map["SSPMTop.SSPMConnector.io_backbone_inbound"] = 1;
  sim_data.signals.push_back(new dat_api<32>(&mod->SSPMTop_SSPMConnector__io_backbone_outbound));
  sim_data.signal_map["SSPMTop.SSPMConnector.io_backbone_outbound"] = 2;
  sim_data.signals.push_back(new dat_api<32>(&mod->SSPMTop_SSPMConnector__io_ocp_S_Data));
  sim_data.signal_map["SSPMTop.SSPMConnector.io_ocp_S_Data"] = 3;
  sim_data.signals.push_back(new dat_api<32>(&mod->SSPMTop_SSPMConnector_1__io_ocp_M_Data));
  sim_data.signal_map["SSPMTop.SSPMConnector_1.io_ocp_M_Data"] = 4;
  sim_data.signals.push_back(new dat_api<32>(&mod->SSPMTop_SSPMConnector_1__io_backbone_inbound));
  sim_data.signal_map["SSPMTop.SSPMConnector_1.io_backbone_inbound"] = 5;
  sim_data.signals.push_back(new dat_api<32>(&mod->SSPMTop_SSPMConnector_1__io_backbone_outbound));
  sim_data.signal_map["SSPMTop.SSPMConnector_1.io_backbone_outbound"] = 6;
  sim_data.signals.push_back(new dat_api<32>(&mod->SSPMTop_SSPMConnector_1__io_ocp_S_Data));
  sim_data.signal_map["SSPMTop.SSPMConnector_1.io_ocp_S_Data"] = 7;
  sim_data.signals.push_back(new dat_api<32>(&mod->SSPMTop_SSPMConnector_2__io_ocp_M_Data));
  sim_data.signal_map["SSPMTop.SSPMConnector_2.io_ocp_M_Data"] = 8;
  sim_data.signals.push_back(new dat_api<32>(&mod->SSPMTop_SSPMConnector_2__io_backbone_inbound));
  sim_data.signal_map["SSPMTop.SSPMConnector_2.io_backbone_inbound"] = 9;
  sim_data.signals.push_back(new dat_api<32>(&mod->SSPMTop_SSPMConnector_2__io_backbone_outbound));
  sim_data.signal_map["SSPMTop.SSPMConnector_2.io_backbone_outbound"] = 10;
  sim_data.signals.push_back(new dat_api<32>(&mod->SSPMTop_SSPMConnector_2__io_ocp_S_Data));
  sim_data.signal_map["SSPMTop.SSPMConnector_2.io_ocp_S_Data"] = 11;
  sim_data.clk_map["clk"] = new clk_api(&mod->clk);
}
