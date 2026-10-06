#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xC];
    s32 id;
    u8 pad_10[0x2C];
} FieldSlot;

typedef struct {
    u8 pad_000[0xB0];
    FieldSlot *slots;
    u8 pad_0B4[0x58];
    u16 unk_10C;
    u16 unk_10E;
    FieldSlot *activeSlot;
    s32 unk_114;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;

extern void ClearHudPopup(void);

void func_ov001_020788b8(s32 id, u16 value)
{
    FieldSlot *slot;
    FieldMenu *menu = data_ov001_020a04d0.menu;
    s32 index;

    if (value == 0) {
        menu->unk_10E = 0;
        menu->activeSlot = NULL;
        menu->unk_114 = 1;
        return;
    }
    for (index = 0; index < 14; index++) {
        slot = &menu->slots[index];
        if (slot->id == id) {
            ClearHudPopup();
            menu->activeSlot = slot;
            menu->unk_10E = value;
            menu->unk_10C = 0;
            return;
        }
    }
}
