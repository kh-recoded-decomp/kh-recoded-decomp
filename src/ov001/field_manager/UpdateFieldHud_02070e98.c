#pragma opt_propagation off
#include "nitro/types.h"

typedef struct TextWindow {
    u8 data[0x34];
} TextWindow;

typedef struct FieldManager {
    u8 pad_000[0x1c];
    u8 records[0x1dc];
    s32 choiceMenuActive;
    TextWindow headerWindow;
    union {
        TextWindow slotWindows[3];
        struct {
            u8 pad_00[0x10];
            s32 highlightDrawn;
            u8 pad_14[0x8];
            u32 highlightFrame;
        } choice;
    } u;
    u8 pad_2cc[0x18];
    u64 noticeStartTick;
    u64 noticeDuration;
    u8 noticeEffect[0x188];
    s32 panelState;
    u32 isSliding : 1;
    u32 unk_480_1 : 3;
    u32 isPaused : 1;
    u32 unk_480_5 : 4;
    u32 showSlotRecords : 1;
    u32 unk_480_10 : 1;
    u32 flag3724Shown : 1;
    u32 flag3723Shown : 1;
    u32 unk_480_13 : 6;
    u32 menuSuspended : 1;
    u32 slotLabelsDirty : 1;
    u32 unk_480_21 : 11;
    u8 pad_484[0x174];
    void *slotRecords[3];
    u8 pad_604[0x4];
    s32 hudState;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

typedef void (*PanelStateHandler)(FieldManager *manager);

typedef struct PanelStateHandlers {
    PanelStateHandler handlers[4];
} PanelStateHandlers;

typedef struct WidgetLayerIds {
    int ids[3];
} WidgetLayerIds;

extern FieldManagerHandle data_ov001_020a04a4;
extern const PanelStateHandlers data_ov001_0209eccc;
extern const WidgetLayerIds data_ov001_0209dbc4;

extern u64 OS_GetTick_02003fd4(void);
extern u32 func_01ff80d4(void);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void InvokeCallback40_020b8268(void *pool, void *record);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void func_ov027_020b81e0(void *pool, void *record, s16 y);
extern void func_ov027_020b7dd4(void *pool);
extern void func_ov027_020b9e30(FieldManager *manager, int layer);
extern void func_ov027_020b9e60(FieldManager *manager);
extern void func_ov001_0207036c(FieldManager *manager);
extern void func_ov001_0207023c(FieldManager *manager);
extern void ClearChoiceHighlight_020701a8(FieldManager *manager);
extern BOOL func_ov001_020728a4(void);
extern BOOL IsHudFlag9Set_02072884(void);
extern BOOL func_ov001_020645c8(u32 flagId);
extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern void SetFieldMenuSuspended_02077b90(int enable, int arg1);
extern void func_020cf048(void *effect);
extern u32 func_ov001_0207b3cc(void);
extern int CountAssignedFieldSlots_0207169c(void);
extern void *func_ov001_020736b4(int layer);
extern void FillBackgroundLayerRect_02001a60(TextWindow *window, void *dst, int x, u16 y, u8 palette);
extern void Text_UploadTileBuffer_02001520(TextWindow *window);

int UpdateFieldHud_02070e98(void)
{
    FieldManager *manager;
    PanelStateHandler *handlers;
    PanelStateHandler handler;
    PanelStateHandlers table;
    FieldManagerHandle *handle = &data_ov001_020a04a4;
    const PanelStateHandlers *source = &data_ov001_0209eccc;
    manager = handle->manager;
    table = *source;
    handlers = table.handlers;

    if (manager->isPaused) {
        return 0;
    }
    handler = handlers[manager->panelState];
    if (handler != NULL) {
        handler(manager);
    }
    func_ov001_0207036c(manager);
    func_ov001_0207023c(manager);
    if (manager->noticeStartTick != 0) {
        if (OS_GetTick_02003fd4() - manager->noticeStartTick > manager->noticeDuration) {
            InvokeCallback40_020b8268(manager->records, FindActiveRecordById_020b8184(manager->records, 6));
            manager->noticeStartTick = 0;
        }
    }
    if (manager->choiceMenuActive != 0 && manager->u.choice.highlightDrawn != 0) {
        if (func_01ff80d4() >= manager->u.choice.highlightFrame + 0x5a) {
            ClearChoiceHighlight_020701a8(manager);
        }
    }
    if (func_ov001_020728a4() && !IsHudFlag9Set_02072884() && manager->panelState == 0) {
        if (manager->flag3724Shown) {
            if (!func_ov001_020645c8(0x3724)) {
                InvokeCallback40_020b8268(manager->records, FindActiveRecordById_020b8184(manager->records, 0x53));
                manager->flag3723Shown = 0;
            }
        } else {
            if (func_ov001_020645c8(0x3724)) {
                TagTracker_InvokeCallback_020b8210(manager->records, FindActiveRecordById_020b8184(manager->records, 0x53));
                manager->flag3724Shown = 1;
            }
        }
        if (manager->flag3723Shown) {
            if (!func_ov001_020645c8(0x3723)) {
                InvokeCallback40_020b8268(manager->records, FindActiveRecordById_020b8184(manager->records, 0x54));
                manager->flag3723Shown = 0;
            }
        } else {
            if (func_ov001_020645c8(0x3723)) {
                TagTracker_InvokeCallback_020b8210(manager->records, FindActiveRecordById_020b8184(manager->records, 0x54));
                manager->flag3723Shown = 1;
            }
        }
    }
    if (!manager->menuSuspended && IsModeSetOrFlag370aClear_0207259c()) {
        SetFieldMenuSuspended_02077b90(0, 0);
        manager->menuSuspended = 1;
    }
    if (manager->showSlotRecords == 1) {
        func_020cf048(manager->noticeEffect);
    }
    func_ov027_020b7dd4(manager->records);
    if (func_ov001_0207b3cc() == 2) {
        WidgetLayerIds layers = data_ov001_0209dbc4;
        u32 i;

        i = 0;
        do {
            func_ov027_020b9e30(manager, layers.ids[i]);
        } while (++i < 3);
    }
    if (manager->showSlotRecords && manager->slotLabelsDirty) {
        int slotCount = CountAssignedFieldSlots_0207169c();
        int lineCount;
        void *charBase = func_ov001_020736b4(0xb);
        int line;

        TagTracker_InvokeCallback_020b8210(manager->records,
                                           FindActiveRecordById_020b8184(manager->records, (u16)(slotCount + 0x50)));
        lineCount = slotCount + 1;
        line = 0;
        if (lineCount > 0) do {
            FillBackgroundLayerRect_02001a60(&manager->u.slotWindows[line], charBase, 0x12, 0x16 - slotCount * 2 + line * 2, 0xf);
            Text_UploadTileBuffer_02001520(&manager->u.slotWindows[line]);
            if (manager->slotRecords[line] != NULL) {
                func_ov027_020b81e0(manager->records, manager->slotRecords[line], 0x16 - slotCount * 2 + line * 2);
                TagTracker_InvokeCallback_020b8210(manager->records, *(void **)((u8 *)manager + 0x5f8 + line * 4));
            }
        } while (++line < lineCount);
        manager->slotLabelsDirty = 0;
    }
    switch (manager->hudState) {
    case 0:
    case 4:
    case 5:
    case 9:
        break;
    default:
        manager->hudState++;
        break;
    }
    func_ov027_020b9e60(manager);
    return 0;
}
