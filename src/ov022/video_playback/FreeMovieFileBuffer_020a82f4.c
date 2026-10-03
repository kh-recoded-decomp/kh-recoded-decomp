#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x48];
    void *buffer;
    u32 size;
    u32 fill;
} MovieFileBank;

extern MovieFileBank data_ov022_020b7d94;

extern void func_01ff89a8(void *buffer, u32 fill, u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);

void FreeMovieFileBuffer_020a82f4(void) {
    func_01ff89a8(data_ov022_020b7d94.buffer, data_ov022_020b7d94.fill, data_ov022_020b7d94.size);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(data_ov022_020b7d94.buffer);
}
