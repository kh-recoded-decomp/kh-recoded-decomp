#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x484];
    s32 unk_484;
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_020a04a4;

extern void func_ov001_020701a8(HudContext *context);

void FlushHudWidgetAndSetState_020724e0(s32 value) {
    HudContext *context = data_020a04a4.context;
    func_ov001_020701a8(context);
    context->unk_484 = value;
}
