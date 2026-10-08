#include "nitro/types.h"
#include "nnsys/g2d.h"

typedef struct GraphicsView {
    NNSG2dScreenData *screen;
    NNSG2dCharacterData *character;
    NNSG2dPaletteData *palette;
} GraphicsView;

typedef struct FieldParams {
    u8 header[8];
    u8 body[0x58];
    s32 mode;
} FieldParams;

typedef struct SaveSlots {
    u8 pad_00[0xA];
    u16 currentSlot;
} SaveSlots;

typedef struct FieldManager {
    u8 pad_000[0x1C];
    u8 records[0x4C];
    void *messages68;
    u32 messages6C;
    void *messages70;
    void *messages74;
    u8 pad_078[0x1FC - 0x78];
    s32 unk_1FC;
    u8 pad_200[0x460 - 0x200];
    void *paletteBuffer0;
    void *paletteBuffer2;
    void *paletteBuffer1;
    void *paletteBuffer3;
    u8 pad_470[4];
    s16 unk_474;
    u8 pad_476[6];
    s32 panelState;
    u32 unk_480_0 : 7;
    u32 modeFlag1 : 1;
    u32 modeFlag2 : 1;
    u32 unk_480_9 : 1;
    u32 modeFlag3 : 1;
    u32 unk_480_11 : 2;
    u32 modeFlag4 : 1;
    u32 unk_480_14 : 2;
    u32 paramActive : 1;
    u32 unk_480_17 : 2;
    u32 startupFlag : 1;
    u32 unk_480_20 : 12;
    u8 pad_484[0x554 - 0x484];
    u8 tickerTween[0x2C];
    s32 tickerSpeed;
    u8 textWindow[0x5D0 - 0x584];
    u8 taskList[0x60C - 0x5D0];
    u8 header[8];
} FieldManager;

