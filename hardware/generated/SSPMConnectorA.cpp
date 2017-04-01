#include "SSPMConnectorA.h"

void SSPMConnectorA_t::init ( val_t rand_init ) {
  this->__srand(rand_init);
  SSPMConnectorA_sspmController__sRespReg.randomize(&__rand_seed);
  clk.len = 1;
  clk.cnt = clk.len;
  clk.values[0] = 0;
}


int SSPMConnectorA_t::clock ( dat_t<1> reset ) {
  uint32_t min = ((uint32_t)1<<31)-1;
  if (clk.cnt < min) min = clk.cnt;
  clk.cnt-=min;
  if (clk.cnt == 0) clock_lo( reset );
  if (clk.cnt == 0) clock_hi( reset );
  if (clk.cnt == 0) clk.cnt = clk.len;
  return min;
}


void SSPMConnectorA_t::print ( FILE* f ) {
}
void SSPMConnectorA_t::print ( std::ostream& s ) {
}


void SSPMConnectorA_t::dump_init ( FILE* f ) {
  fputs("$timescale 1ps $end\n", f);
  fputs("$scope module SSPMConnectorA $end\n", f);
  fputs("$var wire 1 \x21 clk $end\n", f);
  fputs("$var wire 1 \x22 io_connectorSignals_select $end\n", f);
  fputs("$var wire 1 \x25 io_connectorSignals_we $end\n", f);
  fputs("$var wire 1 \x26 io_superMode $end\n", f);
  fputs("$var wire 2 \x29 io_ocp_S_Resp $end\n", f);
  fputs("$var wire 3 \x2a io_ocp_M_Cmd $end\n", f);
  fputs("$var wire 4 \x2c io_ocp_M_ByteEn $end\n", f);
  fputs("$var wire 16 \x2d io_connectorSignals_addr $end\n", f);
  fputs("$var wire 32 \x2e io_connectorSignals_data_in $end\n", f);
  fputs("$var wire 32 \x2f io_ocp_S_Data $end\n", f);
  fputs("$var wire 32 \x30 io_ocp_M_Data $end\n", f);
  fputs("$var wire 32 \x31 io_connectorSignals_data_out $end\n", f);
  fputs("$var wire 32 \x32 io_ocp_M_Addr $end\n", f);
  fputs("$scope module sspmController $end\n", f);
  fputs("$var wire 1 \x23 io_select $end\n", f);
  fputs("$var wire 1 \x24 reset $end\n", f);
  fputs("$var wire 2 \x27 sRespReg $end\n", f);
  fputs("$var wire 2 \x28 io_SResp $end\n", f);
  fputs("$var wire 3 \x2b io_MCmd $end\n", f);
  fputs("$upscope $end\n", f);
  fputs("$upscope $end\n", f);
  fputs("$enddefinitions $end\n", f);
  fputs("$dumpvars\n", f);
  fputs("$end\n", f);
  fputs("#0\n", f);
  dat_dump<1>(f, clk, 0x21);
  dat_dump<1>(f, SSPMConnectorA__io_connectorSignals_select, 0x22);
  SSPMConnectorA__io_connectorSignals_select__prev = SSPMConnectorA__io_connectorSignals_select;
  dat_dump<1>(f, SSPMConnectorA_sspmController__io_select, 0x23);
  SSPMConnectorA_sspmController__io_select__prev = SSPMConnectorA_sspmController__io_select;
  dat_dump<1>(f, SSPMConnectorA_sspmController__reset, 0x24);
  SSPMConnectorA_sspmController__reset__prev = SSPMConnectorA_sspmController__reset;
  dat_dump<1>(f, SSPMConnectorA__io_connectorSignals_we, 0x25);
  SSPMConnectorA__io_connectorSignals_we__prev = SSPMConnectorA__io_connectorSignals_we;
  dat_dump<1>(f, SSPMConnectorA__io_superMode, 0x26);
  SSPMConnectorA__io_superMode__prev = SSPMConnectorA__io_superMode;
  dat_dump<1>(f, SSPMConnectorA_sspmController__sRespReg, 0x27);
  SSPMConnectorA_sspmController__sRespReg__prev = SSPMConnectorA_sspmController__sRespReg;
  dat_dump<1>(f, SSPMConnectorA_sspmController__io_SResp, 0x28);
  SSPMConnectorA_sspmController__io_SResp__prev = SSPMConnectorA_sspmController__io_SResp;
  dat_dump<1>(f, SSPMConnectorA__io_ocp_S_Resp, 0x29);
  SSPMConnectorA__io_ocp_S_Resp__prev = SSPMConnectorA__io_ocp_S_Resp;
  dat_dump<1>(f, SSPMConnectorA__io_ocp_M_Cmd, 0x2a);
  SSPMConnectorA__io_ocp_M_Cmd__prev = SSPMConnectorA__io_ocp_M_Cmd;
  dat_dump<1>(f, SSPMConnectorA_sspmController__io_MCmd, 0x2b);
  SSPMConnectorA_sspmController__io_MCmd__prev = SSPMConnectorA_sspmController__io_MCmd;
  dat_dump<1>(f, SSPMConnectorA__io_ocp_M_ByteEn, 0x2c);
  SSPMConnectorA__io_ocp_M_ByteEn__prev = SSPMConnectorA__io_ocp_M_ByteEn;
  dat_dump<1>(f, SSPMConnectorA__io_connectorSignals_addr, 0x2d);
  SSPMConnectorA__io_connectorSignals_addr__prev = SSPMConnectorA__io_connectorSignals_addr;
  dat_dump<1>(f, SSPMConnectorA__io_connectorSignals_data_in, 0x2e);
  SSPMConnectorA__io_connectorSignals_data_in__prev = SSPMConnectorA__io_connectorSignals_data_in;
  dat_dump<1>(f, SSPMConnectorA__io_ocp_S_Data, 0x2f);
  SSPMConnectorA__io_ocp_S_Data__prev = SSPMConnectorA__io_ocp_S_Data;
  dat_dump<1>(f, SSPMConnectorA__io_ocp_M_Data, 0x30);
  SSPMConnectorA__io_ocp_M_Data__prev = SSPMConnectorA__io_ocp_M_Data;
  dat_dump<1>(f, SSPMConnectorA__io_connectorSignals_data_out, 0x31);
  SSPMConnectorA__io_connectorSignals_data_out__prev = SSPMConnectorA__io_connectorSignals_data_out;
  dat_dump<1>(f, SSPMConnectorA__io_ocp_M_Addr, 0x32);
  SSPMConnectorA__io_ocp_M_Addr__prev = SSPMConnectorA__io_ocp_M_Addr;
}


