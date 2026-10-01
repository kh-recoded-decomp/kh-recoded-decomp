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

extern Ov039State *data_ov039_020bea00;
extern void DestroyAllListEntries_020bc788(void);
extern void func_ov039_020bd00c(void *work);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern BOOL StopOv038SoundStream_020bac24(void);
extern void func_ov039_020bcf88(void);
extern void func_ov039_020bcef0(void *work);
extern void func_ov039_020bab8c(void);
extern void func_ov039_020bce6c(void);
extern void func_ov039_020baae0(int value);
extern int func_02025658(void);
extern void World_SetField4_02063668(int value);
extern void func_020baa40(int mode);
extern void func_ov039_020bab10(void);

void ShutdownHandlersAndExit_020bb540(void)
{
    Ov039State *state = data_ov039_020bea00;
    int mode;

    DestroyAllListEntries_020bc788();
    if (state->menuActive) {
        func_ov039_020bd00c(state->menuWork);
        if (state->menuWork != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(state->menuWork);
            state->menuWork = NULL;
        }
        state->menuReady = 0;
        StopOv038SoundStream_020bac24();
        func_ov039_020bcf88();
    }
    func_ov039_020bcef0(state->primaryWork);
    if (state->primaryWork != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(state->primaryWork);
        state->primaryWork = NULL;
    }
    mode = 0;
    state->unk_ca2c = mode;
    func_ov039_020bab8c();
    func_ov039_020bce6c();
    if (state->nextEntry == -1) {
        func_ov039_020baae0(0);
        if (func_02025658() == 1) {
            World_SetField4_02063668(state->altExit ? 2 : 1);
            return;
        }
        if (func_02025658() == 4) {
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
        func_020baa40(mode);
        return;
    }
    if (state->menuActive) {
        func_ov039_020bab10();
    }
    func_ov039_020baae0(1);
}
