#include "nitro/types.h"

extern u16 _data_02060500;
extern u32 _data_ov091_020c373c;
extern u32 func_0204d924();
extern u32 func_ov039_020bca00();
extern u32 func_ov091_020c1d48();
extern u32 func_ov091_020c2784();

void HandleEntryConfirmInput_020c2064(u32 context)

{
  int result;
  
  result = func_ov039_020bca00();
  if (((((_data_02060500 & 1) == 0) && ((_data_02060500 & 2) == 0)) && ((_data_02060500 & 8) == 0))
     && ((*(u16 *)(result + 8) & 3) != 1)) {
    return;
  }
  func_ov091_020c1d48(*(u32 *)(_data_ov091_020c373c + 0x10),0);
  func_0204d924(0,7);
  func_ov091_020c2784(context,6);
  return;
}
