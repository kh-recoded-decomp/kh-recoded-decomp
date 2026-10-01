#pragma opt_propagation off
#include "nitro/types.h"

extern unsigned int func_ov001_02067704();
extern unsigned int func_ov001_02067cd0();
extern unsigned int func_ov001_02067d0c();
extern unsigned int func_ov001_0206823c();

unsigned int func_ov040_020bcd08(void) {
  int lastSlot;
  int index;

  lastSlot = func_ov001_0206823c();
  lastSlot = lastSlot + -1;
  index = 0;
  if (0 < lastSlot) {
    do {
      func_ov001_02067d0c(index,1);
      func_ov001_02067cd0(index,1);
      index = index + 1;
    } while (index < lastSlot);
  }
  if (0 < lastSlot) {
    func_ov001_02067d0c(lastSlot,0);
    func_ov001_02067cd0(lastSlot,0);
  }
  func_ov001_02067704();
  return 2;
}
