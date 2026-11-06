#include "nitro/types.h"

typedef struct ArrowPromptContext {
    u8 pad_00[0x28];
    u32 flags;
} ArrowPromptContext;

extern ArrowPromptContext *gArrowPromptWork;

u32 SetArrowPromptFlag1(void)
{
    ArrowPromptContext *context = gArrowPromptWork;
    u32 flags = context->flags;
    u32 result = (flags & ~1) | 1;
    context->flags = result;
    return result;
}
