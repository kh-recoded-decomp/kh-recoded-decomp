#include "nitro/types.h"

typedef struct Context {
    u8 pad_000[0x104];
    u8 slotMask;
} Context;

extern Context *data_ov001_020a04cc;

BOOL SetPendingSlotFlag_0207d4d0(int slot)
{
    Context *context;

    context = data_ov001_020a04cc;
    if (context == NULL || (u16)slot >= 4) {
        return FALSE;
    }
    context->slotMask |= 1 << slot;
    return TRUE;
}
