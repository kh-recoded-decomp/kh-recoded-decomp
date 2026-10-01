#include "nitro/types.h"

extern u32 Camera_ComputeFollowPoint_020c2c08();

void func_ov048_020c378c(void *camera,int mode) {
  Camera_ComputeFollowPoint_020c2c08(camera,mode,(void *)((int)camera + 0x18),camera);
}
