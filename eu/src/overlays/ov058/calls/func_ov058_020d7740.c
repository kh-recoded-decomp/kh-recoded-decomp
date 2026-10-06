#include "nitro/types.h"

extern u32 func_01ffb12c();

void func_ov058_020d7740(void *node) {
  if (*(int *)((int)node + 0x130) == 0) {
    return;
  }
  func_01ffb12c(node);
}