typedef struct FieldManagerHandle {
    u32 active;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;
extern char sOv001_UiBtlStrLanguageP2_0209ed90[];
extern char sOv001_UiBtlBtluiP2_0209eda0[];
extern char sOv001_UiBtlBtlLanguageP2_0209edb4[];
extern char sOv001_UiBtlFaceP2_0209edc8[];
extern u8 sOv001_BTLUITASK_0209edd8[];
extern u8 OVERLAY_27_ID[];

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern void *Msg_OpenContainerAndReadHeader(const char *name, u32 mode, BOOL allocFromEnd);
extern BOOL IsModeSetOrFlag370aClear(void);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern void NNSi_FndFreeFromDefaultHeap(void *block);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern void NNS_FndInitList(void *list, u32 linkOffset);
extern void *AddFieldListener(void (*callback)(void));
extern void UpdateFieldWindowFade(void);
extern void ApplyFieldBgScroll(void);
extern void func_02029f8c(int processor, int overlayId);
extern void *func_0202c4a0(u32 fileId, u32 heapId);
extern void *Archive_LoadFile(u32 fileId, u32 heapId);
extern void InitSubScreenVramBanks(void);
extern void LoadMenuScreenGraphics(FieldManager *manager, GraphicsView *view, void *file);
extern void func_ov001_0206f1a0(FieldManager *manager);
extern void InitFieldHudWindow(FieldManager *manager, void *charData);
extern void BuildMessageLineWindow(FieldManager *manager, void *body);
extern void LoadRecordNamesAndEntryList(FieldManager *manager);
extern void InitSceneTextWindow4D8(FieldManager *manager);
extern void InitSceneTextWindow51C(FieldManager *manager);
extern void BuildChoiceWindow(FieldManager *manager, void *charData);
extern void CreateFieldHudWidgets(FieldManager *manager, GraphicsView *view);
extern void RefreshHudTagsAndIcons(FieldManager *manager);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern void func_ov001_0207b430(void);
extern void *func_ov001_0207123c(void);
extern u16 *func_ov027_020b9e10(void *widgets, int layer);
extern void FillBackgroundLayerRect(void *window, u16 *dst, int x, int y, u8 palette);
extern void InvokeForChannelOrBoth(u32 arg0, void *arg1, void *arg2, int channel);
extern void RunFieldListCallbacks(void);
extern void setDualArrayEntry(int slot, void *callback, int arg);
extern void TryEnterFieldPause(void);
extern void StepPromptTask(void);
extern void ResumeFieldAfterPause(void);
extern void func_020524fc(void *tween);
extern BOOL IsHudFlag7Set(void);
extern BOOL IsFieldFlag10Set(void);
extern BOOL IsFieldFlag8Set(void);
extern u32 ReadSessionPackedBits(int bitOffset, u32 bitCount);
extern s8 func_ov001_02068084(void);
extern BOOL IsSessionFlagSet(u32 flagId);
extern void SetParamHalf18(int value);
extern void SetParamWord20(int value);
extern SaveSlots *GetSelectionPackedValueBlock(void);
extern u32 GetParamWord20(void);
extern void AddGaugePoints(u16 slot, int arg1);
extern BOOL func_ov001_02064784(void);
extern void func_ov001_0206efac(FieldManager *manager, void *file);
extern void StartSceneMinigameTask(void);

void *InitFieldManager(FieldParams *params)
{
    FieldManager *manager;
    void *file;
    GraphicsView view;
    BOOL resetParams;
    u32 progressBits;
    SaveSlots *slots;

    manager = NNSi_FndGetCurrentRootHeap();
    data_ov001_020a04c4.manager = manager;
    MI_CpuFill8(manager, 0, 0x1358);
    data_ov001_020a04c4.active = 1;
    manager->messages74 = Msg_OpenContainerAndReadHeader(sOv001_UiBtlStrLanguageP2_0209ed90, 0xE, FALSE);
    manager->startupFlag = IsModeSetOrFlag370aClear() != FALSE;
    manager->paletteBuffer0 = NNS_FndAllocFromDefaultExpHeapEx(0x80, 4);
    manager->paletteBuffer1 = NNS_FndAllocFromDefaultExpHeapEx(0x80, 4);
    manager->paletteBuffer2 = NNS_FndAllocFromDefaultExpHeapEx(0x80, 4);
    manager->paletteBuffer3 = NNS_FndAllocFromDefaultExpHeapEx(0x80, 4);
    MI_CpuCopy8(params, manager->header, 8);
    NNS_FndInitList(manager->taskList, 4);
    AddFieldListener(UpdateFieldWindowFade);
    AddFieldListener(ApplyFieldBgScroll);
    func_02029f8c(0, (int)OVERLAY_27_ID);
    manager->messages68 = Msg_OpenContainerAndReadHeader(sOv001_UiBtlBtluiP2_0209eda0, 0xE, FALSE);
    manager->messages6C = (u32)Msg_OpenContainerAndReadHeader(sOv001_UiBtlBtlLanguageP2_0209edb4, 0xE, FALSE);
    manager->messages70 = Msg_OpenContainerAndReadHeader(sOv001_UiBtlFaceP2_0209edc8, 0xE, FALSE);
    file = func_0202c4a0((((manager->messages6C + 0x8000) & 0xFFFFFC) << 7) | 0x80000000, 0xE);
    InitSubScreenVramBanks();
    LoadMenuScreenGraphics(manager, &view, file);
    func_ov001_0206f1a0(manager);
    InitFieldHudWindow(manager, view.character->pRawData);
    BuildMessageLineWindow(manager, params->body);
    LoadRecordNamesAndEntryList(manager);
    InitSceneTextWindow4D8(manager);
    InitSceneTextWindow51C(manager);
    if (params->mode == 0) {
        BuildChoiceWindow(manager, view.character->pRawData);
    }
    switch (params->mode) {
    case 1:
        manager->modeFlag1 = 1;
        break;
    case 2:
        manager->modeFlag2 = 1;
        break;
    case 3:
        manager->modeFlag3 = 1;
        break;
    case 4:
        manager->modeFlag4 = 1;
        manager->unk_1FC = -1;
        break;
    }
    CreateFieldHudWidgets(manager, &view);
    switch (params->mode) {
    case 0:
    case 4:
        RefreshHudTagsAndIcons(manager);
        break;
    case 1:
        func_ov027_020b8230(manager->records, FindActiveRecordById(manager->records, 0x192));
        func_ov027_020b8230(manager->records, FindActiveRecordById(manager->records, 0x190));
        func_ov027_020b8230(manager->records, FindActiveRecordById(manager->records, 0x32));
        func_ov001_0207b430();
        break;
    case 2:
        RefreshHudTagsAndIcons(manager);
        func_ov027_020b8230(manager->records, FindActiveRecordById(manager->records, 5));
        break;
    case 3:
        RefreshHudTagsAndIcons(manager);
        func_ov001_0207b430();
        break;
    }
    FillBackgroundLayerRect(manager->textWindow, func_ov027_020b9e10(func_ov001_0207123c(), 9), 1, 2, 9);
    manager->panelState = 0;
    InvokeForChannelOrBoth(1, sOv001_BTLUITASK_0209edd8, RunFieldListCallbacks, 0);
    if (file != NULL) {
        NNSi_FndFreeFromDefaultHeap(file);
    }
    resetParams = FALSE;
    setDualArrayEntry(0, TryEnterFieldPause, 1);
    setDualArrayEntry(1, StepPromptTask, 0);
    setDualArrayEntry(2, ResumeFieldAfterPause, 0);
    func_020524fc(manager->tickerTween);
    manager->tickerSpeed = 0x28;
    if (!IsHudFlag7Set() && !IsFieldFlag10Set() && !IsFieldFlag8Set()) {
        progressBits = ReadSessionPackedBits(0x1A00, 2);
        if (func_ov001_02068084() == 5 && progressBits != 2
            && (!IsSessionFlagSet(0x3609) || !IsSessionFlagSet(0x360A))) {
            resetParams = TRUE;
        }
        if (resetParams) {
            SetParamHalf18(0);
            SetParamWord20(0);
        }
        slots = GetSelectionPackedValueBlock();
        manager->unk_474 = -1;
        manager->paramActive = GetParamWord20() != 0;
        AddGaugePoints(slots->currentSlot, 1);
        if (!func_ov001_02064784() && IsSessionFlagSet(0x3708)) {
            file = Archive_LoadFile((((manager->messages6C + 0x8000) & 0xFFFFFC) << 7) | 0x80000005, 0xE);
            func_ov001_0206efac(manager, file);
            NNSi_FndFreeFromDefaultHeap(file);
        }
    } else {
        SetParamHalf18(0);
        SetParamWord20(0);
    }
    return StartSceneMinigameTask;
}
