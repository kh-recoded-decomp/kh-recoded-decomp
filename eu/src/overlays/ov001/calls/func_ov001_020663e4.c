#include "nitro/types.h"

extern unsigned int *data_ov001_020a0484;
extern unsigned int ClearPackedBit();
extern unsigned int LoadPzResource();
extern unsigned int NNSi_FndAllocFromDefaultHeap();
extern unsigned int MIi_CpuClear32();
extern unsigned int MIi_CpuClearFast();
extern unsigned int func_0203670c();

void func_ov001_020663e4(void) {
  void *resource;

  if (data_ov001_020a0484 == (unsigned int *)0x0) {
    data_ov001_020a0484 = NNSi_FndAllocFromDefaultHeap(0x3694);
    MIi_CpuClearFast(0,data_ov001_020a0484,0x3694);
    resource = NNSi_FndAllocFromDefaultHeap(0x18);
    *data_ov001_020a0484 = resource;
    MIi_CpuClear32(0xffffffff,*data_ov001_020a0484,0x18);
    ClearPackedBit((void *)*data_ov001_020a0484,0xa0);
    func_0203670c(data_ov001_020a0484 + 0xf);
    *(u8 *)((int)data_ov001_020a0484 + 0x20f) =
         *(u8 *)((int)data_ov001_020a0484 + 0x20f) & ~1U;
    *(u16 *)(data_ov001_020a0484 + 0x83) = 0xa0;
    LoadPzResource(data_ov001_020a0484);
  }
}
