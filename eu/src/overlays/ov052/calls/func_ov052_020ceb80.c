#include "nitro/types.h"

extern u32 Obj_SetPosition();

void func_ov052_020ceb80(int actor,void *position) {
  Obj_SetPosition(*(void **)(actor + 0x230),position);
}
