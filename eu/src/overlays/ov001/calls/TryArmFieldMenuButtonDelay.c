#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xC8];
    s32 unk_C8;
    u8 pad_0CC[0x78];
    s32 unk_144;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle gFieldCommandMenuGlobals;

extern BOOL InvokeFieldMinigameActiveCallback(void);
extern BOOL IsModeSetOrFlag370aClear(void);
extern BOOL IsLeadEntryFlag80Set(void);

BOOL TryArmFieldMenuButtonDelay(void)
{
    FieldMenu *menu;

    if (InvokeFieldMinigameActiveCallback()) {
        return FALSE;
    }
    if (!IsModeSetOrFlag370aClear()) {
        return FALSE;
    }
    if (IsLeadEntryFlag80Set()) {
        return FALSE;
    }
    menu = gFieldCommandMenuGlobals.menu;
    if (menu->unk_C8 >= 2 && menu->unk_144 < 0) {
        menu->unk_144 = 0;
    }
    return TRUE;
}
