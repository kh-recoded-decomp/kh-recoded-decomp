#include "nitro/types.h"

extern u32 data_ov103_020c04e0;
extern u32 func_01ff8740();
extern u32 func_ov039_020bcd80();
extern u32 func_ov103_020beef4();
extern u32 func_ov103_020bef60();
extern u32 func_ov103_020bf0a4();
extern u32 func_ov103_020bf19c();
extern u32 func_ov103_020bf39c();
extern u32 func_ov103_020bf5c8();
extern u32 func_ov103_020bf994();
extern u32 func_ov103_020c01cc();
extern u32 func_ov103_020c02f4();

void func_ov103_020c031c(int *work) {
  int selection;

  selection = func_ov039_020bcd80();
  func_01ff8740(0,work,0xcbc4);
  if (selection < 0) {
    selection = 0;
  }
  *work = selection;
  work[1] = -0x10;
  work[0x32e2] = 0;
  work[0x32e4] = 0;
  work[0x32e3] = 0;
  func_ov103_020c01cc(work);
  func_ov103_020beef4(work);
  func_ov103_020bef60(work);
  func_ov103_020bf0a4(work);
  func_ov103_020bf19c(work);
  func_ov103_020bf5c8(work);
  func_ov103_020bf994(&data_ov103_020c04e0,work);
  func_ov103_020bf39c(0xffffffff,work);
  func_ov103_020c02f4(2,work);
}
