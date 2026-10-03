#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x6e];
    s8 enabledMask;
} ContextBytes;

extern struct { ContextBytes *context; } contextData_020c0060;

BOOL IsContextSlotEnabled_020bb840(u32 index)
{
    s8 mask = contextData_020c0060.context->enabledMask;
    if (mask < 0 || index >= 3) {
        return TRUE;
    }
    return (mask & (1 << index)) != 0;
}