void SSPMConnectorA_t::dump ( FILE* f, int t ) {
  if (t == 0) return dump_init(f);
  fprintf(f, "#%d\n", t << 1);
  if (clk.len == clk.cnt)  goto L0;
K0:  if (SSPMConnectorA__io_connectorSignals_select != SSPMConnectorA__io_connectorSignals_select__prev)  goto L1;
K1:  if (SSPMConnectorA_sspmController__io_select != SSPMConnectorA_sspmController__io_select__prev)  goto L2;
K2:  if (SSPMConnectorA_sspmController__reset != SSPMConnectorA_sspmController__reset__prev)  goto L3;
K3:  if (SSPMConnectorA__io_connectorSignals_we != SSPMConnectorA__io_connectorSignals_we__prev)  goto L4;
K4:  if (SSPMConnectorA__io_superMode != SSPMConnectorA__io_superMode__prev)  goto L5;
K5:  if (SSPMConnectorA_sspmController__sRespReg != SSPMConnectorA_sspmController__sRespReg__prev)  goto L6;
K6:  if (SSPMConnectorA_sspmController__io_SResp != SSPMConnectorA_sspmController__io_SResp__prev)  goto L7;
K7:  if (SSPMConnectorA__io_ocp_S_Resp != SSPMConnectorA__io_ocp_S_Resp__prev)  goto L8;
K8:  if (SSPMConnectorA__io_ocp_M_Cmd != SSPMConnectorA__io_ocp_M_Cmd__prev)  goto L9;
K9:  if (SSPMConnectorA_sspmController__io_MCmd != SSPMConnectorA_sspmController__io_MCmd__prev)  goto L10;
K10:  if (SSPMConnectorA__io_ocp_M_ByteEn != SSPMConnectorA__io_ocp_M_ByteEn__prev)  goto L11;
K11:  if (SSPMConnectorA__io_connectorSignals_addr != SSPMConnectorA__io_connectorSignals_addr__prev)  goto L12;
K12:  if (SSPMConnectorA__io_connectorSignals_data_in != SSPMConnectorA__io_connectorSignals_data_in__prev)  goto L13;
K13:  if (SSPMConnectorA__io_ocp_S_Data != SSPMConnectorA__io_ocp_S_Data__prev)  goto L14;
K14:  if (SSPMConnectorA__io_ocp_M_Data != SSPMConnectorA__io_ocp_M_Data__prev)  goto L15;
K15:  if (SSPMConnectorA__io_connectorSignals_data_out != SSPMConnectorA__io_connectorSignals_data_out__prev)  goto L16;
K16:  if (SSPMConnectorA__io_ocp_M_Addr != SSPMConnectorA__io_ocp_M_Addr__prev)  goto L17;
K17:  fprintf(f, "#%d\n", (t << 1) + 1);
  if (clk.len == clk.cnt)  goto Z0;
C0:  return;
L0:
  clk.values[0] = 1;
  dat_dump<1>(f, clk, 0x21);
  goto K0;
L1:
  SSPMConnectorA__io_connectorSignals_select__prev = SSPMConnectorA__io_connectorSignals_select;
  dat_dump<1>(f, SSPMConnectorA__io_connectorSignals_select, 0x22);
  goto K1;
L2:
  SSPMConnectorA_sspmController__io_select__prev = SSPMConnectorA_sspmController__io_select;
  dat_dump<1>(f, SSPMConnectorA_sspmController__io_select, 0x23);
  goto K2;
L3:
  SSPMConnectorA_sspmController__reset__prev = SSPMConnectorA_sspmController__reset;
  dat_dump<1>(f, SSPMConnectorA_sspmController__reset, 0x24);
  goto K3;
L4:
  SSPMConnectorA__io_connectorSignals_we__prev = SSPMConnectorA__io_connectorSignals_we;
  dat_dump<1>(f, SSPMConnectorA__io_connectorSignals_we, 0x25);
  goto K4;
L5:
  SSPMConnectorA__io_superMode__prev = SSPMConnectorA__io_superMode;
  dat_dump<1>(f, SSPMConnectorA__io_superMode, 0x26);
  goto K5;
L6:
  SSPMConnectorA_sspmController__sRespReg__prev = SSPMConnectorA_sspmController__sRespReg;
  dat_dump<1>(f, SSPMConnectorA_sspmController__sRespReg, 0x27);
  goto K6;
L7:
  SSPMConnectorA_sspmController__io_SResp__prev = SSPMConnectorA_sspmController__io_SResp;
  dat_dump<1>(f, SSPMConnectorA_sspmController__io_SResp, 0x28);
  goto K7;
L8:
  SSPMConnectorA__io_ocp_S_Resp__prev = SSPMConnectorA__io_ocp_S_Resp;
  dat_dump<1>(f, SSPMConnectorA__io_ocp_S_Resp, 0x29);
  goto K8;
L9:
  SSPMConnectorA__io_ocp_M_Cmd__prev = SSPMConnectorA__io_ocp_M_Cmd;
  dat_dump<1>(f, SSPMConnectorA__io_ocp_M_Cmd, 0x2a);
  goto K9;
L10:
  SSPMConnectorA_sspmController__io_MCmd__prev = SSPMConnectorA_sspmController__io_MCmd;
  dat_dump<1>(f, SSPMConnectorA_sspmController__io_MCmd, 0x2b);
  goto K10;
L11:
  SSPMConnectorA__io_ocp_M_ByteEn__prev = SSPMConnectorA__io_ocp_M_ByteEn;
  dat_dump<1>(f, SSPMConnectorA__io_ocp_M_ByteEn, 0x2c);
  goto K11;
L12:
  SSPMConnectorA__io_connectorSignals_addr__prev = SSPMConnectorA__io_connectorSignals_addr;
  dat_dump<1>(f, SSPMConnectorA__io_connectorSignals_addr, 0x2d);
  goto K12;
L13:
  SSPMConnectorA__io_connectorSignals_data_in__prev = SSPMConnectorA__io_connectorSignals_data_in;
  dat_dump<1>(f, SSPMConnectorA__io_connectorSignals_data_in, 0x2e);
  goto K13;
L14:
  SSPMConnectorA__io_ocp_S_Data__prev = SSPMConnectorA__io_ocp_S_Data;
  dat_dump<1>(f, SSPMConnectorA__io_ocp_S_Data, 0x2f);
  goto K14;
L15:
  SSPMConnectorA__io_ocp_M_Data__prev = SSPMConnectorA__io_ocp_M_Data;
  dat_dump<1>(f, SSPMConnectorA__io_ocp_M_Data, 0x30);
  goto K15;
L16:
  SSPMConnectorA__io_connectorSignals_data_out__prev = SSPMConnectorA__io_connectorSignals_data_out;
  dat_dump<1>(f, SSPMConnectorA__io_connectorSignals_data_out, 0x31);
  goto K16;
L17:
  SSPMConnectorA__io_ocp_M_Addr__prev = SSPMConnectorA__io_ocp_M_Addr;
  dat_dump<1>(f, SSPMConnectorA__io_ocp_M_Addr, 0x32);
  goto K17;
Z0:
  clk.values[0] = 0;
  dat_dump<1>(f, clk, 0x21);
  goto C0;
}




