#include "nitro/types.h"

extern u32 _data_ov025_020b7760;
extern u32 func_0204d924();
extern u32 func_ov001_02063a38();
extern u32 func_ov001_0207b320();
extern u32 func_ov001_0207b6b4();

void HandleDefaultMenuAction_020b5a94(void)

{
  int mode;
  
  if (*(u8 *)(_data_ov025_020b7760 + 0x64e9) == '\0') {
    func_ov001_0207b6b4();
    mode = func_ov001_02063a38();
    func_ov001_0207b320(mode == 10);
    func_0204d924(0,0x3b);
  }
  return;
}
