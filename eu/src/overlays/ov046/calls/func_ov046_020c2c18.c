#include "nitro/types.h"

extern u32 Camera_ComputeFollowPoint();

void func_ov046_020c2c18(void *outPosition,void *target) {
  Camera_ComputeFollowPoint((void *)0x0,0,outPosition,target);
}
