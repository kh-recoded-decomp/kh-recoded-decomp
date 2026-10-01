#include "nitro/types.h"

extern u8 panelState_0207e980[];
#define transitionMode (*(u32 *)(panelState_0207e980 + 0x50))

u32 GetPanelTransitionMode_020748e4(void)

{
  return transitionMode;
}