void SSPMConnectorA_t::clock_lo ( dat_t<1> reset, bool assert_fire ) {
  { SSPMConnectorA_sspmController__io_select.values[0] = SSPMConnectorA__io_connectorSignals_select.values[0];}
  val_t T0;
  T0 = SSPMConnectorA_sspmController__io_select.values[0] == 0x1L;
  { SSPMConnectorA_sspmController__io_MCmd.values[0] = SSPMConnectorA__io_ocp_M_Cmd.values[0];}
  val_t T1;
  T1 = SSPMConnectorA_sspmController__io_MCmd.values[0] == 0x1L;
  val_t T2;
  T2 = SSPMConnectorA_sspmController__io_MCmd.values[0] == 0x2L;
  val_t T3;
  { T3 = T2 | T1;}
  val_t T4;
  { T4 = T3 & T0;}
  val_t T5;
  { T5 = TERNARY(T4, 0x1L, 0x0L);}
  { SSPMConnectorA_sspmController__reset.values[0] = reset.values[0];}
  { T6.values[0] = TERNARY(SSPMConnectorA_sspmController__reset.values[0], 0x0L, T5);}
  { SSPMConnectorA_sspmController__io_SResp.values[0] = SSPMConnectorA_sspmController__sRespReg.values[0];}
  { SSPMConnectorA__io_ocp_S_Resp.values[0] = SSPMConnectorA_sspmController__io_SResp.values[0];}
  { SSPMConnectorA__io_ocp_S_Data.values[0] = SSPMConnectorA__io_connectorSignals_data_in.values[0];}
  { SSPMConnectorA__io_connectorSignals_data_out.values[0] = SSPMConnectorA__io_ocp_M_Data.values[0];}
  val_t T7;
  { T7 = SSPMConnectorA__io_ocp_M_Addr.values[0];}
  T7 = T7 & 0xffffL;
  { SSPMConnectorA__io_connectorSignals_addr.values[0] = T7;}
  val_t T8;
  T8 = (SSPMConnectorA__io_ocp_M_ByteEn.values[0] >> 0) & 1;
  { SSPMConnectorA__io_connectorSignals_we.values[0] = T8;}
}


