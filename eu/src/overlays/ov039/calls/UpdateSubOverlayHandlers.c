#include "nitro/types.h"

typedef struct Ov039State {
    u8 pad_0000[0xc998];
    void *primaryWork;
    void *secondaryWork;
    u8 pad_c9a0[0x1c];
    int primaryIndex;
    u8 pad_c9c0[0x4c];
    BOOL secondaryEnabled;
    u8 pad_ca10[0x14];
    BOOL vblankPending;
    BOOL busyFlag;
    BOOL primaryReady;
    BOOL secondaryReady;
    u8 pad_ca34[0x10];
    u8 startDelay;
} Ov039State;

extern Ov039State *data_ov039_020bea20;
extern char sOv039_MENUMNGR_020be81c[];
extern int LoadPrimarySubOverlay(int index);
extern int LoadSecondarySubOverlay(int index);
extern u32 GetPrimaryMenuSubOverlayWorkSize(void);
extern u32 GetSecondaryMenuSubOverlayWorkSize(void);
extern int GetPrimaryMenuSecondaryOverlayIndex(void);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern int DispatchActiveOverlayCallback(int work);
extern int dispatchSelectedMenuCallback(int work);
extern void UpdatePrimaryMenuSubOverlay(int work);
extern void UpdateSecondaryMenuSubOverlay(int work);
extern void StartMenuBrightnessTweens(int blockCount, u32 flag);
extern void SetMenuPhase(int value);
extern void InvokeForChannelOrBoth(u32 arg0, u32 arg1, int arg2, int channel);
extern void UpdateBrightnessAndTasks(void);

void UpdateSubOverlayHandlers(void)
{
    Ov039State *state = data_ov039_020bea20;

    if (state->primaryWork == NULL) {
        u32 size;
        LoadPrimarySubOverlay(state->primaryIndex);
        size = GetPrimaryMenuSubOverlayWorkSize();
        state->primaryWork = NNSi_FndAllocFromDefaultHeap(size);
        MI_CpuFill8(state->primaryWork, 0, size);
    }
    if (state->primaryReady == 0) {
        state->primaryReady = DispatchActiveOverlayCallback((int)state->primaryWork);
    } else {
        UpdatePrimaryMenuSubOverlay((int)state->primaryWork);
    }
    if (state->secondaryEnabled) {
        if (state->secondaryWork == NULL) {
            u32 size;
            LoadSecondarySubOverlay(GetPrimaryMenuSecondaryOverlayIndex());
            size = GetSecondaryMenuSubOverlayWorkSize();
            state->secondaryWork = NNSi_FndAllocFromDefaultHeap(size);
            MI_CpuFill8(state->secondaryWork, 0, size);
        }
        if (state->secondaryReady == 0) {
            state->secondaryReady = dispatchSelectedMenuCallback((int)state->secondaryWork);
        } else {
            UpdateSecondaryMenuSubOverlay((int)state->secondaryWork);
        }
    }
    if (state->primaryReady && state->secondaryReady) {
        if (state->busyFlag) {
            state->busyFlag = 0;
        }
        if (state->startDelay != 0) {
            state->startDelay--;
        } else {
            StartMenuBrightnessTweens(0, 100);
            SetMenuPhase(2);
        }
    }
    if (state->vblankPending) {
        InvokeForChannelOrBoth(1, (u32)sOv039_MENUMNGR_020be81c, (int)UpdateBrightnessAndTasks, -1);
        state->vblankPending = 0;
    }
}

