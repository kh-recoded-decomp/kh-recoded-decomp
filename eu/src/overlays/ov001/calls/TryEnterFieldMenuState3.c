#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xFC];
    s32 state;
    u8 pad_100[0x38];
    s32 unk_138;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle gFieldCommandMenuGlobals;

extern BOOL IsModeSetOrFlag370aClear(void);
extern BOOL IsLeadEntryFlag80Set(void);
extern BOOL FieldMenu_TryEnterState3(FieldMenu *menu);

BOOL TryEnterFieldMenuState3(void)
{
    FieldMenu *menu = gFieldCommandMenuGlobals.menu;

    if (menu->unk_138 == 0) {
        return FALSE;
    }
    if (menu->state != 0) {
        return FALSE;
    }
    if (!IsModeSetOrFlag370aClear()) {
        return FALSE;
    }
    if (IsLeadEntryFlag80Set()) {
        return FALSE;
    }
    return FieldMenu_TryEnterState3(menu);
}
