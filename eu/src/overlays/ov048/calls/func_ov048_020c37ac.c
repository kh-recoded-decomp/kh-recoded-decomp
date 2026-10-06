#include "nitro/types.h"

extern u32 Camera_ComputeFollowPoint();

void func_ov048_020c37ac(void *camera,int mode) {
  Camera_ComputeFollowPoint(camera,mode,(void *)((int)camera + 0x18),camera);
}
