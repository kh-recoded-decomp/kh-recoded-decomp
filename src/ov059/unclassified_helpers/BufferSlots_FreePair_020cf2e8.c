#include "nitro/types.h"

typedef struct BufferSlot {
    u8 data[0x30];
} BufferSlot;

extern BOOL FreeBufferAndClearStatus_0206a918(BufferSlot *slot);

void BufferSlots_FreePair_020cf2e8(BufferSlot *slots)
{
    int i;

    for (i = 0; i < 2; i++) {
        FreeBufferAndClearStatus_0206a918(&slots[i]);
    }
}
