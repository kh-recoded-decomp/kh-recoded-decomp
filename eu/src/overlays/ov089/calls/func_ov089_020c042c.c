#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 GetActiveMenuScene();
extern u32 ClosePopupWindow();
extern u32 SetPopupConfirmMode();

void func_ov089_020c042c(void) {
  int work;

  work = GetActiveMenuScene();
  if (*(int *)(work + 0x73c) != 0) {
    return;
  }
  if (*(int *)(work + 0x904) != 0) {
    ClosePopupWindow(work,0);
    return;
  }
  PlaySoundEffect(0,1);
  SetPopupConfirmMode(work,1);
}
