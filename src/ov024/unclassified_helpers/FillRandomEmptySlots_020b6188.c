#include "nitro/types.h"

typedef struct Ov024Board {
    u8 pad_00[8];
    u32 freeMask;
    u8 pad_0C[0x31 - 0x0C];
    s8 slotValues[6];
} Ov024Board;

extern u32 func_0202a9d0(u32 range);
extern u64 DivModS32_02023dbc(int dividend, int divisor);
extern int PickRandomSetBit_020b6554(u32 mask);

void FillRandomEmptySlots_020b6188(Ov024Board *board, int count) {
    int placed;
    u32 freeMask = board->freeMask;

    for (placed = 0; placed < count; placed++) {
        int offset;
        int start = func_0202a9d0(6);
        for (offset = 0; offset < 6; offset++) {
            int slotIndex = (int)(DivModS32_02023dbc(start + offset, 6) >> 32);
            if (board->slotValues[slotIndex] < 0) {
                board->slotValues[slotIndex] = PickRandomSetBit_020b6554(freeMask);
                freeMask ^= 1 << board->slotValues[slotIndex];
                break;
            }
        }
    }
}
