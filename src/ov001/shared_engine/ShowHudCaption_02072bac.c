#include "nitro/types.h"

#define ONE_SECOND_IN_TICKS 0x7fd88

typedef struct {
    u8 pad_000[0x1c];
    u8 recordPool[0x1fc - 0x1c];
    u8 captionWindow[0x2e4 - 0x1fc];
    u64 captionTick;
    u64 captionDuration;
    u8 pad_2f4[0x6ec - 0x2f4];
    s32 labelIds[4];
} HudContext;

typedef struct {
    u32 unk_00;
    HudContext *context;
} HudGlobals;

extern HudGlobals data_020a04a4;

extern void CallVirtualHandlerSlot1_02001574(void *window, int arg);
extern void func_020015a0(void *window, u32 x, u32 y, u32 color, u32 flags, s32 labelId);
extern void func_02001520(void *window);
extern u16 *UpdateWidgetLayerDefault_020b9df0(HudContext *context, int layer);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void FillBackgroundLayerRect_02001a60(void *window, u16 *dst, int x, int y, u8 palette);

void ShowHudCaption_02072bac(int labelIndex) {
    HudContext *context = data_020a04a4.context;
    if (labelIndex != -1) {
        s32 labelId = context->labelIds[labelIndex];
        u16 *layer;
        CallVirtualHandlerSlot1_02001574(context->captionWindow, 1);
        func_020015a0(context->captionWindow, 0x70, 3, 2, 0x11, labelId);
        func_02001520(context->captionWindow);
        layer = UpdateWidgetLayerDefault_020b9df0(context, 0xb);
        TagTracker_InvokeCallback_020b8210(context->recordPool, FindActiveRecordById_020b8184(context->recordPool, 6));
        FillBackgroundLayerRect_02001a60(context->captionWindow, layer, 2, 1, 0xf);
        context->captionTick = 0;
        context->captionDuration = ONE_SECOND_IN_TICKS;
    }
}
