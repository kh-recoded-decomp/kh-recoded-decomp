#include "nitro/types.h"

extern int contextData_020b56a4[];
#define activeContext_020b56ac contextData_020b56a4[2]
extern u32 VEC_Mag_01ff9f28();

u32 ScriptOp_GetObjectVectorMagnitude_020b1270(int context)

{
  int object;
  u32 magnitude;
  
  object = activeContext_020b56ac;
  if (activeContext_020b56ac == 0) {
    return 0;
  }
  *(u16 *)(context + 0x2c) = 0x10;
  magnitude = VEC_Mag_01ff9f28(object + 0x368);
  *(u32 *)(context + 0x30) = magnitude;
  return 0;
}
