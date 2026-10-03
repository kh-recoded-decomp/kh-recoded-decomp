#include "nitro/types.h"

typedef struct FadeWork {
    u8 unknown_000[0x104];
    s16 paramA;
    s16 paramB;
    u8 unknown_108;
    s8 current;
    u8 count;
    u8 unknown_10b;
    u8 *entries;
} FadeWork;

extern FadeWork *data_ov035_020bc4e4;
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8740(int value, void *dest, u32 size);
extern void func_01ff8830(void *dest, int value, u32 size);

void CreateMaterialFadeWork_020bb4a4(s16 paramA, s16 paramB, int count) {
    FadeWork *work;
    u32 size;

    data_ov035_020bc4e4 = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(FadeWork));
    func_01ff8740(0, data_ov035_020bc4e4, sizeof(FadeWork));
    work = data_ov035_020bc4e4;
    work->current = -1;
    work->count = count;
    size = count * 4;
    work->entries = NNSi_FndAllocFromDefaultHeap_0202a178(size);
    func_01ff8830(work->entries, 0xff, size);
    work->paramA = paramA;
    work->paramB = paramB;
}
