#include "nitro/types.h"

extern u16 _data_02060500;
extern u32 _data_ov029_020baba0;
extern u32 func_ov001_0206dc4c();
extern u32 func_ov001_0206e444();

u32 HandleOverlayExitFlag_020ba708(void)

{
  int state;
  
  state = _data_ov029_020baba0;
  if ((_data_02060500 & 0x400) != 0) {
    func_ov001_0206dc4c(0);
  }
  if ((*(u16 *)(state + 6) & 0x4000) != 0) {
    func_ov001_0206e444(1);
    *(u16 *)(_data_ov029_020baba0 + 6) = *(u16 *)(_data_ov029_020baba0 + 6) | 0x8000;
    return 6;
  }
  return 0xffffffff;
}
