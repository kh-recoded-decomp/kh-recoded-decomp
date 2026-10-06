#include "nitro/types.h"

extern u32 ReadSessionPackedBits();

void func_ov001_02064628(u32 values, u16 *extra) {
    u16 word;
    u32 value;
    s32 offset;
    s32 index;

    index = 0;
    do {
        value = ReadSessionPackedBits(index * 0x20 + 0x3537, 0x20);
        offset = index * 4;
        index = index + 1;
        *(u32 *)(values + offset) = value;
    } while (index < 3);
    word = ReadSessionPackedBits(0x3597, 0x10);
    *extra = word;
}
