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

extern Ov039State *data_ov039_020bea00;
extern char data_ov039_020be7fc[];
extern int LoadPrimarySubOverlay_020bce34(int index);
extern int LoadSecondarySubOverlay_020bcf50(int index);
extern u32 func_ov039_020bd654(void);
extern u32 func_ov039_020bd674(void);
extern int func_ov039_020bd634(void);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff8830(void *dst, int value, u32 size);
extern int DispatchActiveOverlayCallback_020bceb0(int work);
extern int dispatchSelectedMenuCallback_020bcfcc(int work);
extern void func_ov039_020bcf20(int work);
extern void func_ov039_020bd054(int work);
extern void InitStreamBufferPair_020bacbc(int blockCount, u32 flag);
extern void func_ov039_020baae0(int value);
extern void InvokeForChannelOrBoth_0200110c(u32 arg0, u32 arg1, int arg2, int channel);
extern void UpdateBrightnessAndTasks_020bad34(void);

void UpdateSubOverlayHandlers_020bb148(void)
{
    Ov039State *state = data_ov039_020bea00;

    if (state->primaryWork == NULL) {
        u32 size;
        LoadPrimarySubOverlay_020bce34(state->primaryIndex);
        size = func_ov039_020bd654();
        state->primaryWork = NNSi_FndAllocFromDefaultHeap_0202a178(size);
        func_01ff8830(state->primaryWork, 0, size);
    }
    if (state->primaryReady == 0) {
        state->primaryReady = DispatchActiveOverlayCallback_020bceb0((int)state->primaryWork);
    } else {
        func_ov039_020bcf20((int)state->primaryWork);
    }
    if (state->secondaryEnabled) {
        if (state->secondaryWork == NULL) {
            u32 size;
            LoadSecondarySubOverlay_020bcf50(func_ov039_020bd634());
            size = func_ov039_020bd674();
            state->secondaryWork = NNSi_FndAllocFromDefaultHeap_0202a178(size);
            func_01ff8830(state->secondaryWork, 0, size);
        }
        if (state->secondaryReady == 0) {
            state->secondaryReady = dispatchSelectedMenuCallback_020bcfcc((int)state->secondaryWork);
        } else {
            func_ov039_020bd054((int)state->secondaryWork);
        }
    }
    if (state->primaryReady && state->secondaryReady) {
        if (state->busyFlag) {
            state->busyFlag = 0;
        }
        if (state->startDelay != 0) {
            state->startDelay--;
        } else {
            InitStreamBufferPair_020bacbc(0, 100);
            func_ov039_020baae0(2);
        }
    }
    if (state->vblankPending) {
        InvokeForChannelOrBoth_0200110c(1, (u32)data_ov039_020be7fc, (int)UpdateBrightnessAndTasks_020bad34, -1);
        state->vblankPending = 0;
    }
}

