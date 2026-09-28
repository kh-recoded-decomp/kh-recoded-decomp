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

extern FieldMenuHandle data_ov001_020a04b0;

extern BOOL func_ov001_020728a4(void);
extern BOOL func_ov001_020728e4(void);
extern void *GetWord20_020019f0(void *window);
extern void SelectListNodeOrFirst_020019b8(void *self, void *target);
extern u32 func_ov001_02073634(u32 messageId);
extern void func_ov027_020ba25c(MessageSet *messages, u32 fileId, int compressed);
extern void func_ov001_02076a9c(FieldMenu *menu, void *window, FieldEntry *entry, MessageSet *messages, s32 number);
extern void FreePointerIfSet_020ba294(void **pointer);
extern void func_ov001_020769f4(FieldMenu *menu);
extern FieldEntry *func_ov001_02075348(FieldMenu *menu, s32 index, s32 arg2, s32 arg3);

void func_ov001_02078710(s32 index, s32 kind)
{
    FieldMenu *menu = data_ov001_020a04b0.menu;
    FieldEntry *entry;
    void *savedNode;
    MessageSet messages;
    s32 i;

    if (index < 0 || index > 1) {
        return;
    }
    if (func_ov001_020728a4()) {
        entry = &menu->buttons[index] + 1;
        savedNode = GetWord20_020019f0(menu);
        SelectListNodeOrFirst_020019b8(menu, entry->listNode);
        func_ov027_020ba25c(&messages, func_ov001_02073634(0), 1);
        func_ov001_02076a9c(menu, menu, entry, &messages, index + 1);
        FreePointerIfSet_020ba294(&messages.file);
        SelectListNodeOrFirst_020019b8(menu, savedNode);
        if (menu->mode == 2 && menu->unk_C8 != menu->unk_DC) {
            menu->unk_C8 = menu->unk_DC;
            func_ov001_020769f4(menu);
        }
        return;
    }
    if (!func_ov001_020728e4()) {
        return;
    }
    for (i = 0; i < menu->activeCount; i++) {
        entry = func_ov001_02075348(menu, i, 1, 0);
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
