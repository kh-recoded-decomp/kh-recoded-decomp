#include "nitro/types.h"

extern unsigned int *gFieldEffectPool;
extern unsigned int ActorSlot_UnlinkRoot();
extern unsigned int NNSi_FndFreeFromDefaultHeap();

void DestroyFieldEffectPool(void) {
  if (gFieldEffectPool != (unsigned int *)0x0) {
    NNSi_FndFreeFromDefaultHeap((void *)*gFieldEffectPool);
    NNSi_FndFreeFromDefaultHeap((void *)gFieldEffectPool[0x84]);
    ActorSlot_UnlinkRoot(gFieldEffectPool + 0xf);
    NNSi_FndFreeFromDefaultHeap(gFieldEffectPool);
    gFieldEffectPool = (unsigned int *)0x0;
  }
}
