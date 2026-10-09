#include "nitro/types.h"

typedef struct {
    u8 data[0x70];
} PlayerCardSlot;

typedef struct {
    int ids[3];
} WidgetIdList;

typedef struct {
    u8 pad_00;
    u8 exitReady;
    u8 pad_02[0xb9];
    s8 choice;
    u8 pad_bc[3];
    s8 hostMode;
    u8 pad_c0[0x20];
    u8 flagsLow : 2;
    u8 touchLocked : 1;
    u8 flagsMid : 3;
    u8 widgetsHidden : 1;
    u8 slotsDirty : 1;
    u8 dirtySlots : 3;
    u8 pad_e1_bits : 5;
    u8 lowBits : 3;
    u8 holdRefresh : 1;
    u8 sharingActive : 1;
    u8 highBits : 3;
    u8 pad_e3;
    s32 state;
    u8 pad_e8[4];
    s32 slotIndex;
    u8 pad_f0[0x69d0];
    u8 manager[0x6444];
    u16 touchCursor;
    u8 pad_cf06[0x52];
    PlayerCardSlot slots[3];
} PanelContext;

extern PanelContext *data_ov015_0207e960;
extern WidgetIdList data_ov015_02079f7c;

extern void SpawnDropsPerTenUnits_0206671c(void);
extern BOOL PlaySoundEffect_0204d924(int bank, int id);
extern void func_ov015_0206f310(int slot);
extern void func_ov015_0206f688(int slot, int value);
extern u16 *func_ov002_02062000(void);
extern BOOL IsGlobalBit0Set_020632ac(void);
extern BOOL IsButtonBPressed_020632c8(void);
extern void UpdateWidgetRootOnly_020b8ca8(void *manager, u16 entry);
extern u16 GetMenuTouchHeld_02066b2c(int arg);
extern void func_ov015_020716f8(void);
extern int TestContextFlagBit_0206f460(int slot);
extern void *FindWidgetById_020b90a4(void *manager, int id);
extern BOOL IsWidgetMoveFinished_020b9100(void *widget);
extern void func_ov015_0206f22c(void *widget);
extern void SetWidgetRootTouchEnabled_020b984c(void *manager, int enabled);
extern void SetEntrySlotsVisible_020b9580(void *manager, void *widget, int visible);
extern void HidePanelOptionSlots_020718fc(void);
extern BOOL AreAllWidgetMovesFinished_020b912c(void *manager);
extern void func_ov015_02070af8(int mode);
extern void StartPanelFadeOut(int frames);
extern void func_ov015_02072cb4(void);
extern BOOL func_ov002_0206655c(void);
extern void func_ov015_0206fa98(void);
extern void UpdatePlayerCounter_0206f5d8(void);
extern u32 DispatchContextCommand_02066c78(u32 command, void *value, u32 extra, void *buffer);
extern void FreePanelBuffers_02072a54(void);
extern void StopSeqArcOrDefault_0204d960(int bank, int seq, int fade);
extern void func_020254dc(void);

