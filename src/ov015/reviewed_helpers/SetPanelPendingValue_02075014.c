#include "nitro/types.h"

extern u8 panelState_0207e980[];
#define pendingValue (*(u32 *)(panelState_0207e980 + 0x4c))

void SetPanelPendingValue_02075014(u32 value)

{
  pendingValue = value;
  return;
}
