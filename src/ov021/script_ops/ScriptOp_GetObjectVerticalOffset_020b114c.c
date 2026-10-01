#include "nitro/types.h"

extern int contextData_020b56a4[];
#define activeContext_020b56ac contextData_020b56a4[2]

u32 ScriptOp_GetObjectVerticalOffset_020b114c(int context)

{
  int object;
  
  object = activeContext_020b56ac;
  if (activeContext_020b56ac == 0) {
    return 0;
  }
  *(u16 *)(context + 0x2c) = 0x10;
  *(int *)(context + 0x30) = *(int *)(object + 0x2c4) - *(int *)(object + 0x290);
  return 0;
}
