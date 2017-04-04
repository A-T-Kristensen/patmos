#ifndef __SSPMConnector__
#define __SSPMConnector__

#include "emulator.h"

class SSPMConnector_t : public mod_t {
 private:
  val_t __rand_seed;
  void __srand(val_t seed) { __rand_seed = seed; }
  val_t __rand_val() { return ::__rand_val(&__rand_seed); }
 public:
  dat_t<1> SSPMConnector__io_connectorSignals_we;
  dat_t<1> SSPMConnector__io_connectorSignals_select;
  dat_t<1> SSPMConnector__io_superMode;
  dat_t<2> SSPMConnector_sspmController__io_SResp;
  dat_t<2> SSPMConnector__io_ocp_S_Resp;
  dat_t<3> SSPMConnector__io_ocp_M_Cmd;
  dat_t<4> SSPMConnector__io_ocp_M_ByteEn;
  dat_t<16> SSPMConnector__io_connectorSignals_addr;
  dat_t<32> SSPMConnector__io_connectorSignals_data_in;
  dat_t<32> SSPMConnector__io_ocp_S_Data;
  dat_t<32> SSPMConnector__io_ocp_M_Data;
  dat_t<32> SSPMConnector__io_connectorSignals_data_out;
  dat_t<32> SSPMConnector__io_ocp_M_Addr;
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
class SSPMConnector_api_t : public emul_api_t {
 public:
  SSPMConnector_api_t(mod_t* m) : emul_api_t(m) { }
  void init_sim_data();
};

#endif