#include "nitro/types.h"

extern unsigned int SetSecondaryElementEnabled();
extern unsigned int SlotMenu_RefreshView();
extern unsigned int SlotMenu_StartScrollAnimation();

void func_ov076_020c5ca0(int work) {
  SetSecondaryElementEnabled(0);
  SlotMenu_RefreshView(work);
  *(u8 *)(work + 0x49857) = *(u8 *)(work + 0x49857) + -1;
  if (*(u8 *)(work + 0x49857) == '\0') {
    SlotMenu_StartScrollAnimation(work);
  }
}
