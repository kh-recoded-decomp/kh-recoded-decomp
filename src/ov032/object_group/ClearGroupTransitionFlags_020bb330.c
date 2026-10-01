#include "nitro/types.h"

extern int contextData_020c0060[];
#define activeContext_020c0064 contextData_020c0060[1]

u32 ClearGroupTransitionFlags_020bb330(void)

{
  *(u16 *)(activeContext_020c0064 + 6) = *(u16 *)(activeContext_020c0064 + 6) & 0xfff3;
  return 0xffffffff;
}
