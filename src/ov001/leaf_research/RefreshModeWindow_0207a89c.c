#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    s32 mode;
} ModeState;

typedef struct {
    u32 active;
    ModeState state;
} ModeContext;

extern ModeContext *g_activeContext_020a04c4;

extern void FlushBufferAndRunCallback_0200153c(void *window);

void RefreshModeWindow_0207a89c(int screen)
{
    ModeContext *context = g_activeContext_020a04c4;

    if (context != NULL && screen == 0) {
        switch (context->state.mode) {
        case 4:
        case 5:
        case 6:
            FlushBufferAndRunCallback_0200153c((u8 *)&context->state + 0x94);
            break;
        }
    }
}
