#include "nitro/types.h"

void SetMatrixInputDisabled_020c8de8(int context,int value)

{
  *(u8 *)(context + 0x13e7c) = value == 0;
  return;
}
