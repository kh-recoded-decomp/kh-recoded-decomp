#include "nitro/types.h"

extern u16 _data_02060500;
extern u32 _data_ov091_020c50e4;
extern u32 func_0204d924();
extern u32 func_ov039_020bca00();
extern u32 func_ov091_020c317c();
extern u32 func_ov091_020c3bc4();

void func_ov093_020c34a4(u32 context)

{
  int result;

  result = func_ov039_020bca00();
  if (((((_data_02060500 & 1) == 0) && ((_data_02060500 & 2) == 0)) && ((_data_02060500 & 8) == 0))
     && ((*(u16 *)(result + 8) & 3) != 1)) {
    return;
  }
  func_ov091_020c317c(*(u32 *)(_data_ov091_020c50e4 + 0x10),0);
  func_0204d924(0,1);
  func_ov091_020c3bc4(context,6);
  return;
}
