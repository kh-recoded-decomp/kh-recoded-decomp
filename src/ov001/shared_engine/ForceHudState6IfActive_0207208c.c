#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x608];
    s32 state;
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_020a04a4;

extern void func_ov001_02078938(s32 value);

void ForceHudState6IfActive_0207208c(void) {
    HudContext *context = data_020a04a4.context;
    if (context->state != 0) {
        context->state = 6;
        func_ov001_02078938(1);
    }
}
