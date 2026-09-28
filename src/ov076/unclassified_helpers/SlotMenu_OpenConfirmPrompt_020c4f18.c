#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
} SlotMenu;

extern void SlotMenu_ResetToBrowse_020c4ea8(SlotMenu *menu);
extern void func_ov076_020c439c(SlotMenu *menu);
extern void func_ov076_020c8388(SlotMenu *menu, int messageId);

void SlotMenu_OpenConfirmPrompt_020c4f18(SlotMenu *menu)
{
    SlotMenu_ResetToBrowse_020c4ea8(menu);
    func_ov076_020c439c(menu);
    func_ov076_020c8388(menu, 0x27);
    menu->state = 3;
}
