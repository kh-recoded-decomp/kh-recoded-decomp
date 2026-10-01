#include "nitro/types.h"

extern u32 func_ov039_020bc618();
extern u32 func_ov087_020c6218();

void func_ov087_020c7bf8(void) {
  int work;

  work = func_ov039_020bc618();
  if (*(int *)(work + 0x10) != 0) {
    return;
  }
  func_ov087_020c6218(work,1);
}
