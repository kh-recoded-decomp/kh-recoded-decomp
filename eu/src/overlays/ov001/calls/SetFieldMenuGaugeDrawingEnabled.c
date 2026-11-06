#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x118];
    s32 unk_118;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle gFieldCommandMenuGlobals;

void SetFieldMenuGaugeDrawingEnabled(s32 value)
{
    gFieldCommandMenuGlobals.menu->unk_118 = value;
}
