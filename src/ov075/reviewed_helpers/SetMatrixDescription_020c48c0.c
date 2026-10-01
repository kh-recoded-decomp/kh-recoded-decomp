#include "nitro/types.h"

extern u32 func_ov027_020ba2a8();

void SetMatrixDescription_020c48c0(int context,int messageIndex)

{
  u32 description;
  
  if (messageIndex >= 0) {
    description = func_ov027_020ba2a8(context + 0x4ee0,messageIndex);
  }
  else {
    description = 0;
  }
  *(u32 *)(context + 0x11fac) = description;
  *(u8 *)(context + 7) = 1;
  return;
}
