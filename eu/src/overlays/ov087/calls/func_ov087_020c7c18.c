#include "nitro/types.h"

extern u32 func_ov039_020bc638();
extern u32 func_ov087_020c6238();

void func_ov087_020c7c18(void) {
  int work;

  work = func_ov039_020bc638();
  if (*(int *)(work + 0x10) != 0) {
    return;
  }
  func_ov087_020c6238(work,1);
}
