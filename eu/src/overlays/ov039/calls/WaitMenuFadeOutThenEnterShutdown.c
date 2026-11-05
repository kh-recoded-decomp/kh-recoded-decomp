#include "nitro/types.h"

extern unsigned int data_ov039_020bea20;
extern unsigned int SetMenuPhase();
extern unsigned int UpdatePrimaryMenuSubOverlay();
extern unsigned int UpdateSecondaryMenuSubOverlay();

void WaitMenuFadeOutThenEnterShutdown(void) {
  int work;

  work = data_ov039_020bea20;
  UpdatePrimaryMenuSubOverlay(*(unsigned int *)(data_ov039_020bea20 + 0xc998));
  UpdateSecondaryMenuSubOverlay(*(unsigned int *)(work + 0xc99c));
  if (((u32)*(int *)(work + 0xc9e8) << 29) >> 31 == 0) {
    return;
  }
  SetMenuPhase(8);
}
