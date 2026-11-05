#include "nitro/types.h"

typedef unsigned int code();

extern signed char *data_ov015_0207e960;
extern u8 gPanelExitResetCallback;
extern u8 gLinkPanelStateHandlers;

void SetWirelessMenuState(char nextState) {
  if (*data_ov015_0207e960 != -1) {
    (**(code **)(&gLinkPanelStateHandlers + *data_ov015_0207e960 * 0xc))();
  }
  *data_ov015_0207e960 = nextState;
  (**(code **)(&gPanelExitResetCallback + (short)*data_ov015_0207e960 * 0xc))();
}
