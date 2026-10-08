#include "nitro/types.h"

typedef struct FieldEntry {
    u32 current;
    u32 limit;
    s32 id;
    s32 value;
    s32 state;
    u8 pad_14[0x14];
    u16 flags;
    u16 enabled;
    u8 pad_2c[0x10];
} FieldEntry;

typedef struct FieldMenu {
    u8 pad_000[0xac];
    FieldEntry *entries;
    u8 pad_0b0[0x20];
    s32 activeCount;
} FieldMenu;

typedef struct FieldMenuHandle {
    u32 state;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;
extern void DrawMenuPanelPage(FieldMenu *menu);

void SetFieldEntryEnabled(s32 id, s32 enabled)
{
    FieldMenu *menu = data_ov001_020a04d0.menu;
    FieldEntry *entry;
    s32 index;

    for (index = 0; index < menu->activeCount; index++) {
        entry = &menu->entries[index];
        if (entry->id == id) {
            if (entry->state != 3) {
                return;
            }
            entry->enabled = enabled;
            if (enabled == 0) {
                entry->flags &= ~1;
            } else {
                entry->flags |= 1;
            }
            DrawMenuPanelPage(menu);
            return;
        }
    }
}
