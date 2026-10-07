#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 GetActiveMenuScene();
extern u32 SetPopupConfirmMode();

void func_ov089_020c04e8(void) {
  u32 work;

  work = GetActiveMenuScene();
  PlaySoundEffect(0,1);
  SetPopupConfirmMode(work,0);
}
