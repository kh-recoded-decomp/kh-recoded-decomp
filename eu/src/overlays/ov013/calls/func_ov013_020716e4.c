#include "nitro/types.h"

typedef unsigned int code();

extern signed char *data_ov013_02074ce0;
extern u8 gPanelExitModeResolver;
extern u8 gPanelMenuStateHandlers;

void func_ov013_020716e4(char nextState) {
  if (*data_ov013_02074ce0 != -1) {
    (**(code **)(&gPanelMenuStateHandlers + *data_ov013_02074ce0 * 0xc))();
  }
  *data_ov013_02074ce0 = nextState;
  (**(code **)(&gPanelExitModeResolver + (short)*data_ov013_02074ce0 * 0xc))();
}
