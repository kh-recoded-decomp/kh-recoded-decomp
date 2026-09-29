#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x28];
    u16 flags;
    u8 pad_2A[2];
    s32 unk_2C;
} FieldEntry;

typedef struct {
    u8 pad_000[0x34];
    u8 layer[0x34];
    s32 unk_68;
    u8 pad_06C[0x5C];
    s32 unk_C8;
    u8 pad_0CC[0x20];
    s32 entryIndex;
    u8 pad_0F0[0xC];
    s32 state;
    u8 pad_100[0x4];
    s32 mode;
    s32 idleCount;
    u8 pad_10C[0x10];
    void *cursorRecord;
    u8 pad_120[0x8];
    s32 unk_128;
    u8 pad_12C[0x8];
    s32 unk_134;
} FieldMenu;

extern int func_ov001_0207123c(void);
extern u16 *UpdateWidgetLayerDefault_020b9df0(int layers, int layerIndex);
extern void *GetSceneTagTracker_020711b0(void);
extern FieldEntry *func_ov001_02075348(FieldMenu *menu, s32 index, s32 slot, s32 *outValue);
extern void func_ov001_02075b48(FieldMenu *menu, FieldEntry *entry, u16 *screen, s32 slot, s32 kind, s32 row, s32 palette);
extern void func_ov027_020b822c(void *tracker, void *record, u16 x, u16 y);
extern void func_ov001_02075db8(FieldMenu *menu);
extern void func_ov001_02075ccc(FieldMenu *menu, void *tracker);
extern BOOL func_ov001_020728a4(void);
extern void *FindActiveRecordById_020b8184(void *pool, u16 recordId);
extern void TagTracker_InvokeCallback_020b8210(void *pool, void *record);
extern void InvokeCallback40_020b8268(void *pool, void *record);
extern void FillBackgroundLayerRect_02001a60(void *info, u16 *dst, int x, int y, u8 palette);

static inline BOOL IsEntryActive(FieldEntry *entry)
{
    BOOL active = FALSE;
    if ((entry->flags & 1) && (entry->flags & 4)) {
        active = TRUE;
    }
    return active;
}

static inline BOOL IsEntrySelectable(FieldMenu *menu, FieldEntry *entry)
{
    BOOL selectable = FALSE;
    if (IsEntryActive(entry) && menu->unk_68 != 10) {
        selectable = TRUE;
    }
    return selectable;
}

void RefreshFieldMenuSlots_0207651c(FieldMenu *menu, s32 level)
{
    u16 *screen = UpdateWidgetLayerDefault_020b9df0(func_ov001_0207123c(), 0xb);
    void *tracker = GetSceneTagTracker_020711b0();
    BOOL ready = FALSE;
    s32 i = -1;
    s32 limit = level * 3 - 7;
    FieldEntry *entry;
    s32 kind;
    s32 slotIndex;

    do {
        if (menu->unk_C8 < 3 && i == -1) {
            switch (menu->mode) {
            case 0:
                slotIndex = 2;
                entry = func_ov001_02075348(menu, 2, 1, NULL);
                break;
            case 1:
                entry = func_ov001_02075348(menu, 0xe, 1, NULL);
                break;
            case 2:
                entry = func_ov001_02075348(menu, 2, 1, NULL);
                break;
            }
        } else {
            entry = func_ov001_02075348(menu, menu->entryIndex, i + 1, &slotIndex);
        }
        switch (i) {
        case -1:
            if (menu->unk_C8 < 3) {
                kind = 1;
            } else {
                kind = limit;
                if (kind >= 1) {
                    kind = 1;
                    ready = TRUE;
                }
            }
            break;
        case 0:
            if (menu->unk_C8 < 3) {
                kind = limit;
                if ((entry->flags & 1) && (entry->flags & 4) && menu->unk_68 != 10) {
                    if (kind >= 2) {
                        kind = 2;
                        ready = TRUE;
                    }
                } else if (limit >= 1) {
                    kind = 1;
                    ready = TRUE;
                }
            } else {
                kind = IsEntrySelectable(menu, entry) ? 2 : 1;
            }
            break;
        case 1:
            kind = 1;
            break;
        }
        func_ov001_02075b48(menu, entry, screen, i + 1, kind, i * 2 + 0x12, kind == 2 ? 1 : 9);
        i++;
    } while (i < 2);

    func_ov027_020b822c(tracker, menu->cursorRecord, 0, 0x14);
    entry = func_ov001_02075348(menu, menu->entryIndex, 1, NULL);
    if (menu->unk_C8 < 3) {
        func_ov027_020b822c(tracker, menu->cursorRecord, 0, 0x10);
        if (ready) {
            if (menu->unk_134 != 0 && entry->unk_2C != 0) {
                func_ov001_02075db8(menu);
            } else {
                menu->state = 0;
                menu->idleCount = 0;
                if ((entry->flags & 1) && (entry->flags & 4) && menu->unk_68 != 10) {
                    func_ov001_02075ccc(menu, tracker);
                } else {
                    func_ov027_020b822c(tracker, menu->cursorRecord, 0, 0x12);
                }
            }
        } else {
            menu->idleCount++;
        }
    } else {
        if ((entry->flags & 1) && (entry->flags & 4) && menu->unk_68 != 10) {
            func_ov001_02075ccc(menu, tracker);
        } else {
            func_ov027_020b822c(tracker, menu->cursorRecord, 0, 0x12);
        }
        if (ready) {
            if (menu->unk_134 != 0 && entry->unk_2C != 0) {
                func_ov001_02075db8(menu);
            } else {
                menu->state = 0;
                menu->idleCount = 0;
                menu->unk_134 = 0;
            }
            func_ov027_020b822c(tracker, menu->cursorRecord, 0, 0x10);
        } else {
            menu->idleCount++;
        }
    }

    if (menu->unk_68 != 10) {
        TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0x21));
        if (func_ov001_020728a4()) {
            TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, menu->mode == 1 ? 0xd : 0xe));
        } else {
            TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0xc));
        }
    } else {
        TagTracker_InvokeCallback_020b8210(tracker, FindActiveRecordById_020b8184(tracker, 0x24));
        InvokeCallback40_020b8268(tracker, FindActiveRecordById_020b8184(tracker, 0xc));
    }
    FillBackgroundLayerRect_02001a60(menu->layer, screen, 2, 0x16, menu->unk_128 != 0 ? 9 : 10);
}
