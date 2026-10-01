#include "nitro/types.h"

extern u8 panelState_0207e980[];
#define pendingValue (*(u32 *)(panelState_0207e980 + 40))

void func_ov015_02075024(u32 value)

{
  pendingValue = value;
  return;
}
