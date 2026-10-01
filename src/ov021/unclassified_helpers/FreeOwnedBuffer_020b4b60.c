#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    void *buffer;
    u8 pad_10[0x8c];
    u32 pad_9c_bits : 31;
    u32 ownsBuffer : 1;
} BufferHolder;

extern void FreeFromStageHeap_0209cf68(void *block);

void FreeOwnedBuffer_020b4b60(BufferHolder *holder)
{
    if (holder->ownsBuffer && holder->buffer != NULL) {
        FreeFromStageHeap_0209cf68(holder->buffer);
    }
    holder->buffer = NULL;
}
