#include "nitro/types.h"

extern unsigned int *data_ov001_020a0464;
extern unsigned int ClearPackedBit();
extern unsigned int LoadPzResource_020663a4();
extern unsigned int NNSi_FndAllocFromDefaultHeap_0202a178();
extern unsigned int func_01ff86fc();
extern unsigned int func_01ff8740();
extern unsigned int func_020366f8();

void func_ov001_020663e4(void) {
  void *resource;

  if (data_ov001_020a0464 == (unsigned int *)0x0) {
    data_ov001_020a0464 = NNSi_FndAllocFromDefaultHeap_0202a178(0x3694);
    func_01ff8740(0,data_ov001_020a0464,0x3694);
    resource = NNSi_FndAllocFromDefaultHeap_0202a178(0x18);
    *data_ov001_020a0464 = resource;
    func_01ff86fc(0xffffffff,*data_ov001_020a0464,0x18);
    ClearPackedBit((void *)*data_ov001_020a0464,0xa0);
    func_020366f8(data_ov001_020a0464 + 0xf);
    *(u8 *)((int)data_ov001_020a0464 + 0x20f) =
         *(u8 *)((int)data_ov001_020a0464 + 0x20f) & ~1U;
    *(u16 *)(data_ov001_020a0464 + 0x83) = 0xa0;
    LoadPzResource_020663a4(data_ov001_020a0464);
  }
}
