#include "nitro/types.h"

extern u32 SceneNode_Draw_01ffb12c();

void func_ov058_020d7980(void *node) {
  if (*(int *)((int)node + 0x130) == 0) {
    return;
  }
  SceneNode_Draw_01ffb12c(node);
}
