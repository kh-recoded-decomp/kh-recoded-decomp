#include "nitro/types.h"

extern u32 SceneNode_Draw();

void func_ov058_020d79a0(void *node) {
  if (*(int *)((int)node + 0x130) == 0) {
    return;
  }
  SceneNode_Draw(node);
}
