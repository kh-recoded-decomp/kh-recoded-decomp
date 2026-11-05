#include "src/overlays/ov001/SessionPlacement.h"

extern u32 ReadSessionPackedBits();

void LoadPackedSessionPlacement(VecFx32 *position, u16 *angle) {
    u16 word;
    u32 value;
    s32 offset;
    s32 index;

    index = 0;
    do {
        value = ReadSessionPackedBits(index * 0x20 + 0x3537, 0x20);
        offset = index * 4;
        index = index + 1;
        *(u32 *)((u8 *)position + offset) = value;
    } while (index < 3);
    word = ReadSessionPackedBits(0x3597, 0x10);
    *angle = word;
}
