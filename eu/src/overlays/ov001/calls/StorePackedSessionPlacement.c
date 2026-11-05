#include "src/overlays/ov001/SessionPlacement.h"

extern u32 WriteSessionPackedBits();

void StorePackedSessionPlacement(const VecFx32 *position, u32 angle) {
    s32 index = 0;
    do {
        WriteSessionPackedBits(index * 0x20 + 0x3537, 0x20, *(const u32 *)((const u8 *)position + index * 4));
        index = index + 1;
    } while (index < 3);
    WriteSessionPackedBits(0x3597, 0x10, angle);
}
