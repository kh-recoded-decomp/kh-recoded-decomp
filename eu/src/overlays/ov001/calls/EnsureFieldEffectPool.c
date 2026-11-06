#include "nitro/types.h"

extern unsigned int *gFieldEffectPool;
extern unsigned int ClearPackedBit();
extern unsigned int LoadPzResource();
extern unsigned int NNSi_FndAllocFromDefaultHeap();
extern unsigned int MIi_CpuClear32();
extern unsigned int MIi_CpuClearFast();
extern unsigned int InitPersistentActorSlot();

void EnsureFieldEffectPool(void) {
  void *resource;

  if (gFieldEffectPool == (unsigned int *)0x0) {
    gFieldEffectPool = NNSi_FndAllocFromDefaultHeap(0x3694);
    MIi_CpuClearFast(0,gFieldEffectPool,0x3694);
    resource = NNSi_FndAllocFromDefaultHeap(0x18);
    *gFieldEffectPool = resource;
    MIi_CpuClear32(0xffffffff,*gFieldEffectPool,0x18);
    ClearPackedBit((void *)*gFieldEffectPool,0xa0);
    InitPersistentActorSlot(gFieldEffectPool + 0xf);
    *(u8 *)((int)gFieldEffectPool + 0x20f) =
         *(u8 *)((int)gFieldEffectPool + 0x20f) & ~1U;
    *(u16 *)(gFieldEffectPool + 0x83) = 0xa0;
    LoadPzResource(gFieldEffectPool);
  }
}
