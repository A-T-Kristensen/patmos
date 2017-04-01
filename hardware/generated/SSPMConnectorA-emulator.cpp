#include "SSPMConnectorA.h"

int main (int argc, char* argv[]) {
  SSPMConnectorA_t module;
  SSPMConnectorA_api_t api(&module);
  module.init();
  api.init_sim_data();
  FILE *f = fopen("generated//SSPMConnectorA.vcd", "w");
  module.set_dumpfile(f);
  while(!api.exit()) api.tick();
  if (f) fclose(f);
}
