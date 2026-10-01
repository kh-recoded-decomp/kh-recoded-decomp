#include "nitro/types.h"

extern u32 func_0204d924();
extern u32 func_ov001_0206459c();
extern u32 func_ov039_020bbf78();
extern u32 func_ov039_020bc618();

void func_ov089_020c045c(void) {
  int selection;

  selection = func_ov039_020bc618();
  selection = *(int *)(*(int *)(selection + 0x748) * 0xc + *(int *)(selection + 0x738) + 8);
  if ((selection < 0) || (selection == 8)) {
    selection = 7;
  }
  else {
    selection = selection + 1;
  }
  func_ov001_0206459c(0x3703,3,selection);
  func_0204d924(0,1);
  func_ov039_020bbf78(0xffffffff,0xffffffff,1);
}
