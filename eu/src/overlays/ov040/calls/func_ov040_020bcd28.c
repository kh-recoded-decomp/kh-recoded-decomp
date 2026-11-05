#pragma opt_propagation off
#define func_ov001_0206823c GetCurrentSceneEntrySlotId
#include "nitro/types.h"

extern unsigned int ResetSceneSlots();
extern unsigned int SetSceneSlotDrawingEnabled();
extern unsigned int func_ov001_02067d0c();
extern unsigned int func_ov001_0206823c();

unsigned int func_ov040_020bcd28(void) {
  int lastSlot;
  int index;

  lastSlot = func_ov001_0206823c();
  lastSlot = lastSlot + -1;
  index = 0;
  if (0 < lastSlot) {
    do {
      func_ov001_02067d0c(index,1);
      SetSceneSlotDrawingEnabled(index,1);
      index = index + 1;
    } while (index < lastSlot);
  }
  if (0 < lastSlot) {
    func_ov001_02067d0c(lastSlot,0);
    SetSceneSlotDrawingEnabled(lastSlot,0);
  }
  ResetSceneSlots();
  return 2;
}
