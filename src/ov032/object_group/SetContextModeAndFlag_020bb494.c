#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u16 flags;
    u8 mode;
} GroupContext;

extern struct { int reserved; GroupContext *context; } contextData_020c0060;

void SetContextModeAndFlag_020bb494(u8 mode)
{
    contextData_020c0060.context->mode = mode;
    contextData_020c0060.context->flags |= 0x4000;
}
