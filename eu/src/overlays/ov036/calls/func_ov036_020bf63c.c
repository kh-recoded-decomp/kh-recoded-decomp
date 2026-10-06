#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 NNS_FndInitListWithOffset0_0204f130();
extern u32 func_0204f0d4();

void func_ov036_020bf63c(int work) {
  int recordIndex;
  int slot;

  NNS_FndInitListWithOffset0_0204f130((void *)(gTextWindowResourceTable + 0x18));
  slot = 0;
  do {
    recordIndex = *(int *)(work + 0xb4 + slot * 0x10);
    if (recordIndex != -1) {
      func_0204f0d4((void *)(gTextWindowResourceTable + 0x18),recordIndex);
      *(u32 *)(work + 0xb4 + slot * 0x10) = 0xffffffff;
    }
    slot = slot + 1;
  } while (slot < 5);
}
