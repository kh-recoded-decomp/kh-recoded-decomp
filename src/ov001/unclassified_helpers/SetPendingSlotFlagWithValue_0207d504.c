#include "nitro/types.h"

typedef struct Context {
    u8 pad_000[0x100];
    u32 slotValue;
    u8 slotMask;
} Context;

extern Context *data_ov001_020a04cc;

BOOL SetPendingSlotFlagWithValue_0207d504(int slot, u32 value)
{
    Context *context;

    context = data_ov001_020a04cc;
    if (context == NULL || (u16)slot >= 4) {
        return FALSE;
    }
    context->slotMask |= 1 << slot;
    context->slotValue = value;
    return TRUE;
}
