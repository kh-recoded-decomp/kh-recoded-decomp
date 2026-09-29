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

extern FieldManagerHandle data_ov001_020a04a4;
extern char data_ov001_0209ed70[];
extern char data_ov001_0209ed80[];
extern char data_ov001_0209ed94[];
extern char data_ov001_0209eda8[];
extern u8 data_ov001_0209edb8[];
extern u8 SDK_OVERLAY_ov027_ID_0000001b[];

extern void *NNSi_FndGetCurrentRootHeap_0202a764(void);
extern void func_01ff8830(void *dst, int value, u32 size);
extern void *Msg_OpenContainerAndReadHeader_0202cc6c(const char *name, u32 mode, BOOL allocFromEnd);
extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern void *NNSi_FndAllocFromDefaultHeapEx_0202a19c(u32 size, int align);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_01ff89a8(const void *src, void *dst, u32 size);
extern void func_0201288c(void *list, u32 linkOffset);
extern void *func_ov001_0207157c(void (*callback)(void));
extern void func_ov001_0206e8c4(void);
extern void func_ov001_0206e9a8(void);
extern void func_02029f78(int processor, int overlayId);
extern void *func_0202c48c(u32 fileId, u32 heapId);
extern void *func_0202c478(u32 fileId, u32 heapId);
extern void InitSubScreenVramBanks_0206ed04(void);
extern void func_ov001_0206f064(FieldManager *manager, GraphicsView *view, void *file);
extern void func_ov001_0206f1a0(FieldManager *manager);
extern void func_ov001_0206f200(FieldManager *manager, void *charData);
extern void func_ov001_0206f324(FieldManager *manager, void *body);
extern void func_ov001_0206f484(FieldManager *manager);
extern void InitSceneTextWindow4D8_0206f694(FieldManager *manager);
extern void InitSceneTextWindow51C_0206f6dc(FieldManager *manager);
extern void BuildChoiceWindow_0206f730(FieldManager *manager, void *charData);
extern void func_ov001_0206fa74(FieldManager *manager, GraphicsView *view);
extern void func_ov001_020700d4(FieldManager *manager);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void func_ov001_0207b408(void);
extern void *func_ov001_0207123c(void);
extern u16 *UpdateWidgetLayerDefault_020b9df0(void *widgets, int layer);
extern void FillBackgroundLayerRect_02001a60(void *window, u16 *dst, int x, int y, u8 palette);
extern void InvokeForChannelOrBoth_0200110c(u32 arg0, void *arg1, void *arg2, int channel);
extern void func_ov001_0206e7e4(void);
extern void setDualArrayEntry_02025448(int slot, void *callback, int arg);
extern void func_ov001_020703a8(void);
extern void func_ov001_020704cc(void);
extern void func_ov001_020704fc(void);
extern void func_020524e8(void *tween);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL func_ov001_020728c4(void);
extern BOOL func_ov001_020728a4(void);
extern u32 func_ov001_02064574(int bitOffset, u32 bitCount);
extern s8 GetCtxModeByte_02068084(void);
extern BOOL func_ov001_020645c8(u32 flagId);
extern void SetParamHalf18_02050630(int value);
extern void SetParamWord20_02050640(int value);
extern SaveSlots *func_020505a8(void);
extern u32 GetParamWord20_02050650(void);
extern void func_ov001_02073074(u16 slot, int arg1);
extern BOOL func_ov001_02064784(void);
extern void func_ov001_0206efac(FieldManager *manager, void *file);
extern void func_ov001_02070cfc(void);

