#include "nitro/types.h"

typedef struct Ov039Task {
    BOOL (*run)(void);
    u8 pad_04[0xc];
    BOOL finished;
} Ov039Task;

typedef struct TouchSample {
    u16 x;
    u16 y;
    u16 touch;
    u16 validity;
} TouchSample;

typedef union TouchPos {
    u32 raw;
    struct {
        u16 x;
        u16 y;
    } p;
} TouchPos;

typedef struct Ov039State {
    u8 resources[0x647c];
    u8 subResources[0xc8f8 - 0x647c];
    u8 mainTracker[0x4c];
    u8 subTracker[0x50];
    int mode;
    u8 pad_c998[8];
    u8 tileTable[0x1c];
    int primaryIndex;
    u8 pad_c9c0[4];
    int phase;
    u8 pad_c9c8[0x40];
    int frameFlag;
    u8 pad_ca0c[4];
    BOOL inputEnabled;
    BOOL touchEnabled;
    u8 pad_ca18[8];
    u16 buttonState;
    u8 layerMask;
    u8 pad_ca23[0x1d];
    BOOL tasksPaused;
    u8 pad_ca44[4];
    u16 touchHistory;
    u16 inputSource;
    u8 pad_ca4c[0x18];
    TouchPos prevTouch;
    TouchPos touchPos;
    u16 touchState;
    u16 releasedButtons;
    u16 prevHeld;
    u8 pad_ca72[2];
    u8 taskList[1];
} Ov039State;

extern Ov039State *data_ov039_020bea00;
extern u16 data_020604fc;

extern void *NNS_FndGetNextListObject_02012a38(void *list, void *object);
extern void RemoveListEntry_020bc70c(void *entry);
extern int FS_UnloadOverlayImage_0204f5dc(void *p);
extern int CopySourceBlock_020b9f7c(TouchSample *sample);
extern u16 func_0204f5ec(const u16 *source);
extern void func_ov039_020bb6e8(void);
extern void UpdateWidgetRootAndResetList_020b8c80(void *root, int keys);
extern void func_ov027_020b7dd4(void *tracker);
extern void func_ov027_020b9e60(void *table);
extern void func_ov076_020c5d10(void *arg);

void UpdateOverlayFrame_020bbb6c(void *arg)
{
    Ov039State *state = data_ov039_020bea00;
    Ov039Task *task;
    Ov039Task *next;
    TouchSample sample;
    int result;
    u16 held;
    BOOL wasTouching;
    BOOL inside;

    state->tasksPaused = TRUE;
    task = NNS_FndGetNextListObject_02012a38(state->taskList, NULL);
    if (task != NULL) {
        do {
            next = NNS_FndGetNextListObject_02012a38(state->taskList, task);
            if (task->finished) {
                RemoveListEntry_020bc70c(task);
            }
            task = next;
        } while (next != NULL);
    }
    result = 0;
    state->tasksPaused = FALSE;
    state->buttonState = 0;
    state->frameFlag = 1;
    FS_UnloadOverlayImage_0204f5dc(&state->inputSource);
    held = data_020604fc;
    CopySourceBlock_020b9f7c(&sample);
    state->touchHistory <<= 1;
    state->touchState <<= 1;
    state->releasedButtons = 0;
    state->prevTouch = state->touchPos;
    if (state->phase == 3) {
        wasTouching = FALSE;
        if (state->touchEnabled && sample.touch && (state->touchState & 3)) {
            wasTouching = TRUE;
        }
        if (sample.validity == 0 && sample.x < 0x100 && sample.y < 0xc0) {
            inside = TRUE;
        } else {
            inside = FALSE;
        }
        if (inside) {
            state->touchHistory |= sample.touch & 1;
        }
        if (state->inputEnabled && !wasTouching && (held & state->prevHeld)) {
            result = -1;
        } else if (wasTouching) {
            result = 1;
        }
        if (result == 0) {
            if (held != 0) {
                result = -1;
            } else if (sample.touch && state->touchEnabled) {
                result = 1;
            }
        }
        if (result > 0) {
            if (inside) {
                state->touchState |= sample.touch & 1;
                state->touchPos.p.x = sample.x;
                state->touchPos.p.y = sample.y;
            } else {
                state->touchState |= (state->touchState >> 1) & 1;
            }
        } else if (result < 0) {
            state->releasedButtons = func_0204f5ec(&state->inputSource);
        }
    }
    state->prevHeld = held;
    func_ov039_020bb6e8();
    if (state->layerMask & 1) {
        UpdateWidgetRootAndResetList_020b8c80(state->resources, state->buttonState);
    }
    if (state->layerMask & 4) {
        UpdateWidgetRootAndResetList_020b8c80(state->subResources, state->buttonState);
    }
    if (state->layerMask & 2) {
        func_ov027_020b7dd4(state->mainTracker);
    }
    if (state->layerMask & 8) {
        func_ov027_020b7dd4(state->subTracker);
    }
    func_ov027_020b9e60(state->tileTable);
    if (state->mode == 3 && state->primaryIndex == 6 && arg != NULL) {
        func_ov076_020c5d10(arg);
    }
}

