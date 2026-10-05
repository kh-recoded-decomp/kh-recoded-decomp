#include "nitro/types.h"

typedef struct ArrowPrompt {
    u8 pad_00[0xc];
    s32 active;
    u32 startTime;
    u32 flashStart;
    u32 finishStart;
    s32 timeLimit;
} ArrowPrompt;

extern void *GetSceneTagTracker_020711b0(void);
extern int func_ov001_0207123c(void);
extern u32 func_0202a7a4(void);
extern void RunHudExitCallback_02071fec(void);
extern void func_ov027_020b9d54(int layers, int layer, int x, int y, int width, int height);
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void func_ov027_020b81d8(void *pool, void *record, s16 frame);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, void *record);
extern void InvokeCallback40_020b8268(void *pool, void *record);

static inline int FramesToMs(u32 frames) {
    return frames * 1000 / 30;
}

void UpdateArrowPromptTimer_0207d848(ArrowPrompt *prompt) {
    void *tracker = GetSceneTagTracker_020711b0();
    int layers = func_ov001_0207123c();
    u32 now = func_0202a7a4();
    int elapsed;
    int seconds;
    void *record;

    if (prompt->flashStart != 0 && FramesToMs(now - prompt->flashStart) >= 500) {
        prompt->flashStart = 0;
        InvokeCallback40_020b8268(tracker, FindActiveRecordById_020b8184(tracker, 0x134));
    }
    if (prompt->finishStart != 0) {
        if (FramesToMs(now - prompt->finishStart) >= 500) {
            RunHudExitCallback_02071fec();
        }
        return;
    }
    seconds = 0;
    func_ov027_020b9d54(layers, 0xb, 0xe, 0, 4, 2);
    elapsed = FramesToMs(func_0202a7a4() - prompt->startTime);
    if (prompt->timeLimit - elapsed < -500) {
        RunHudExitCallback_02071fec();
        return;
    }
    if (elapsed >= prompt->timeLimit) {
        prompt->active = 0;
    } else {
        seconds = prompt->timeLimit / 1000 - elapsed / 1000;
    }
    if (seconds / 10 != 0) {
        record = FindActiveRecordById_020b8184(tracker, seconds / 10 + 0x168);
        func_ov027_020b81d8(tracker, record, 0xe);
        TagTracker_InvokeCallback_020b8210(tracker, record);
    }
    record = FindActiveRecordById_020b8184(tracker, seconds % 10 + 0x168);
    func_ov027_020b81d8(tracker, record, seconds >= 10 ? 0x10 : 0xf);
    TagTracker_InvokeCallback_020b8210(tracker, record);
}
