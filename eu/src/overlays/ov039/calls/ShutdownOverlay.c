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

extern Ov039State *data_ov039_020bea20;
extern u8 sOv039_MENUMNGR_020be81c[];
extern int func_ov039_020bd644(void);
extern void ShutdownHandlersAndExit(void);
extern void DestroyAllListEntries(void);
extern void NotifyBothOrOne(u32 a, u32 b, int index);
extern void FreePointerIfSet(void **ptr);
extern void DestroyObjectsAndRelease(void *panel);
extern void func_ov027_020b7e1c(void *widget);
extern void FreeAllocatedBuffers(void *owner);
extern void UnloadAllSubOverlays(void);
extern int FSi_DefaultStepDoneB(void *step);
extern BOOL FreeResourceBufferAndProbeHeap(FreeableResource *resource);
extern BOOL ReleaseRecordSlot(s32 slot);
extern void ReleaseRecordManager(void);
extern void PXI_Init_0202a64c(void *resource);
extern void FreeSlotPair(Ov039State *state, int slot);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void func_02029fac(int processor, int overlayId);
extern char OVERLAY_27_ID[];
extern void func_02050a58(void);
extern void OS_ResetSystem(u32 newSlot0);

void ShutdownOverlay(void)
{
    Ov039State *state = data_ov039_020bea20;
    BOOL resetOnExit = state->resetOnExit;

    if (func_ov039_020bd644() != -1) {
        state->nextEntry = -1;
        state->menuActive = TRUE;
        ShutdownHandlersAndExit();
    }
    DestroyAllListEntries();
    NotifyBothOrOne(1, (u32)sOv039_MENUMNGR_020be81c, -1);
    FreePointerIfSet(&state->extraBuffer);
    DestroyObjectsAndRelease(state->panelA);
    DestroyObjectsAndRelease(state->panelB);
    func_ov027_020b7e1c(state->widgetA);
    func_ov027_020b7e1c(state->widgetB);
    FreeAllocatedBuffers(state->screenLayers);
    UnloadAllSubOverlays();
    FSi_DefaultStepDoneB(state->stepState);
    FreeResourceBufferAndProbeHeap(&data_ov039_020bea20->resources[0]);
    FreeResourceBufferAndProbeHeap(&data_ov039_020bea20->resources[1]);
    FreeResourceBufferAndProbeHeap(&data_ov039_020bea20->resources[2]);
    FreeResourceBufferAndProbeHeap(&data_ov039_020bea20->resources[3]);
    ReleaseRecordSlot(2);
    ReleaseRecordSlot(0);
    ReleaseRecordSlot(1);
    ReleaseRecordManager();
    PXI_Init_0202a64c(state->sharedResource);
    FreeSlotPair(state, 0);
    FreeSlotPair(state, 2);
    if (state != NULL) {
        NNSi_FndFreeFromDefaultHeap(state);
    }
    func_02029fac(0, (int)OVERLAY_27_ID);
    func_02050a58();
    if (resetOnExit) {
        OS_ResetSystem(-2);
    }
}
