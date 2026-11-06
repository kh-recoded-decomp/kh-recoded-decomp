#include "nitro/types.h"

extern unsigned int gMenuOverlayWork;
extern unsigned int SetMenuPhase();
extern unsigned int SetMenuInputEnabled();
extern unsigned int UpdatePrimaryMenuSubOverlay();
extern unsigned int UpdateSecondaryMenuSubOverlay();

void WaitMenuFadeInThenEnableInput(void) {
  int work;

  work = gMenuOverlayWork;
  UpdatePrimaryMenuSubOverlay(*(unsigned int *)(gMenuOverlayWork + 0xc998));
  UpdateSecondaryMenuSubOverlay(*(unsigned int *)(work + 0xc99c));
  if (((u32)*(int *)(work + 0xc9e8) << 29) >> 31 == 0) {
    return;
  }
  *(unsigned int *)(work + 0xca0c) = 0;
  SetMenuInputEnabled(1);
  SetMenuPhase(3);
}
