#include "nitro/types.h"

extern void WriteSessionPackedBits(u32 id, int size, int value);
extern void ClearSessionPackedBit(u32 id);

void func_ov035_020bb28c(void) {
    ClearSessionPackedBit(0x3702);
    ClearSessionPackedBit(0x379b);
    WriteSessionPackedBits(0x3791, 10, 0);
    ClearSessionPackedBit(0x3723);
    ClearSessionPackedBit(0x3724);
}
