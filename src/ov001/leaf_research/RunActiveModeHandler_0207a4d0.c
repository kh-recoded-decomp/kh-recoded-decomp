#include "nitro/types.h"

typedef void (*ModeHandler)(void *modeState);

typedef struct {
    u32 unk_00;
    u8 modeState[8];
    s32 mode;
    u8 pad_10[0xf8 - 0x10];
    u32 suspended;
} ModeContext;

extern ModeContext *g_activeContext_020a04c4;
extern ModeHandler data_ov001_0209ef04[];

extern void func_ov001_0207a370(void);

u32 RunActiveModeHandler_0207a4d0(void)
{
    ModeContext *context = g_activeContext_020a04c4;
    ModeHandler handler;

    if (context->suspended != 0) {
        return 0;
    }
    func_ov001_0207a370();
    handler = data_ov001_0209ef04[context->mode];
    if (handler != NULL) {
        handler(context->modeState);
    }
    return 0;
}
