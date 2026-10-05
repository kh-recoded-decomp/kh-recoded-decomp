#include "nitro/types.h"

typedef struct FieldMenu {
    u8 pad_000[0x110];
    int primaryHandle;
    int secondaryHandle;
} FieldMenu;

typedef struct MenuGlobals {
    u32 unk_00;
    FieldMenu *menu;
} MenuGlobals;

extern MenuGlobals data_ov001_020a04b0;

BOOL IsMenuSlotBusy_02078910(void)
{
    BOOL idle = FALSE;
    FieldMenu *menu = data_ov001_020a04b0.menu;
    BOOL busy;

    if (menu->primaryHandle == 0 && menu->secondaryHandle == 0) {
        idle = TRUE;
    }
    busy = TRUE;
    if (idle) {
        busy = FALSE;
    }
    return busy;
}


