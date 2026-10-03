#include "nitro/types.h"

typedef struct SceneContext {
    u8 pad_00[0x23];
    s8 progress;
    u8 pad_24[2];
    s8 stage;
    u8 pad_27[0x51];
    s32 stageMode;
    u8 pad_7c[4];
    s32 refreshPending;
    s32 refreshTimer;
} SceneContext;

typedef struct PackedFileView {
    u8 data[0xc];
} PackedFileView;

typedef struct SceneState {
    s16 areaId;
    s16 posX;
    s16 posY;
    u16 flags;
    s8 fadeMode;
    u8 pad_09[0x0B];
    void *overlayTask;
    void *mainTask;
    void *subTask;
    void *menuTask;
    PackedFileView fileView;
    s32 unk_30;
    s32 unk_34;
    u8 pad_38[4];
    s32 unk_3c;
    s32 unk_40;
} SceneState;

typedef struct Ov032Globals {
    SceneContext *context;
    SceneState *scene;
} Ov032Globals;

typedef struct SceneEntryParams {
    s8 fadeMode;
    s8 areaId;
    s16 posX;
    s16 posY;
} SceneEntryParams;

typedef struct TaskDescriptorArgs {
    int unk_00;
    int heapHandle;
    int unk_08;
} TaskDescriptorArgs;

typedef int (*StateHandler)(void);

extern Ov032Globals data_ov032_020c0060;
extern u8 data_020608c8;
extern u8 data_020b52a0[];
extern u8 data_0209eb18[];
extern char data_ov032_020c0020[];
extern u8 data_ov032_020c0030[];

extern SceneState *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern BOOL func_ov001_020645c8(u32 eventId);
extern void SetupFlaggedSelectionRecords_0204f778(void);
extern void func_ov001_020633d4(void);
extern void CreateSessionNameMenu_02063ba4(void);
extern void InitMovieGraphics_020bb3a0(void);
extern void CreateSessionTask_0206c6dc(void);
extern int func_0202a158(void);
extern void *func_0202a448(void *descriptor, void *userData);
extern void func_ov001_020633a0(int mode);
extern void *CreateOverlayTask_0206a6f4(int areaId);
extern SceneContext *func_ov001_0206468c(s32 index);
extern u32 Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern void LoadPackedFileView_020ba25c(PackedFileView *view, u32 fileId, BOOL fromTail);
extern int ZeroHalfThenFree_0202cd78(u32 header);
extern void UploadGroupMenuTiles_020bbba8(int alternate);
extern void SetGroupMenuPercent_020bbb7c(int percent);
extern void LoadPzTextureParams_02066488(void);
extern void ApplySlotStyleToSession_020ba570(void);
extern int RunSceneStateMachine_020ba790(void);

StateHandler InitSceneOverlayState_020ba3e0(SceneEntryParams *params)
{
    TaskDescriptorArgs argsCopy;
    TaskDescriptorArgs args;
    u32 header;

    data_ov032_020c0060.scene = NNSi_FndGetCurrentRootHeap_0202a764();
    data_ov032_020c0060.scene->areaId = params->areaId;
    data_ov032_020c0060.scene->posX = params->posX;
    data_ov032_020c0060.scene->posY = params->posY;
    data_ov032_020c0060.scene->unk_40 = 0;
    data_ov032_020c0060.scene->flags = 0x23;
    if (func_ov001_020645c8(0x3609) || func_ov001_020645c8(0x360a)) {
        u8 previousCount = data_020608c8;
        SetupFlaggedSelectionRecords_0204f778();
        if (previousCount != data_020608c8) {
            func_ov001_020633d4();
        }
    }
    CreateSessionNameMenu_02063ba4();
    InitMovieGraphics_020bb3a0();
    CreateSessionTask_0206c6dc();
    args.heapHandle = func_0202a158();
    args.unk_00 = 0;
    args.unk_08 = 0;
    argsCopy = args;
    data_ov032_020c0060.scene->mainTask = func_0202a448(data_020b52a0, &argsCopy);
    func_ov001_020633a0(0);
    data_ov032_020c0060.scene->overlayTask = CreateOverlayTask_0206a6f4(params->areaId);
    data_ov032_020c0060.scene->fadeMode = params->fadeMode;
    data_ov032_020c0060.scene->subTask = func_0202a448(data_0209eb18, NULL);
    data_ov032_020c0060.context = func_ov001_0206468c(10);
    header = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov032_020c0020, 0xe, FALSE);
    LoadPackedFileView_020ba25c(&data_ov032_020c0060.scene->fileView, ((header + 0x8000) & 0xfffffc) << 7 | 0x80000007, TRUE);
    ZeroHalfThenFree_0202cd78(header);
    if (data_ov032_020c0060.context->stage < 0) {
        data_ov032_020c0060.scene->menuTask = (void *)-1;
    } else {
        data_ov032_020c0060.scene->menuTask = func_0202a448(data_ov032_020c0030, NULL);
        if (data_ov032_020c0060.context->stage >= 15 ||
            (data_ov032_020c0060.context->stage == 11 && data_ov032_020c0060.context->stageMode == 1 &&
             data_ov032_020c0060.context->progress == -1)) {
            UploadGroupMenuTiles_020bbba8(FALSE);
        } else {
            UploadGroupMenuTiles_020bbba8(TRUE);
        }
        if (data_ov032_020c0060.context->progress == -1) {
            SetGroupMenuPercent_020bbb7c(100);
        } else {
            SetGroupMenuPercent_020bbb7c(data_ov032_020c0060.context->progress);
        }
    }
    LoadPzTextureParams_02066488();
    data_ov032_020c0060.scene->unk_30 = 0;
    data_ov032_020c0060.context->refreshPending = 0;
    data_ov032_020c0060.context->refreshTimer = 0;
    data_ov032_020c0060.scene->unk_34 = 0;
    data_ov032_020c0060.scene->unk_3c = 8;
    ApplySlotStyleToSession_020ba570();
    return RunSceneStateMachine_020ba790;
}
