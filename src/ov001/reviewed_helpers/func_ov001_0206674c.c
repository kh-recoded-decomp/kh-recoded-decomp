#include "nitro/types.h"

extern unsigned int *data_ov001_020a0464;
extern unsigned int ActorSlot_UnlinkRoot_02036748();
extern unsigned int SetPackedBit();
extern unsigned int func_020367c0();

void func_ov001_0206674c(int entry) {
  if (*(int *)(entry + 0x24) != 0) {
    func_020367c0(*(int *)(entry + 0x24),entry);
    if (*(int *)((int)*(void **)(entry + 0x24) + 0x10) == 0) {
      ActorSlot_UnlinkRoot_02036748(*(void **)(entry + 0x24));
    }
    *(unsigned int *)(entry + 0x24) = 0;
    SetPackedBit((void *)*data_ov001_020a0464,(u32)*(u8 *)(entry + 0x2d));
  }
}
