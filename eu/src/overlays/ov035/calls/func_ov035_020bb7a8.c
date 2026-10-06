#include "nitro/types.h"

extern u32 data_ov035_020bc504;
extern void func_ov035_020bb66c(void);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void func_ov035_020bb7a8(void) {
    func_ov035_020bb66c();
    NNSi_FndFreeFromDefaultHeap(*(void **)(data_ov035_020bc504 + 0x10c));
    NNSi_FndFreeFromDefaultHeap((void *)data_ov035_020bc504);
}
