#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x104];
    s32 unk_104;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle gFieldCommandMenuGlobals;

s32 GetFieldMenuListMode(void)
{
    return gFieldCommandMenuGlobals.menu->unk_104;
}
