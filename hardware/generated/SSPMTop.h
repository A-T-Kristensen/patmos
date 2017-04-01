#ifndef __SSPMTop__
#define __SSPMTop__

#include "emulator.h"

class SSPMTop_t : public mod_t {
 private:
  val_t __rand_seed;
  void __srand(val_t seed) { __rand_seed = seed; }
  val_t __rand_val() { return ::__rand_val(&__rand_seed); }
 public:
  dat_t<2> SSPMTop_SSPMConnector_2__io_ocp_S_Resp;
  dat_t<2> SSPMTop_SSPMConnector_1__io_ocp_S_Resp;
  dat_t<2> SSPMTop_SSPMConnector__io_ocp_S_Resp;
  dat_t<2> SSPMTop__io_select;
  dat_t<32> SSPMTop__io_in_0;
  dat_t<32> SSPMTop_SSPMConnector__io_ocp_M_Data;
  dat_t<32> SSPMTop_SSPMConnector__io_backbone_inbound;
  dat_t<32> SSPMTop_SSPMConnector__io_backbone_outbound;
  dat_t<32> SSPMTop_SSPMConnector__io_ocp_S_Data;
  dat_t<32> SSPMTop__io_in_1;
  dat_t<32> SSPMTop_SSPMConnector_1__io_ocp_M_Data;
  dat_t<32> SSPMTop_SSPMConnector_1__io_backbone_inbound;
  dat_t<32> SSPMTop_SSPMConnector_1__io_backbone_outbound;
  dat_t<32> SSPMTop_SSPMConnector_1__io_ocp_S_Data;
  dat_t<32> SSPMTop__io_in_2;
  dat_t<32> SSPMTop_SSPMConnector_2__io_ocp_M_Data;
  dat_t<32> SSPMTop_SSPMConnector_2__io_backbone_inbound;
  dat_t<32> SSPMTop_SSPMConnector_2__io_backbone_outbound;
  dat_t<32> SSPMTop_SSPMConnector_2__io_ocp_S_Data;
  dat_t<32> SSPMTop__io_out;
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
class SSPMTop_api_t : public emul_api_t {
 public:
  SSPMTop_api_t(mod_t* m) : emul_api_t(m) { }
  void init_sim_data();
};

#endif
