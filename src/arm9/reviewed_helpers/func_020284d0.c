#include "nitro/types.h"

extern u32 func_ov001_02063838();
extern u32 func_ov001_0208881c();
extern u32 func_ov036_020bc5e0();

void func_020284d0(void) {
  int active;

  active = func_ov001_02063838();
  if (active != 0) {
    func_ov001_0208881c();
    return;
  }
  func_ov036_020bc5e0();
}
