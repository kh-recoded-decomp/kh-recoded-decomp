#include "nitro/types.h"

extern signed char *gWirelessCardExchangeGlobals;
extern int SetWirelessConnectionState();

void ReturnWirelessConnectionToState2IfInRange3To7(void) {
  if (4 < ((*gWirelessCardExchangeGlobals + -3) * 0x1000000 >> 0x18 & 0xffU)) {
    return;
  }
  SetWirelessConnectionState(2);
}
