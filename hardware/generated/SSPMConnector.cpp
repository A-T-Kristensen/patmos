#include "SSPMConnector.h"

void SSPMConnector_t::init ( val_t rand_init ) {
  this->__srand(rand_init);
   SSPMConnector_sspmController__io_SResp.randomize(&__rand_seed);
  clk.len = 1;
  clk.cnt = clk.len;
  clk.values[0] = 0;
}


int SSPMConnector_t::clock ( dat_t<1> reset ) {
  uint32_t min = ((uint32_t)1<<31)-1;
  if (clk.cnt < min) min = clk.cnt;
  clk.cnt-=min;
  if (clk.cnt == 0) clock_lo( reset );
  if (clk.cnt == 0) clock_hi( reset );
  if (clk.cnt == 0) clk.cnt = clk.len;
  return min;
}


void SSPMConnector_t::print ( FILE* f ) {
}
void SSPMConnector_t::print ( std::ostream& s ) {
}


void SSPMConnector_t::dump_init ( FILE* f ) {
}


void SSPMConnector_t::dump ( FILE* f, int t ) {
}




void SSPMConnector_t::clock_lo ( dat_t<1> reset, bool assert_fire ) {
  { val_t __r = this->__rand_val(); SSPMConnector_sspmController__io_SResp.values[0] = __r;}
  SSPMConnector_sspmController__io_SResp.values[0] = SSPMConnector_sspmController__io_SResp.values[0] & 0x3L;
  { SSPMConnector__io_ocp_S_Resp.values[0] = SSPMConnector_sspmController__io_SResp.values[0];}
  { SSPMConnector__io_ocp_S_Data.values[0] = SSPMConnector__io_connectorSignals_data_in.values[0];}
  { SSPMConnector__io_connectorSignals_data_out.values[0] = SSPMConnector__io_ocp_M_Data.values[0];}
  val_t T0;
  { T0 = SSPMConnector__io_ocp_M_Addr.values[0];}
  T0 = T0 & 0xffffL;
  { SSPMConnector__io_connectorSignals_addr.values[0] = T0;}
  val_t T1;
  T1 = (SSPMConnector__io_ocp_M_ByteEn.values[0] >> 0) & 1;
  { SSPMConnector__io_connectorSignals_we.values[0] = T1;}
}


void SSPMConnector_t::clock_hi ( dat_t<1> reset ) {
}


void SSPMConnector_api_t::init_sim_data (  ) {
  sim_data.inputs.clear();
  sim_data.outputs.clear();
  sim_data.signals.clear();
  SSPMConnector_t* mod = dynamic_cast<SSPMConnector_t*>(module);
  assert(mod);
  sim_data.inputs.push_back(new dat_api<1>(&mod->SSPMConnector__io_superMode));
  sim_data.inputs.push_back(new dat_api<3>(&mod->SSPMConnector__io_ocp_M_Cmd));
  sim_data.inputs.push_back(new dat_api<32>(&mod->SSPMConnector__io_ocp_M_Addr));
  sim_data.inputs.push_back(new dat_api<32>(&mod->SSPMConnector__io_ocp_M_Data));
  sim_data.inputs.push_back(new dat_api<4>(&mod->SSPMConnector__io_ocp_M_ByteEn));
  sim_data.inputs.push_back(new dat_api<1>(&mod->SSPMConnector__io_connectorSignals_select));
  sim_data.inputs.push_back(new dat_api<32>(&mod->SSPMConnector__io_connectorSignals_data_in));
  sim_data.outputs.push_back(new dat_api<2>(&mod->SSPMConnector__io_ocp_S_Resp));
  sim_data.outputs.push_back(new dat_api<32>(&mod->SSPMConnector__io_ocp_S_Data));
  sim_data.outputs.push_back(new dat_api<32>(&mod->SSPMConnector__io_connectorSignals_data_out));
  sim_data.outputs.push_back(new dat_api<16>(&mod->SSPMConnector__io_connectorSignals_addr));
  sim_data.outputs.push_back(new dat_api<1>(&mod->SSPMConnector__io_connectorSignals_we));
  sim_data.clk_map["clk"] = new clk_api(&mod->clk);
}
