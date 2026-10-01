#include "nitro/types.h"

extern u32 data_ov036_020c3844;
extern u32 NNS_FndInitListWithOffset0_0204f11c();
extern u32 func_0204f0c0();

void func_ov036_020bf61c(int work) {
  int recordIndex;
  int slot;

  NNS_FndInitListWithOffset0_0204f11c((void *)(data_ov036_020c3844 + 0x18));
  slot = 0;
  do {
    recordIndex = *(int *)(work + 0xb4 + slot * 0x10);
    if (recordIndex != -1) {
      func_0204f0c0((void *)(data_ov036_020c3844 + 0x18),recordIndex);
      *(u32 *)(work + 0xb4 + slot * 0x10) = 0xffffffff;
    }
    slot = slot + 1;
  } while (slot < 5);
}
