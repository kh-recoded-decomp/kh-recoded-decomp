#include "nitro/types.h"

extern u16 _data_02060500;
extern u32 func_0204d924();

void SelectPreviousRootMenuItem_020c54f0(u8 *context)

{
  if (context[3] != '\0') {
    return;
  }
  if (*context == '\0') {
    if ((_data_02060500 & 0x40) == 0) {
      return;
    }
    *context = context[1];
  }
  *context = *context + -1;
  func_0204d924(0,0);
  context[2] = '\x01';
  return;
}
