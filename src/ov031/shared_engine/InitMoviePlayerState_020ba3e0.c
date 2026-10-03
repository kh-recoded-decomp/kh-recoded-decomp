#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct MovieOverlayState {
    s16 areaId;
    s16 posX;
    s16 posY;
    u16 flags;
    u8 pad_08[0x8];
    void *overlayTask;
    void *mainTask;
    s32 currentState;
    VecFx32 upVector;
    s32 position;
    u8 pad_2c[0x4];
    s32 target;
    u8 pad_34[0x8];
    s8 fadeMode;
    u8 pad_3d[0x13];
    void *records;
    u8 pad_54[0x68];
    s32 frameCount;
    u8 pad_c0[0x344];
    void *pendingList;
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

typedef s32 (*StateHandler)(void);

extern MovieOverlayState *g_activeState_020bc800;
extern u8 data_ov021_020b52a0[];

extern MovieOverlayState *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void ResetSelectionSlots_020bb38c(void);
extern void CreateSessionNameMenu_02063ba4(void);
extern void InitMovieGraphics_020bb3cc(void);
extern void CreateSessionTask_0206c6dc(void);
extern void func_ov001_020633a0(int mode);
extern void *CreateOverlayTask_0206a6f4(int areaId);
extern int func_0202a158(void);
extern void *func_0202a448(void *descriptor, void *userData);
extern void LoadPzTextureParams_02066488(void);
extern void ClearFieldCounters_02064dc8(void);
extern s32 RunStateMachine_020ba4b4(void);

StateHandler InitMoviePlayerState_020ba3e0(MovieEntryParams *params)
{
    TaskDescriptorArgs argsCopy;
    VecFx32 upVector;
    TaskDescriptorArgs args;
    int heapHandle;

    g_activeState_020bc800 = NNSi_FndGetCurrentRootHeap_0202a764();
    g_activeState_020bc800->areaId = params->areaId;
    g_activeState_020bc800->posX = params->posX;
    g_activeState_020bc800->posY = params->posY;
    upVector.x = 0;
    upVector.y = 0;
    upVector.z = FX32_ONE;
    g_activeState_020bc800->upVector = upVector;
    g_activeState_020bc800->position = 0x333;
    g_activeState_020bc800->target = g_activeState_020bc800->position;
    g_activeState_020bc800->frameCount = 0;
    g_activeState_020bc800->flags = 0x23;
    ResetSelectionSlots_020bb38c();
    CreateSessionNameMenu_02063ba4();
    InitMovieGraphics_020bb3cc();
    g_activeState_020bc800->pendingList = NULL;
    CreateSessionTask_0206c6dc();
    func_ov001_020633a0(1);
    g_activeState_020bc800->overlayTask = CreateOverlayTask_0206a6f4(params->areaId);
    g_activeState_020bc800->fadeMode = params->fadeMode;
    heapHandle = func_0202a158();
    args.unk_00 = 2;
    args.heapHandle = heapHandle;
    args.unk_08 = 0;
    argsCopy = args;
    g_activeState_020bc800->mainTask = func_0202a448(data_ov021_020b52a0, &argsCopy);
    LoadPzTextureParams_02066488();
    ClearFieldCounters_02064dc8();
    g_activeState_020bc800->records = NULL;
    g_activeState_020bc800->currentState = 0;
    return RunStateMachine_020ba4b4;
}
