#include "nitro/types.h"

typedef struct {
    u32 current;
    u32 limit;
    u8 pad_08[0x20];
    u16 flags;
    u8 pad_2A[0x12];
} FieldEntry;

typedef struct {
    u8 pad_000[0xAC];
    FieldEntry *entries;
    u8 pad_0B0[0x20];
    s32 activeCount;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern BOOL func_ov001_020728a4(void);

void func_ov001_02078680(void)
{
    FieldMenu *menu = data_ov001_020a04b0.menu;
    FieldEntry *entry;
    s32 index;

    if (!func_ov001_020728a4()) {
        return;
    }
    for (index = 0; index < menu->activeCount; index++) {
        entry = &menu->entries[index];
        if (entry->flags & 0x10) {
            if (++entry->current > entry->limit) {
                entry->current = entry->limit;
            }
        }
    }
}
