#include "nitro/types.h"

typedef unsigned int code();

extern signed char *gWirelessCardExchangeGlobals;
extern u8 gWirelessStateInitCallback;
extern u8 gWirelessStateHandlers;

void SetWirelessConnectionState(char nextState) {
  if (*gWirelessCardExchangeGlobals != -1) {
    (**(code **)(&gWirelessStateHandlers + *gWirelessCardExchangeGlobals * 0xc))();
  }
  *gWirelessCardExchangeGlobals = nextState;
  (**(code **)(&gWirelessStateInitCallback + (short)*gWirelessCardExchangeGlobals * 0xc))();
}
