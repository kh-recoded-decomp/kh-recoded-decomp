#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x1c];
    u8 recordPool[0x18c - 0x1c];
    u8 popupWindow[0x40c - 0x18c];
    u64 popupTick;
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_020a04a4;

extern void CallVirtualHandlerSlot1_02001574(void *window, int arg);
extern void func_02001520(void *window);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void InvokeCallback40_020b8268(void *pool, void *record);

void ClearHudPopup_0207248c(void) {
    HudContext *context = data_020a04a4.context;
    if (context->popupTick != 0) {
        CallVirtualHandlerSlot1_02001574(context->popupWindow, 1);
        func_02001520(context->popupWindow);
        InvokeCallback40_020b8268(context->recordPool, FindActiveRecordById_020b8184(context->recordPool, 0x34));
        context->popupTick = 0;
    }
}
