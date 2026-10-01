#include "nitro/types.h"

extern int contextData_020b56a4[];
#define activeContext_020b56ac contextData_020b56a4[2]

u32 ScriptOp_GetObjectFixedField_020b10bc(int context)

{
  int object;
  
  object = activeContext_020b56ac;
  if (activeContext_020b56ac == 0) {
    return 0;
  }
  *(u16 *)(context + 0x2c) = 0x10;
  *(u32 *)(context + 0x30) = *(u32 *)(object + 0x29c);
  return 0;
}
