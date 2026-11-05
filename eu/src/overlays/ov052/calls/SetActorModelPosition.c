#include "nitro/types.h"

extern u32 Obj_SetPosition();

void SetActorModelPosition(int actor,void *position) {
  Obj_SetPosition(*(void **)(actor + 0x230),position);
}
