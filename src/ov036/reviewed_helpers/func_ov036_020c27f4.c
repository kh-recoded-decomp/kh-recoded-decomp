#include "nitro/types.h"

extern u32 data_ov036_020c3844;
extern u32 func_0204d924();

void func_ov036_020c27f4(void) {
  if (*(int *)(data_ov036_020c3844 + 0x68a4) != 0) {
    return;
  }
  func_0204d924(0,7);
  *(u32 *)(data_ov036_020c3844 + 0x68a4) = 2;
}
