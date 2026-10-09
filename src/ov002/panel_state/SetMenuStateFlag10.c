#include "nitro/types.h"

typedef struct MenuFlagContext {
    u8 pad_00[0x22];
    u8 stateFlags;
} MenuFlagContext;

extern MenuFlagContext *g_context_0206c464;

s32 SetMenuStateFlag10(void)
{
    MenuFlagContext *context = g_context_0206c464;
    s32 flags = context->stateFlags | 0x10;

    context->stateFlags = flags;
    return flags;
}
