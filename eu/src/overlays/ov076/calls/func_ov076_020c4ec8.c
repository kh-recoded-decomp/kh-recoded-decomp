#include "nitro/types.h"

extern unsigned int func_ov039_020bc1dc();
extern unsigned int SlotMenu_ShowSlotHint();
extern unsigned int SetNavigationElementsVisible();

void func_ov076_020c4ec8(unsigned int *work) {
  unsigned int scene;

  *work = 1;
  work[0x71bd] = 0;
  SlotMenu_ShowSlotHint(work);
  if (work[0x1281d] != 0) {
    work[0x1281d] = 0;
    return;
  }
  scene = func_ov039_020bc1dc();
  SetNavigationElementsVisible(scene,1);
}
