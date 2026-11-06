#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x68];
    u32 unk_68;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle gFieldCommandMenuGlobals;

u32 GetFieldMenuMode(void)
{
    return gFieldCommandMenuGlobals.menu->unk_68;
}