void UpdatePanelShareState_02071100(void)
{
    WidgetIdList ids;
    u8 *manager;
    void *widget;
    int slot;

    SpawnDropsPerTenUnits_0206671c();
    data_ov015_0207e960->holdRefresh = 0;
    if (data_ov015_0207e960->slotsDirty) {
        PlaySoundEffect_0204d924(2, 7);
        if (data_ov015_0207e960->dirtySlots & 1) {
            func_ov015_0206f310(0);
            func_ov015_0206f688(0, 0);
        }
        if (data_ov015_0207e960->dirtySlots & 2) {
            func_ov015_0206f310(1);
            func_ov015_0206f688(1, 0);
        }
        if (data_ov015_0207e960->dirtySlots & 4) {
            func_ov015_0206f310(2);
            func_ov015_0206f688(2, 0);
        }
        data_ov015_0207e960->dirtySlots = 0;
        data_ov015_0207e960->slotsDirty = 0;
    }
    if (data_ov015_0207e960->state == 10) {
        UpdateWidgetRootOnly_020b8ca8(data_ov015_0207e960->manager, *func_ov002_02062000());
    } else if (!IsGlobalBit0Set_020632ac() && !IsButtonBPressed_020632c8() && data_ov015_0207e960->state < 100) {
        UpdateWidgetRootOnly_020b8ca8(data_ov015_0207e960->manager, 0);
    }
    switch (data_ov015_0207e960->state) {
    case 0:
        data_ov015_0207e960->touchCursor = GetMenuTouchHeld_02066b2c(0);
        data_ov015_0207e960->state = 5;
        break;
    case 5:
        if (IsButtonBPressed_020632c8() || data_ov015_0207e960->holdRefresh) {
            func_ov015_020716f8();
            data_ov015_0207e960->touchLocked = 1;
            data_ov015_0207e960->state = 10;
            return;
        }
        if (IsGlobalBit0Set_020632ac()) {
            ids = data_ov015_02079f7c;
            slot = -1;
            if (TestContextFlagBit_0206f460(0) == 1) {
                slot = 0;
            } else if (TestContextFlagBit_0206f460(1) == 1) {
                slot = 1;
            } else if (TestContextFlagBit_0206f460(2) == 1) {
                slot = 2;
            }
            if (slot != -1) {
                widget = FindWidgetById_020b90a4(data_ov015_0207e960->manager, ids.ids[slot]);
                if (IsWidgetMoveFinished_020b9100(widget)) {
                    PlaySoundEffect_0204d924(2, 1);
                    func_ov015_0206f22c(widget);
                }
            }
        }
        if (data_ov015_0207e960->widgetsHidden) {
            SetWidgetRootTouchEnabled_020b984c(data_ov015_0207e960->manager, 0);
            manager = data_ov015_0207e960->manager;
            SetEntrySlotsVisible_020b9580(manager, FindWidgetById_020b90a4(manager, 10), 0);
            manager = data_ov015_0207e960->manager;
            SetEntrySlotsVisible_020b9580(manager, FindWidgetById_020b90a4(manager, 11), 0);
            manager = data_ov015_0207e960->manager;
            SetEntrySlotsVisible_020b9580(manager, FindWidgetById_020b90a4(manager, 12), 0);
            data_ov015_0207e960->touchLocked = 1;
            data_ov015_0207e960->state = 0x14;
        }
        break;
    case 10:
        if (IsButtonBPressed_020632c8()) {
            PlaySoundEffect_0204d924(2, 2);
            data_ov015_0207e960->choice = 2;
        }
        if (data_ov015_0207e960->choice != 0) {
            data_ov015_0207e960->state = 11;
        }
        break;
    case 11:
        data_ov015_0207e960->state = 12;
        break;
    case 12:
        if (data_ov015_0207e960->choice != 0) {
            HidePanelOptionSlots_020718fc();
            if (data_ov015_0207e960->choice == 1) {
                data_ov015_0207e960->state = 100;
                return;
            }
            data_ov015_0207e960->touchLocked = 0;
            SetWidgetRootTouchEnabled_020b984c(data_ov015_0207e960->manager, 1);
            data_ov015_0207e960->state = 0;
        }
        break;
    case 15:
        if (AreAllWidgetMovesFinished_020b912c(data_ov015_0207e960->manager)) {
            data_ov015_0207e960->state = 0x14;
        }
        break;
    case 0x14:
        data_ov015_0207e960->touchLocked = 1;
        data_ov015_0207e960->state = 0x1e;
        break;
    case 0x1e:
        data_ov015_0207e960->state = 0x28;
        break;
    case 0x28:
        func_ov015_02070af8(6);
        break;
    case 100:
        StartPanelFadeOut(3);
        data_ov015_0207e960->touchLocked = 1;
        func_ov015_02072cb4();
        data_ov015_0207e960->state = 0x6e;
        break;
    case 0x6e:
        if (data_ov015_0207e960->hostMode == 1 && func_ov002_0206655c()) {
            for (slot = 0; slot < 3; slot++) {
                data_ov015_0207e960->slotIndex = slot;
                if (TestContextFlagBit_0206f460(slot)) {
                    func_ov015_0206fa98();
                    UpdatePlayerCounter_0206f5d8();
                    DispatchContextCommand_02066c78(0x80000001, &data_ov015_0207e960->slots[slot], 0, 0);
                }
            }
            FreePanelBuffers_02072a54();
            data_ov015_0207e960->sharingActive = 0;
            if (DispatchContextCommand_02066c78(5, 0, 0, 0)) {
                StopSeqArcOrDefault_0204d960(2, 0xd, 4);
            }
            func_020254dc();
            data_ov015_0207e960->exitReady = 2;
            data_ov015_0207e960->state = 0x96;
        }
        break;
    }
}
