#include "nitro/types.h"

typedef struct {
    u8 data[0x30];
} SlotBuffer;

typedef struct {
    u8 pad[0xcaec];
    SlotBuffer slots[0xef];
} SlotWork;

extern int FreeBufferAndClearStatus_0206a918(SlotBuffer *slot);

void FreeSlotBuffers_020c0704(SlotWork *work) {
    int i;

    for (i = 0; i < 0xef; i++) {
        FreeBufferAndClearStatus_0206a918(&work->slots[i]);
    }
}