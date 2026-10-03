#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct MovieOverlayState {
    s16 areaId;
    s16 posX;
    s16 posY;
    u16 flags;
    s8 fadeMode;
    u8 pad_09[0x0B];
    void *overlayTask;
    void *mainTask;
    void *subTask;
    int counter;
    VecFx32 upVector;
    int frame;
} MovieOverlayState;

typedef struct MovieEntryParams {
    s8 fadeMode;
    s8 areaId;
    s16 posX;
    s16 posY;
} MovieEntryParams;

typedef struct TaskDescriptorArgs {
    int unk_00;
    int heapHandle;
    int unk_08;
} TaskDescriptorArgs;

typedef struct {
    u8 pad_00[2];
    u16 current;
    u16 initial;
} SelectionRecord;

typedef int (*StateHandler)(void);

extern MovieOverlayState *g_moviePlayerCtx_020bd000;
extern u8 data_ov021_020b52a0[];
extern u8 data_ov001_0209eb18[];

extern MovieOverlayState *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_ov030_020bc424(void);
extern void CreateSessionNameMenu_02063ba4(void);
extern void SetupMovieDisplay_020bab00(void);
extern void CreateSessionTask_0206c6dc(void);
extern void func_ov001_020633a0(int mode);
extern void *CreateOverlayTask_0206a6f4(int areaId);
extern int func_0202a158(void);
extern void *func_0202a448(void *descriptor, void *userData);
extern void LoadPzTextureParams_02066488(void);
extern SelectionRecord *GetOverlaySelectionRecord_0204f768(int index);
extern void ClearFieldCounters_02064dc8(void);
extern int RunSceneStateMachine_020ba4c0(void);

StateHandler InitMovieOverlayState_020ba3e0(MovieEntryParams *params)
{
    TaskDescriptorArgs argsCopy;
    VecFx32 upVector;
    TaskDescriptorArgs args;
    int index;
    int heapHandle;

    g_moviePlayerCtx_020bd000 = NNSi_FndGetCurrentRootHeap_0202a764();
    g_moviePlayerCtx_020bd000->areaId = params->areaId;
    g_moviePlayerCtx_020bd000->posX = params->posX;
    g_moviePlayerCtx_020bd000->posY = params->posY;
    upVector.x = 0;
    upVector.y = 0;
    upVector.z = FX32_ONE;
    g_moviePlayerCtx_020bd000->upVector = upVector;
    g_moviePlayerCtx_020bd000->flags = 0x23;
    func_ov030_020bc424();
    CreateSessionNameMenu_02063ba4();
    SetupMovieDisplay_020bab00();
    CreateSessionTask_0206c6dc();
    func_ov001_020633a0(0);
    g_moviePlayerCtx_020bd000->overlayTask = CreateOverlayTask_0206a6f4(params->areaId);
    g_moviePlayerCtx_020bd000->fadeMode = params->fadeMode;
    heapHandle = func_0202a158();
    args.unk_00 = 1;
    args.heapHandle = heapHandle;
    args.unk_08 = 0;
    argsCopy = args;
    g_moviePlayerCtx_020bd000->mainTask = func_0202a448(data_ov021_020b52a0, &argsCopy);
    g_moviePlayerCtx_020bd000->subTask = func_0202a448(data_ov001_0209eb18, NULL);
    LoadPzTextureParams_02066488();
    g_moviePlayerCtx_020bd000->frame = 0;
    for (index = 0; index < 3; index++) {
        GetOverlaySelectionRecord_0204f768(index)->current = GetOverlaySelectionRecord_0204f768(index)->initial;
    }
    ClearFieldCounters_02064dc8();
    g_moviePlayerCtx_020bd000->counter = 0;
    return RunSceneStateMachine_020ba4c0;
}