void SSPMConnectorA_t::clock_hi ( dat_t<1> reset ) {
  dat_t<2> SSPMConnectorA_sspmController__sRespReg__shadow = T6;
  SSPMConnectorA_sspmController__sRespReg = T6;
}


void SSPMConnectorA_api_t::init_sim_data (  ) {
  sim_data.inputs.clear();
  sim_data.outputs.clear();
  sim_data.signals.clear();
  SSPMConnectorA_t* mod = dynamic_cast<SSPMConnectorA_t*>(module);
  assert(mod);
  sim_data.inputs.push_back(new dat_api<1>(&mod->SSPMConnectorA__io_superMode));
  sim_data.inputs.push_back(new dat_api<3>(&mod->SSPMConnectorA__io_ocp_M_Cmd));
  sim_data.inputs.push_back(new dat_api<32>(&mod->SSPMConnectorA__io_ocp_M_Addr));
  sim_data.inputs.push_back(new dat_api<32>(&mod->SSPMConnectorA__io_ocp_M_Data));
  sim_data.inputs.push_back(new dat_api<4>(&mod->SSPMConnectorA__io_ocp_M_ByteEn));
  sim_data.inputs.push_back(new dat_api<1>(&mod->SSPMConnectorA__io_connectorSignals_select));
  sim_data.inputs.push_back(new dat_api<32>(&mod->SSPMConnectorA__io_connectorSignals_data_in));
  sim_data.outputs.push_back(new dat_api<2>(&mod->SSPMConnectorA__io_ocp_S_Resp));
  sim_data.outputs.push_back(new dat_api<32>(&mod->SSPMConnectorA__io_ocp_S_Data));
  sim_data.outputs.push_back(new dat_api<32>(&mod->SSPMConnectorA__io_connectorSignals_data_out));
  sim_data.outputs.push_back(new dat_api<16>(&mod->SSPMConnectorA__io_connectorSignals_addr));
  sim_data.outputs.push_back(new dat_api<1>(&mod->SSPMConnectorA__io_connectorSignals_we));
  sim_data.signals.push_back(new dat_api<1>(&mod->SSPMConnectorA_sspmController__io_select));
  sim_data.signal_map["SSPMConnectorA.sspmController.io_select"] = 0;
  sim_data.signals.push_back(new dat_api<3>(&mod->SSPMConnectorA_sspmController__io_MCmd));
  sim_data.signal_map["SSPMConnectorA.sspmController.io_MCmd"] = 1;
  sim_data.signals.push_back(new dat_api<2>(&mod->SSPMConnectorA_sspmController__sRespReg));
  sim_data.signal_map["SSPMConnectorA.sspmController.sRespReg"] = 2;
  sim_data.signals.push_back(new dat_api<2>(&mod->SSPMConnectorA_sspmController__io_SResp));
  sim_data.signal_map["SSPMConnectorA.sspmController.io_SResp"] = 3;
  sim_data.clk_map["clk"] = new clk_api(&mod->clk);
}
