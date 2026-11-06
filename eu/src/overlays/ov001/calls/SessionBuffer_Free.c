#include "src/overlays/ov001/SessionBuffers.h"

extern u32 gFieldSessionWork;
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void SessionBuffer_Free(s32 index) {
    SessionBufferSlot32 *slot = (SessionBufferSlot32 *)(
        gFieldSessionWork + SESSION_BUFFER_TABLE_OFFSET + index * SESSION_BUFFER_RECORD_BYTES);
    u32 address = slot->address;
    if (address != 0) {
        NNSi_FndFreeFromDefaultHeap((void *)address);
        slot->address = 0;
        slot->size = 0;
    }
}
