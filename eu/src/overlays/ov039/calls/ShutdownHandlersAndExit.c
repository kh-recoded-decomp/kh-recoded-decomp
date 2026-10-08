#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xc994];
    int returnScene;
    void *primaryWork;
    void *menuWork;
    u8 pad_c9a0[0x1c];
    int nextEntry;
    u8 pad_c9c0[0x4c];
    BOOL menuActive;
    u8 pad_ca10[0x1c];
    int unk_ca2c;
    int menuReady;
    u8 pad_ca34[0x4c];
    BOOL altExit;
} Ov039State;

extern Ov039State *data_ov039_020bea20;
extern void DestroyAllListEntries(void);
extern void CloseSecondarySubOverlay(void *work);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern BOOL LoadBgLayerSet4(void);
extern void UnloadSecondarySubOverlay(void);
extern void func_ov039_020bcf10(void *work);
extern void LoadBgLayerSet3(void);
extern void UnloadPrimarySubOverlay(void);
extern void RuntimeState_SetMode(int value);
extern int GetCurrentSceneId(void);
extern void func_ov000_02063668(int value);
extern void HasOv029ObjectField28(int mode);
extern void func_ov039_020bab30(void);

void ShutdownHandlersAndExit(void)
{
    Ov039State *state = data_ov039_020bea20;
    int mode;

    DestroyAllListEntries();
    if (state->menuActive) {
        CloseSecondarySubOverlay(state->menuWork);
        if (state->menuWork != NULL) {
            NNSi_FndFreeFromDefaultHeap(state->menuWork);
            state->menuWork = NULL;
        }
        state->menuReady = 0;
        LoadBgLayerSet4();
        UnloadSecondarySubOverlay();
    }
    func_ov039_020bcf10(state->primaryWork);
    if (state->primaryWork != NULL) {
        NNSi_FndFreeFromDefaultHeap(state->primaryWork);
        state->primaryWork = NULL;
    }
    mode = 0;
    state->unk_ca2c = mode;
    LoadBgLayerSet3();
    UnloadPrimarySubOverlay();
    if (state->nextEntry == -1) {
        RuntimeState_SetMode(0);
        if (GetCurrentSceneId() == 1) {
            func_ov000_02063668(state->altExit ? 2 : 1);
            return;
        }
        if (GetCurrentSceneId() == 4) {
            return;
        }
        if (state->returnScene == 3) {
            if (state->altExit) {
                mode = 1;
            }
        } else if (state->returnScene == 6) {
            if (state->altExit) {
                mode = 1;
            }
        }
        HasOv029ObjectField28(mode);
        return;
    }
    if (state->menuActive) {
        func_ov039_020bab30();
    }
    RuntimeState_SetMode(1);
}
