#include "nitro/types.h"

typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))

typedef struct {
    u8 pad_000[0x1c];
    u8 tagPool[0x1fc - 0x1c];
    u8 textLayer[0x2cc - 0x1fc];
    u8 messageSet[0x2e4 - 0x2cc];
    u64 shownTick;
    u64 displayTicks;
} FieldManager;

typedef struct {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;

extern int func_ov027_020ba31c(void *messages, const char *format, u16 *buffer, int length, va_list args);
extern void CallVirtualHandlerSlot1_02001574(void *layer, int arg);
extern void DrawTextAnchored_020015a0(void *layer, int x, int y, int color, u32 flags, const u16 *text);
extern void FlushBufferAndRunCallback_0200153c(void *layer);
extern u16 *UpdateWidgetLayerDefault_020b9df0(FieldManager *manager, int index);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void FillBackgroundLayerRect_02001a60(void *info, u16 *dst, int x, int y, u8 palette);
extern u64 OS_GetTick_02003fd4(void);

void ShowFieldMessageLine_02072ad0(const char *format, ...) {
    FieldManager *manager = data_ov001_020a04a4.manager;
    u16 text[0x40];
    va_list args;
    u16 *screen;

    va_start(args, format);
    func_ov027_020ba31c(manager->messageSet, format, text, 0x40, args);
    CallVirtualHandlerSlot1_02001574(manager->textLayer, 1);
    DrawTextAnchored_020015a0(manager->textLayer, 0x70, 3, 2, 0x11, text);
    FlushBufferAndRunCallback_0200153c(manager->textLayer);
    screen = UpdateWidgetLayerDefault_020b9df0(manager, 0xb);
    TagTracker_InvokeCallback_020b8210(manager->tagPool, FindActiveRecordById_020b8184(manager->tagPool, 6));
    FillBackgroundLayerRect_02001a60(manager->textLayer, screen, 2, 1, 0xf);
    manager->shownTick = OS_GetTick_02003fd4();
    manager->displayTicks = 0x17f898;
}
