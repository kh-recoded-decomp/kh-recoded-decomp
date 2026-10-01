#include "nitro/types.h"

extern int contextData_020c0060[];
#define activeContext_020c0064 contextData_020c0060[1]
extern u32 func_ov001_0207ed2c();
extern u32 func_ov001_02087178();

u32 AcknowledgeGroupTransition_020ba940(void)

{
  int ready;
  
  ready = func_ov001_0207ed2c();
  if (ready == 0) {
    return 0xffffffff;
  }
  func_ov001_02087178();
  *(u16 *)(activeContext_020c0064 + 6) = *(u16 *)(activeContext_020c0064 + 6) | 0x8000;
  return 3;
}
