#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1c];
    u8 recordPool[0x2e4 - 0x1c];
    u64 captionTick;
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_020a04a4;

extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void InvokeCallback40_020b8268(void *pool, void *record);

void HideHudCaption_02072c40(void) {
    HudContext *context = data_020a04a4.context;
    InvokeCallback40_020b8268(context->recordPool, FindActiveRecordById_020b8184(context->recordPool, 6));
    context->captionTick = 0;
}
