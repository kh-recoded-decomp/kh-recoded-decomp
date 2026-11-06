#include "nitro/types.h"

extern unsigned int *gFieldEffectPool;
extern unsigned int ActorSlot_UnlinkRoot();
extern unsigned int SetPackedBit();
extern unsigned int UnlinkContainerListNode();

void ReleaseFieldEffectSlot(int entry) {
  if (*(int *)(entry + 0x24) != 0) {
    UnlinkContainerListNode(*(int *)(entry + 0x24),entry);
    if (*(int *)((int)*(void **)(entry + 0x24) + 0x10) == 0) {
      ActorSlot_UnlinkRoot(*(void **)(entry + 0x24));
    }
    *(unsigned int *)(entry + 0x24) = 0;
    SetPackedBit((void *)*gFieldEffectPool,(u32)*(u8 *)(entry + 0x2d));
  }
}
