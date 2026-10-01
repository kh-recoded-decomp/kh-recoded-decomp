#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    void *buffer;
} FreeableResource;

typedef struct {
    u8 panelA[0x647c];
    u8 panelB[0x647c];
    u8 widgetA[0x4c];
    u8 widgetB[0x4c];
    void *sharedResource;
    u8 pad_c994[0xc];
    u8 screenLayers[0x1c];
    int nextEntry;
    u8 pad_c9c0[0x4c];
    BOOL menuActive;
    u8 pad_ca10[0x24];
    BOOL resetOnExit;
    u8 pad_ca38[0x12];
    u8 stepState[0x3a];
    FreeableResource resources[4];
    u8 pad_cab4[0x10];
    void *extraBuffer;
} Ov039State;

extern Ov039State *data_ov039_020bea00;
extern u8 data_ov039_020be7fc[];
extern int func_ov039_020bd624(void);
extern void ShutdownHandlersAndExit_020bb540(void);
extern void DestroyAllListEntries_020bc788(void);
extern void NotifyBothOrOne_02001154(u32 a, u32 b, int index);
extern void FreePointerIfSet_020ba294(void **ptr);
extern void func_ov027_020b8c58(void *panel);
extern void func_ov027_020b7dfc(void *widget);
extern void FreeAllocatedBuffers_020b9a60(void *owner);
extern void func_ov039_020bcdd0(void);
extern int func_0204f5d8(void *step);
extern BOOL FreeResourceBufferAndProbeHeap_02001474(FreeableResource *resource);
extern BOOL ReleaseRecordSlot_02051dfc(s32 slot);
extern void func_02051cdc(void);
extern void func_0202a638(void *resource);
extern void func_ov039_020bb824(Ov039State *state, int slot);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_02029f98(int processor, int overlayId);
extern char OVERLAY_27_ID_0000001b[];
extern void func_02050a44(void);
extern void func_02004a60(u32 newSlot0);

void ShutdownOverlay_020bbe60(void)
{
    Ov039State *state = data_ov039_020bea00;
    BOOL resetOnExit = state->resetOnExit;

    if (func_ov039_020bd624() != -1) {
        state->nextEntry = -1;
        state->menuActive = TRUE;
        ShutdownHandlersAndExit_020bb540();
    }
    DestroyAllListEntries_020bc788();
    NotifyBothOrOne_02001154(1, (u32)data_ov039_020be7fc, -1);
    FreePointerIfSet_020ba294(&state->extraBuffer);
    func_ov027_020b8c58(state->panelA);
    func_ov027_020b8c58(state->panelB);
    func_ov027_020b7dfc(state->widgetA);
    func_ov027_020b7dfc(state->widgetB);
    FreeAllocatedBuffers_020b9a60(state->screenLayers);
    func_ov039_020bcdd0();
    func_0204f5d8(state->stepState);
    FreeResourceBufferAndProbeHeap_02001474(&data_ov039_020bea00->resources[0]);
    FreeResourceBufferAndProbeHeap_02001474(&data_ov039_020bea00->resources[1]);
    FreeResourceBufferAndProbeHeap_02001474(&data_ov039_020bea00->resources[2]);
    FreeResourceBufferAndProbeHeap_02001474(&data_ov039_020bea00->resources[3]);
    ReleaseRecordSlot_02051dfc(2);
    ReleaseRecordSlot_02051dfc(0);
    ReleaseRecordSlot_02051dfc(1);
    func_02051cdc();
    func_0202a638(state->sharedResource);
    func_ov039_020bb824(state, 0);
    func_ov039_020bb824(state, 2);
    if (state != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(state);
    }
    func_02029f98(0, (int)OVERLAY_27_ID_0000001b);
    func_02050a44();
    if (resetOnExit) {
        func_02004a60(-2);
    }
}
