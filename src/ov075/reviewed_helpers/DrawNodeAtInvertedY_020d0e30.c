#include "nitro/types.h"

extern u32 SceneNode_Draw_01ffb12c();

void DrawNodeAtInvertedY_020d0e30(void *node,u32 x,int y)

{
  *(u32 *)((int)node + 0xa4) = x;
  *(int *)((int)node + 0xa8) = 0xc0000 - y;
  SceneNode_Draw_01ffb12c(node);
  return;
}
