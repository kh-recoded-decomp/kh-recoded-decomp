#include "nitro/types.h"

#ifndef FIELD_MENU_FLAGS_QUALIFIER
#define FIELD_MENU_FLAGS_QUALIFIER
#endif

typedef struct {
    s32 active;
    u32 unk_04;
    s32 id;
    u32 unk_0C;
    s32 state;
    u8 pad_14[0x14];
    FIELD_MENU_FLAGS_QUALIFIER u16 flags;
    u16 timer;
} FieldMenuEntry;

typedef struct {
    u8 pad_000[0xb8];
    u8 entryList[0x10];
    s32 unk_C8;
    u8 pad_0CC[0xc];
    s32 remaining;
    u8 pad_0DC[0x10];
    s32 cursorIndex;
    u8 pad_0F0[0x8];
    s32 selectedIndex;
    u8 pad_0FC[0x8];
    s32 mode;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern void *GetSceneTagTracker_020711b0(void);
extern FieldMenuEntry *FindFieldMenuEntryById_020754d8(FieldMenu *menu, int listKind, int entryId, s32 *outIndex);
extern FieldMenuEntry *CycleMenuEntry_02075348(FieldMenu *menu, s32 index, s32 step, s32 *outIndex);
extern void *func_ov027_020b8390(void *pool, int tag);
extern void func_ov027_020b83e8(void *pool, void *record, int arg);
extern void *FindActiveRecordById_020b8184(void *pool, u32 recordId);
extern void InvokeCallback40_020b8268(void *pool, void *record);
extern void func_ov001_02078360(int a, int b);
extern void RemoveIntrusiveListObject_020129d8(void *list, void *object);
extern void func_ov001_020769f4(FieldMenu *menu);
extern BOOL IsFieldFlag8Set_020728a4(void);
extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL IsFieldFlag10Set_020728c4(void);

#ifndef FIELD_MENU_FLAGS_KEEP_MASK
#define FIELD_MENU_FLAGS_KEEP_MASK (~1)
#endif
#ifndef FIELD_MENU_CLEARED_ID
#define FIELD_MENU_CLEARED_ID 0xffff
#endif

void TickFieldMenuEntry_02078000(int listKind, int entryId) {
    FieldMenu *menu = data_ov001_020a04b0.menu;
    void *pool = GetSceneTagTracker_020711b0();
    FieldMenuEntry *entry = FindFieldMenuEntryById_020754d8(menu, listKind, entryId, NULL);
    s32 nextIndex;

    if (entry == NULL) {
        return;
    }
    if (entry->state != 3) {
        if (entry->state == 5) {
            if (entry->timer != 0) {
                entry->timer--;
            }
            if (entry->timer == 0) {
                CycleMenuEntry_02075348(menu, menu->selectedIndex, 2, &nextIndex);
                menu->remaining--;
                if (menu->remaining <= 0) {
                    menu->remaining = 0;
                    func_ov027_020b83e8(pool, func_ov027_020b8390(pool, 0x12), 0);
                    InvokeCallback40_020b8268(pool, FindActiveRecordById_020b8184(pool, 0x55));
                    func_ov001_02078360(0, 1);
                } else if (menu->mode == 1) {
                    menu->unk_C8 = menu->remaining;
                }
                entry->flags &= FIELD_MENU_FLAGS_KEEP_MASK;
                entry->flags |= 8;
                entry->id = FIELD_MENU_CLEARED_ID;
                entry->active = 0;
                RemoveIntrusiveListObject_020129d8(menu->entryList, entry);
                if (menu->mode == 1) {
                    if (CycleMenuEntry_02075348(menu, menu->selectedIndex, 2, &nextIndex) == NULL) {
                        nextIndex = 0;
                    }
                    menu->selectedIndex = nextIndex;
                    menu->cursorIndex = menu->selectedIndex;
                }
                func_ov001_020769f4(menu);
                return;
            }
            entry->active = 0;
        } else if (IsFieldFlag8Set_020728a4()) {
            entry->flags &= FIELD_MENU_FLAGS_KEEP_MASK;
            entry->active = 0;
        } else if (IsModeSetOrFlag370aClear_0207259c() && !IsHudFlag7Set_020725bc() && !IsFieldFlag10Set_020728c4()) {
            entry->flags &= FIELD_MENU_FLAGS_KEEP_MASK;
            entry->active = 0;
        } else {
            if (entry->timer != 0) {
                entry->timer--;
            }
            if (entry->timer == 0) {
                entry->timer = 0;
                if (entryId == CycleMenuEntry_02075348(menu, menu->cursorIndex, 1, NULL)->id) {
                    menu->unk_C8 = 0;
                }
                func_ov001_020769f4(menu);
            }
        }
    }
    entry->flags |= 2;
}
