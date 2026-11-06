#include "src/overlays/ov001/SessionBuffers.h"

extern u32 gFieldSessionWork;

u32 SessionBuffer_GetSize(s32 index) {
    const SessionBufferSlot32 *slot = (const SessionBufferSlot32 *)(
        gFieldSessionWork + index * SESSION_BUFFER_RECORD_BYTES + SESSION_BUFFER_TABLE_OFFSET);
    return slot->size;
}
