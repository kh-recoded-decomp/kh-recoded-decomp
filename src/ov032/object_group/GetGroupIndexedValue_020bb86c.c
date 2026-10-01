#include "nitro/types.h"

extern int contextData_020c0060[];
#define activeContext_020c0064 contextData_020c0060[1]

u32 GetGroupIndexedValue_020bb86c(u32 index)

{
  if (index < 3) {
    index = (u32)*(u16 *)(activeContext_020c0064 + index * 2 + 0x44);
  }
  return index;
}
