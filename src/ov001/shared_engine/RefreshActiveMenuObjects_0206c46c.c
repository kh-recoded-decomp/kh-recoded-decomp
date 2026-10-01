#include "nitro/types.h"

typedef struct MenuItemInfo {
    u16 unk_00;
    u16 unk_02_0 : 1;
    u16 isWide : 1;
    u16 unk_02_2 : 14;
    u8 pad_04[0x20];
} MenuItemInfo;

typedef struct MenuContext {
    u32 flags;
    u32 kind;
    u16 itemId;
    u8 pad_0a[0x46];
    u8 pairedObjects[0x7c];
    u8 wideObjects[0x148];
    u8 position[8];
} MenuContext;

extern MenuContext *data_ov001_020a0484;
extern BOOL func_ov001_02087960(u16 itemId, MenuItemInfo *info);
extern void SetupMirroredObjectPair_0206c218(void *objects, void *pos);
extern void func_ov001_0206c048(void *objects, void *pos);

void RefreshActiveMenuObjects_0206c46c(void)
{
    MenuContext *menu = data_ov001_020a0484;
    MenuItemInfo info;

    if (menu == NULL || !(menu->flags & 0x10)) {
        return;
    }
    menu->flags &= ~0x10;
    switch (menu->kind) {
    case 0:
        break;
    case 1:
        if (func_ov001_02087960(menu->itemId, &info)) {
            if (!info.isWide) {
                SetupMirroredObjectPair_0206c218(menu->pairedObjects, menu->position);
                return;
            }
            func_ov001_0206c048(menu->wideObjects, menu->position);
            return;
        }
        break;
    case 2:
    case 3:
        func_ov001_0206c048(menu->wideObjects, menu->position);
        return;
    case 4:
        SetupMirroredObjectPair_0206c218(menu->pairedObjects, menu->position);
        return;
    }
}
