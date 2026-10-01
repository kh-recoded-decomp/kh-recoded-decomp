#include "nitro/types.h"

extern u32 func_0204d924();

void ToggleRootMenuOptionLeft_020c55bc(int context)

{
  if (*(u8 *)(context + 3) != '\x01') {
    return;
  }
  *(u8 *)(context + 4) = *(u8 *)(context + 4) ^ 1;
  func_0204d924(0,0);
  *(u8 *)(context + 2) = 1;
  return;
}
