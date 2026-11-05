#ifndef KH_RECODED_SESSION_BUFFERS_H
#define KH_RECODED_SESSION_BUFFERS_H

#include "nitro/types.h"

/* Recovered DS record: an ARM data address and its requested byte size.
 * This is a 32-bit memory-layout view, not a host pointer-bearing structure.
 */
typedef struct SessionBufferSlot32 {
    u32 address;
    u32 size;
} SessionBufferSlot32;

typedef char SessionBufferSlot32SizeCheck[sizeof(SessionBufferSlot32) == 8 ? 1 : -1];

enum {
    SESSION_BUFFER_TABLE_OFFSET = 0x283c,
    SESSION_BUFFER_RECORD_BYTES = 8
};

/* All functions require an initialized context and a valid slot index.
 * Capacity, context ownership and total context size are not inferred here.
 */
void *AllocSessionBuffer(s32 index, u32 size);
u32 SessionBuffer_GetAddress(s32 index);
u32 SessionBuffer_GetSize(s32 index);
void SessionBuffer_Free(s32 index);

#endif
