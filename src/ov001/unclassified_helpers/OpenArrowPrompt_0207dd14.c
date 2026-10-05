#include "nitro/types.h"

typedef struct ArrowPrompt {
    u8 state;
    u8 steps;
    u8 pad_02[0x2];
    s32 visible;
    u8 pad_08[0x4];
    s32 active;
    s32 seed;
    u8 pad_14[0x4];
    s32 elapsed;
    s32 timeLimit;
    u16 directions[2];
    u16 count;
    u16 remaining : 14;
    u32 failed : 1;
    u32 cleared : 1;
    s32 current;
} ArrowPrompt;

typedef struct StepTable {
    s32 values[4];
} StepTable;

extern ArrowPrompt *data_ov001_020a04d0;
extern const StepTable data_ov001_0209dff8;
extern const StepTable data_ov001_0209e008;

extern void *GetSceneTagTracker_020711b0(void);
extern int func_ov001_0207123c(void);
extern s32 GetClampedPaletteSlot_02073598(void);
extern int func_0202a7a4(void);
extern void SetupBgBlend_0207d6f4(void);
extern void func_ov027_020b9d54(int layers, int layer, int x, int y, int width, int height);
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *tracker, void *record);
extern u16 func_ov001_0207d838(void);
extern void ShowTwoDigitCounters_0207d984(ArrowPrompt *prompt);
extern void RefreshCounterRecordPositions_0207d790(ArrowPrompt *prompt);

void OpenArrowPrompt_0207dd14(void) {
    ArrowPrompt *prompt = data_ov001_020a04d0;
    void *tracker = GetSceneTagTracker_020711b0();
    int layers = func_ov001_0207123c();
    StepTable steps = data_ov001_0209dff8;
    StepTable seconds = data_ov001_0209e008;
    int i;

    if (prompt == NULL) {
        return;
    }
    i = 0;
    prompt->state = 0;
    prompt->steps = (steps.values[GetClampedPaletteSlot_02073598()] * 10 + 9) / 10;
    prompt->seed = func_0202a7a4();
    prompt->timeLimit = (seconds.values[GetClampedPaletteSlot_02073598()] * 10 + 9) / 10 * 1000;
    prompt->elapsed = 0;
    prompt->count = 0;
    prompt->remaining = 4;
    prompt->failed = 0;
    prompt->cleared = 0;
    SetupBgBlend_0207d6f4();
    func_ov027_020b9d54(layers, 0xb, 0, 8, 0xb, 0x10);
    TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0x12c));
    TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0x12e));
    TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0x131));
    TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0x132));
    TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0x133));
    prompt->current = 0;
    do {
        prompt->directions[i] = func_ov001_0207d838();
        i++;
    } while (i < 2);
    ShowTwoDigitCounters_0207d984(prompt);
    RefreshCounterRecordPositions_0207d790(prompt);
    prompt->visible = 1;
    prompt->active = 1;
}