void *InitFieldManager_02070934(FieldParams *params)
{
    FieldManager *manager;
    void *file;
    GraphicsView view;
    BOOL resetParams;
    u32 progressBits;
    SaveSlots *slots;

    manager = NNSi_FndGetCurrentRootHeap_0202a764();
    data_ov001_020a04a4.manager = manager;
    func_01ff8830(manager, 0, 0x1358);
    data_ov001_020a04a4.active = 1;
    manager->messages74 = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov001_0209ed70, 0xE, FALSE);
    manager->startupFlag = IsModeSetOrFlag370aClear_0207259c() != FALSE;
    manager->paletteBuffer0 = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x80, 4);
    manager->paletteBuffer1 = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x80, 4);
    manager->paletteBuffer2 = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x80, 4);
    manager->paletteBuffer3 = NNSi_FndAllocFromDefaultHeapEx_0202a19c(0x80, 4);
    func_01ff89a8(params, manager->header, 8);
    func_0201288c(manager->taskList, 4);
    func_ov001_0207157c(func_ov001_0206e8c4);
    func_ov001_0207157c(func_ov001_0206e9a8);
    func_02029f78(0, (int)SDK_OVERLAY_ov027_ID_0000001b);
    manager->messages68 = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov001_0209ed80, 0xE, FALSE);
    manager->messages6C = (u32)Msg_OpenContainerAndReadHeader_0202cc6c(data_ov001_0209ed94, 0xE, FALSE);
    manager->messages70 = Msg_OpenContainerAndReadHeader_0202cc6c(data_ov001_0209eda8, 0xE, FALSE);
    file = func_0202c48c((((manager->messages6C + 0x8000) & 0xFFFFFC) << 7) | 0x80000000, 0xE);
    InitSubScreenVramBanks_0206ed04();
    func_ov001_0206f064(manager, &view, file);
    func_ov001_0206f1a0(manager);
    func_ov001_0206f200(manager, view.character->pRawData);
    func_ov001_0206f324(manager, params->body);
    func_ov001_0206f484(manager);
    InitSceneTextWindow4D8_0206f694(manager);
    InitSceneTextWindow51C_0206f6dc(manager);
    if (params->mode == 0) {
        BuildChoiceWindow_0206f730(manager, view.character->pRawData);
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
    func_ov001_0206fa74(manager, &view);
    switch (params->mode) {
    case 0:
    case 4:
        func_ov001_020700d4(manager);
        break;
    case 1:
        TagTracker_InvokeCallback_020b8210(manager->records, FindActiveRecordById_020b8184(manager->records, 0x192));
        TagTracker_InvokeCallback_020b8210(manager->records, FindActiveRecordById_020b8184(manager->records, 0x190));
        TagTracker_InvokeCallback_020b8210(manager->records, FindActiveRecordById_020b8184(manager->records, 0x32));
        func_ov001_0207b408();
        break;
    case 2:
        func_ov001_020700d4(manager);
        TagTracker_InvokeCallback_020b8210(manager->records, FindActiveRecordById_020b8184(manager->records, 5));
        break;
    case 3:
        func_ov001_020700d4(manager);
        func_ov001_0207b408();
        break;
    }
    FillBackgroundLayerRect_02001a60(manager->textWindow, UpdateWidgetLayerDefault_020b9df0(func_ov001_0207123c(), 9), 1, 2, 9);
    manager->panelState = 0;
    InvokeForChannelOrBoth_0200110c(1, data_ov001_0209edb8, func_ov001_0206e7e4, 0);
    if (file != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
    }
    resetParams = FALSE;
    setDualArrayEntry_02025448(0, func_ov001_020703a8, 1);
    setDualArrayEntry_02025448(1, func_ov001_020704cc, 0);
    setDualArrayEntry_02025448(2, func_ov001_020704fc, 0);
    func_020524e8(manager->tickerTween);
    manager->tickerSpeed = 0x28;
    if (!IsHudFlag7Set_020725bc() && !func_ov001_020728c4() && !func_ov001_020728a4()) {
        progressBits = func_ov001_02064574(0x1A00, 2);
        if (GetCtxModeByte_02068084() == 5 && progressBits != 2
            && (!func_ov001_020645c8(0x3609) || !func_ov001_020645c8(0x360A))) {
            resetParams = TRUE;
        }
        if (resetParams) {
            SetParamHalf18_02050630(0);
            SetParamWord20_02050640(0);
        }
        slots = func_020505a8();
        manager->unk_474 = -1;
        manager->paramActive = GetParamWord20_02050650() != 0;
        func_ov001_02073074(slots->currentSlot, 1);
        if (!func_ov001_02064784() && func_ov001_020645c8(0x3708)) {
            file = func_0202c478((((manager->messages6C + 0x8000) & 0xFFFFFC) << 7) | 0x80000005, 0xE);
            func_ov001_0206efac(manager, file);
            NNSi_FndFreeFromDefaultHeap_0202a1c4(file);
        }
    } else {
        SetParamHalf18_02050630(0);
        SetParamWord20_02050640(0);
    }
    return func_ov001_02070cfc;
}
