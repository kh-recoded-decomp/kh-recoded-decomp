#include "nitro/types.h"

typedef struct ArrowPromptContext {
    u8 pad_00[0x28];
    u32 flags;
} ArrowPromptContext;

extern ArrowPromptContext *data_ov001_020a04f0;

u32 SetArrowPromptFlag1(void)
{
    ArrowPromptContext *context = data_ov001_020a04f0;
    u32 flags = context->flags;
    u32 result = (flags & ~1) | 1;
    context->flags = result;
    return result;
}
