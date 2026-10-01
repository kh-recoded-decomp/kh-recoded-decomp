#include "nitro/types.h"

extern volatile u16 data_04000050;
extern unsigned int data_ov045_020c0880;
extern unsigned int data_ov045_020c0814;
extern unsigned int data_ov045_020c0824;
extern unsigned int func_01ff8830();
extern unsigned int func_01ff89a8();
extern unsigned int func_0202a764();
extern unsigned int func_ov001_0207512c();
extern unsigned int func_ov001_02075248();
extern unsigned int func_ov045_020be668();

unsigned int func_ov045_020be6a0(unsigned int arguments) {
  u16 *work;
  unsigned int scene;
  u8 *layout;
  unsigned int mode;

  work = (u16 *)func_0202a764();
  mode = 0;
  func_01ff8830(work,0,0x1a4c);
  func_01ff89a8(arguments,work,0x10);
  data_ov045_020c0880 = work;
  scene = func_ov001_02075248(0);
  *(unsigned int *)(work + 0x10) = scene;
  func_ov001_0207512c(0,0);
  if (*work == 3) {
    layout = &data_ov045_020c0814;
  }
  else {
    layout = &data_ov045_020c0824;
    mode = 2;
  }
  func_ov045_020be668(work + 0x12,work + 0x16,layout,mode);
  data_04000050 = 0;
  return 0x20be711;
}
