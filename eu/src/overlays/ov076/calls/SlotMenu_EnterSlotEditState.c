#include "nitro/types.h"

extern unsigned int GetMenuWork();
extern unsigned int SlotMenu_ShowSlotHint();
extern unsigned int SetNavigationElementsVisible();

void SlotMenu_EnterSlotEditState(unsigned int *work) {
  unsigned int scene;

  *work = 1;
  work[0x71bd] = 0;
  SlotMenu_ShowSlotHint(work);
  if (work[0x1281d] != 0) {
    work[0x1281d] = 0;
    return;
  }
  scene = GetMenuWork();
  SetNavigationElementsVisible(scene,1);
}
