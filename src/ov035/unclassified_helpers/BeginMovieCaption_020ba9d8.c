#include "nitro/types.h"

typedef struct CaptionParams {
    s8 style;
    s8 line;
    s16 x;
    s16 y;
} CaptionParams;

typedef struct MovieContext {
    s16 line;
    s16 x;
    s16 y;
    u16 flags;
    u8 pad_08[0x10];
    int timer;
    s8 style;
} MovieContext;

extern MovieContext *g_movieContext_020bc4e0;

void BeginMovieCaption_020ba9d8(CaptionParams *params)
{
    g_movieContext_020bc4e0->x = params->x;
    g_movieContext_020bc4e0->y = params->y;
    g_movieContext_020bc4e0->line = params->line;
    g_movieContext_020bc4e0->flags = 3;
    g_movieContext_020bc4e0->flags |= 0x20;
    g_movieContext_020bc4e0->style = params->style;
    g_movieContext_020bc4e0->timer = 0;
}