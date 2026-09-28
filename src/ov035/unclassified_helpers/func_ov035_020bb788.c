#include "nitro/types.h"

extern u32 data_ov035_020bc4e4;
extern void func_ov035_020bb64c(void);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void func_ov035_020bb788(void) {
    func_ov035_020bb64c();
    NNSi_FndFreeFromDefaultHeap_0202a1c4(*(void **)(data_ov035_020bc4e4 + 0x10c));
    NNSi_FndFreeFromDefaultHeap_0202a1c4((void *)data_ov035_020bc4e4);
}
