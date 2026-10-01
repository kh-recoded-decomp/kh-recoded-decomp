#include "nitro/types.h"

extern u8 panelState_0207e980[];
#define transitionMode (*(u32 *)(panelState_0207e980 + 0x50))

void SetPanelTransitionMode_020737c4(u32 mode)

{
  transitionMode = mode;
  return;
}
