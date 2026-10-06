#include "nitro/types.h"

extern unsigned int *data_ov001_020a0484;
extern unsigned int ActorSlot_UnlinkRoot();
extern unsigned int NNSi_FndFreeFromDefaultHeap();

void func_ov001_02066454(void) {
  if (data_ov001_020a0484 != (unsigned int *)0x0) {
    NNSi_FndFreeFromDefaultHeap((void *)*data_ov001_020a0484);
    NNSi_FndFreeFromDefaultHeap((void *)data_ov001_020a0484[0x84]);
    ActorSlot_UnlinkRoot(data_ov001_020a0484 + 0xf);
    NNSi_FndFreeFromDefaultHeap(data_ov001_020a0484);
    data_ov001_020a0484 = (unsigned int *)0x0;
  }
}
