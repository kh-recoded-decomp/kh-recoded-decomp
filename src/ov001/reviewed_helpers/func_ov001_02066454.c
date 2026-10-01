#include "nitro/types.h"

extern unsigned int *data_ov001_020a0464;
extern unsigned int ActorSlot_UnlinkRoot_02036748();
extern unsigned int NNSi_FndFreeFromDefaultHeap_0202a1c4();

void func_ov001_02066454(void) {
  if (data_ov001_020a0464 != (unsigned int *)0x0) {
    NNSi_FndFreeFromDefaultHeap_0202a1c4((void *)*data_ov001_020a0464);
    NNSi_FndFreeFromDefaultHeap_0202a1c4((void *)data_ov001_020a0464[0x84]);
    ActorSlot_UnlinkRoot_02036748(data_ov001_020a0464 + 0xf);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(data_ov001_020a0464);
    data_ov001_020a0464 = (unsigned int *)0x0;
  }
}
