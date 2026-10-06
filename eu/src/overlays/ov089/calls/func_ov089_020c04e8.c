#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 func_ov039_020bc638();
extern u32 SetPopupConfirmMode();

void func_ov089_020c04e8(void) {
  u32 work;

  work = func_ov039_020bc638();
  PlaySoundEffect(0,1);
  SetPopupConfirmMode(work,0);
}
