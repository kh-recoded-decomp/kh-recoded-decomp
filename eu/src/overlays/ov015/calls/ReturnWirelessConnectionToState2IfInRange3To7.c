#include "nitro/types.h"

extern signed char *data_ov015_0207e964;
extern int SetWirelessConnectionState();

void ReturnWirelessConnectionToState2IfInRange3To7(void) {
  if (4 < ((*data_ov015_0207e964 + -3) * 0x1000000 >> 0x18 & 0xffU)) {
    return;
  }
  SetWirelessConnectionState(2);
}
