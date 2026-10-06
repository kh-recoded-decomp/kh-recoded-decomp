#include "nitro/types.h"

extern u32 SetSessionStateBit();
extern u32 func_ov001_02068ec4();

void func_ov001_02068d78(void) {
  func_ov001_02068ec4(0);
  SetSessionStateBit(1,2);
}
