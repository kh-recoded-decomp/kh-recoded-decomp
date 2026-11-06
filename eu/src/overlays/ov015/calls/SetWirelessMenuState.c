#include "nitro/types.h"

typedef unsigned int code();

extern signed char *gWirelessMenuWork;
extern u8 gPanelExitResetCallback;
extern u8 gLinkPanelStateHandlers;

void SetWirelessMenuState(char nextState) {
  if (*gWirelessMenuWork != -1) {
    (**(code **)(&gLinkPanelStateHandlers + *gWirelessMenuWork * 0xc))();
  }
  *gWirelessMenuWork = nextState;
  (**(code **)(&gPanelExitResetCallback + (short)*gWirelessMenuWork * 0xc))();
}
