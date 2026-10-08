#include "nitro/types.h"

typedef struct {
    void *file;
    u32 count;
    u8 *strings;
} MessageSet;

typedef struct {
    u8 pad_00[0x14];
    s32 unk_14;
    s32 unk_18;
    void *listNode;
    u8 pad_20[4];
    s32 unk_24;
    u16 flags;
    u8 pad_2A[0x12];
} FieldEntry;

typedef struct {
    u8 pad_000[0xB4];
    FieldEntry *buttons;
    u8 pad_0B8[0x10];
    s32 unk_C8;
    u8 pad_0CC[4];
    s32 activeCount;
    u8 pad_0D4[8];
    s32 unk_DC;
    u8 pad_0E0[0x24];
    s32 mode;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;

extern BOOL IsFieldFlag8Set(void);
extern BOOL IsFieldFlag13OrSessionFlagSet(void);
extern void *GetWord20(void *window);
extern void SelectListNodeOrFirst(void *self, void *target);
extern u32 MakePrimaryVramKey_02073634(u32 messageId);
extern void LoadPackedFileView(MessageSet *messages, u32 fileId, int compressed);
extern void DrawFieldSlotCell(FieldMenu *menu, void *window, FieldEntry *entry, MessageSet *messages, s32 number);
extern void FreePointerIfSet(void **pointer);
extern void DrawMenuPanelPage(FieldMenu *menu);
extern FieldEntry *CycleMenuEntry(FieldMenu *menu, s32 index, s32 arg2, s32 arg3);

void func_ov001_02078710(s32 index, s32 kind)
{
    FieldMenu *menu = data_ov001_020a04d0.menu;
    FieldEntry *entry;
    void *savedNode;
    MessageSet messages;
    s32 i;

    if (index < 0 || index > 1) {
        return;
    }
    if (IsFieldFlag8Set()) {
        entry = &menu->buttons[index] + 1;
        savedNode = GetWord20(menu);
        SelectListNodeOrFirst(menu, entry->listNode);
        LoadPackedFileView(&messages, MakePrimaryVramKey_02073634(0), 1);
        DrawFieldSlotCell(menu, menu, entry, &messages, index + 1);
        FreePointerIfSet(&messages.file);
        SelectListNodeOrFirst(menu, savedNode);
        if (menu->mode == 2 && menu->unk_C8 != menu->unk_DC) {
            menu->unk_C8 = menu->unk_DC;
            DrawMenuPanelPage(menu);
        }
        return;
    }
    if (!IsFieldFlag13OrSessionFlagSet()) {
        return;
    }
    for (i = 0; i < menu->activeCount; i++) {
        entry = CycleMenuEntry(menu, i, 1, 0);
        if (kind == 2) {
            if (entry->unk_18 != -1) {
                entry->unk_24 = 1;
                entry->flags |= 6;
            }
        } else if (kind == 3) {
            if (entry->unk_14 != -1) {
                entry->unk_24 = 1;
                entry->flags |= 6;
            }
        }
    }
}
