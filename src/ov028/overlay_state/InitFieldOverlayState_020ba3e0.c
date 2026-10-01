#include "nitro/types.h"

typedef struct FieldOverlayState {
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
} FieldOverlayState;

typedef struct FieldEntryParams {
    s8 fadeMode;
    s8 areaId;
    s16 posX;
    s16 posY;
} FieldEntryParams;

typedef struct TaskDescriptorArgs {
    int unk_00;
    int heapHandle;
    int unk_08;
} TaskDescriptorArgs;

typedef int (*StateHandler)(void);

extern FieldOverlayState *data_ov028_020bb380;
extern u8 data_020608c8;
extern u8 data_020b52a0[];
extern u8 data_0209eb18[];

extern FieldOverlayState *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern BOOL func_ov001_020645c8(u32 eventId);
extern void func_ov001_020645e8(u32 eventId);
extern void SetupAllSelectionRecords_0204f85c(void);
extern void func_0204f8dc(void);
extern void func_0204f98c(void);
extern void SyncSelectionRecordFromSlotEntry_0204fabc(void);
extern void func_0204fba0(void);
extern void RebuildRecordCounters_02028e6c(void);
extern void SetupFlaggedSelectionRecords_0204f778(void);
extern void func_ov001_020633d4(void);
extern void CreateSessionNameMenu_02063ba4(void);
extern void func_ov028_020baed0(void);
extern void CreateSessionTask_0206c6dc(void);
extern int func_0202a158(void);
extern void *func_0202a448(void *descriptor, void *userData);
extern void func_ov001_020633a0(int mode);
extern void *CreateOverlayTask_0206a6f4(int areaId);
extern void LoadPzTextureParams_02066488(void);
extern int func_ov028_020ba584(void);

StateHandler InitFieldOverlayState_020ba3e0(FieldEntryParams *params)
{
    BOOL flagged;
    TaskDescriptorArgs argsCopy;
    TaskDescriptorArgs args;

    data_ov028_020bb380 = NNSi_FndGetCurrentRootHeap_0202a764();
    data_ov028_020bb380->areaId = params->areaId;
    data_ov028_020bb380->posX = params->posX;
    data_ov028_020bb380->posY = params->posY;
    if (func_ov001_020645c8(0x35e3)) {
        SetupAllSelectionRecords_0204f85c();
        func_0204f8dc();
        func_0204f98c();
        SyncSelectionRecordFromSlotEntry_0204fabc();
        func_0204fba0();
        RebuildRecordCounters_02028e6c();
        func_ov001_020645e8(0x35e3);
    }
    data_ov028_020bb380->flags = 0x23;
    flagged = FALSE;
    if (func_ov001_020645c8(0x3609) || func_ov001_020645c8(0x360a)) {
        flagged = TRUE;
    }
    if (flagged) {
        u8 previousCount = data_020608c8;
        SetupFlaggedSelectionRecords_0204f778();
        if (previousCount != data_020608c8) {
            func_ov001_020633d4();
        }
    } else {
        if (data_020608c8 != 1) {
            SyncSelectionRecordFromSlotEntry_0204fabc();
        }
        data_020608c8 = 1;
    }
    CreateSessionNameMenu_02063ba4();
    func_ov028_020baed0();
    CreateSessionTask_0206c6dc();
    args.heapHandle = func_0202a158();
    args.unk_00 = 0;
    args.unk_08 = 0;
    argsCopy = args;
    data_ov028_020bb380->mainTask = func_0202a448(data_020b52a0, &argsCopy);
    func_ov001_020633a0(0);
    data_ov028_020bb380->overlayTask = CreateOverlayTask_0206a6f4(params->areaId);
    data_ov028_020bb380->fadeMode = params->fadeMode;
    data_ov028_020bb380->subTask = func_0202a448(data_0209eb18, NULL);
    LoadPzTextureParams_02066488();
    data_ov028_020bb380->counter = 0;
    return func_ov028_020ba584;
}
