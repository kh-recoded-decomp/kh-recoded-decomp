#include "src/overlays/ov001/SessionBuffers.h"

extern u32 data_ov001_020a0480;

u32 SessionBuffer_GetAddress(s32 index) {
    const SessionBufferSlot32 *slot = (const SessionBufferSlot32 *)(
        data_ov001_020a0480 + index * SESSION_BUFFER_RECORD_BYTES + SESSION_BUFFER_TABLE_OFFSET);
    return slot->address;
}
