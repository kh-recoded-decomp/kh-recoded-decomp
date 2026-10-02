#include "nitro/types.h"

typedef struct MessageWindow {
    u8 pad_00[4];
    s32 phase;
    u8 pad_08[0x84 - 0x08];
    u64 pageTick;
    u8 pad_8c[0x94 - 0x8c];
    u8 textLayer[4];
} MessageWindow;

typedef struct ModeContext {
    s32 mode;
} ModeContext;

extern ModeContext *g_activeContext_020a04c4;

extern u64 OS_GetTick_02003fd4(void);
extern int func_ov001_02079b4c(MessageWindow *window, int arg);
extern int func_ov001_02079a9c(MessageWindow *window);
extern int func_ov001_02079c88(MessageWindow *window, BOOL fullRedraw);
extern void Text_UploadTileBuffer_02001520(void *layer);
extern void *GetSceneTagTracker_020711b0(void);
extern void FinishMessageWindowPage_02079f2c(MessageWindow *window);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, void *record);

void UpdateMessageWindow_02079ff8(MessageWindow *window)
{
    ModeContext *context = g_activeContext_020a04c4;
    int busy = 0;
    u64 now = OS_GetTick_02003fd4();
    void *tracker;

    if (context->mode == 2 || (u32)(context->mode - 8) <= 1) {
        if (now < window->pageTick + 0x1991b) {
            return;
        }
    }
    switch (window->phase) {
    case 0:
        busy = func_ov001_02079b4c(window, 0);
        break;
    case 2:
        busy = func_ov001_02079c88(window, 0);
        break;
    case 1:
        busy = func_ov001_02079a9c(window);
        Text_UploadTileBuffer_02001520(window->textLayer);
        break;
    }
    if (busy == 0) {
        tracker = GetSceneTagTracker_020711b0();
        FinishMessageWindowPage_02079f2c(window);
        switch (context->mode) {
        case 5:
        case 10:
            TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0x25a));
            return;
        case 7:
            TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0x258));
            return;
        case 6:
            TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0x259));
            return;
        }
    }
}
