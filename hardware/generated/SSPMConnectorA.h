#ifndef __SSPMConnectorA__
#define __SSPMConnectorA__

#include "emulator.h"

class SSPMConnectorA_t : public mod_t {
 private:
  val_t __rand_seed;
  void __srand(val_t seed) { __rand_seed = seed; }
  val_t __rand_val() { return ::__rand_val(&__rand_seed); }
 public:
  dat_t<1> SSPMConnectorA__io_connectorSignals_select;
  dat_t<1> SSPMConnectorA_sspmController__io_select;
  dat_t<1> reset;
  dat_t<1> SSPMConnectorA_sspmController__reset;
  dat_t<1> SSPMConnectorA__io_connectorSignals_we;
  dat_t<1> SSPMConnectorA__io_superMode;
  dat_t<2> T6;
  dat_t<2> SSPMConnectorA_sspmController__sRespReg;
  dat_t<2> SSPMConnectorA_sspmController__io_SResp;
  dat_t<2> SSPMConnectorA__io_ocp_S_Resp;
  dat_t<3> SSPMConnectorA__io_ocp_M_Cmd;
  dat_t<3> SSPMConnectorA_sspmController__io_MCmd;
  dat_t<4> SSPMConnectorA__io_ocp_M_ByteEn;
  dat_t<16> SSPMConnectorA__io_connectorSignals_addr;
  dat_t<32> SSPMConnectorA__io_connectorSignals_data_in;
  dat_t<32> SSPMConnectorA__io_ocp_S_Data;
  dat_t<32> SSPMConnectorA__io_ocp_M_Data;
  dat_t<32> SSPMConnectorA__io_connectorSignals_data_out;
  dat_t<32> SSPMConnectorA__io_ocp_M_Addr;
  dat_t<1> SSPMConnectorA__io_connectorSignals_select__prev;
  dat_t<1> SSPMConnectorA_sspmController__io_select__prev;
  dat_t<1> SSPMConnectorA_sspmController__reset__prev;
  dat_t<1> SSPMConnectorA__io_connectorSignals_we__prev;
  dat_t<1> SSPMConnectorA__io_superMode__prev;
  dat_t<2> SSPMConnectorA_sspmController__sRespReg__prev;
  dat_t<2> SSPMConnectorA_sspmController__io_SResp__prev;
  dat_t<2> SSPMConnectorA__io_ocp_S_Resp__prev;
  dat_t<3> SSPMConnectorA__io_ocp_M_Cmd__prev;
  dat_t<3> SSPMConnectorA_sspmController__io_MCmd__prev;
  dat_t<4> SSPMConnectorA__io_ocp_M_ByteEn__prev;
  dat_t<16> SSPMConnectorA__io_connectorSignals_addr__prev;
  dat_t<32> SSPMConnectorA__io_connectorSignals_data_in__prev;
  dat_t<32> SSPMConnectorA__io_ocp_S_Data__prev;
  dat_t<32> SSPMConnectorA__io_ocp_M_Data__prev;
  dat_t<32> SSPMConnectorA__io_connectorSignals_data_out__prev;
  dat_t<32> SSPMConnectorA__io_ocp_M_Addr__prev;
  clk_t clk;

  void init ( val_t rand_init = 0 );
  void clock_lo ( dat_t<1> reset, bool assert_fire=true );
  void clock_hi ( dat_t<1> reset );
  int clock ( dat_t<1> reset );
  void print ( FILE* f );
  void print ( std::ostream& s );
  void dump ( FILE* f, int t );
  void dump_init ( FILE* f );

};

#include "emul_api.h"
class SSPMConnectorA_api_t : public emul_api_t {
 public:
  SSPMConnectorA_api_t(mod_t* m) : emul_api_t(m) { }
  void init_sim_data();
};

#endif
