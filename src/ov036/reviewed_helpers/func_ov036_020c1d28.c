#include "nitro/types.h"

extern u32 data_ov036_020c3844;
extern u32 func_ov036_020bf4fc();
extern u32 func_ov036_020c27dc();
extern u32 func_ov036_020c27ec();

void func_ov036_020c1d28(int work) {
  int state;

  state = func_ov036_020c27ec(data_ov036_020c3844 + 0x64fc);
  if (state != 9) {
    return;
  }
  func_ov036_020bf4fc(work + 0xb4,0);
  func_ov036_020bf4fc(work + 0xf4,0);
  func_ov036_020c27dc(work,9);
}
