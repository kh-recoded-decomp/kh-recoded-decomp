#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x4a06c];
    BOOL tutorialFlagPending;
} SlotMenu;

extern void SlotMenu_ResetToBrowse_020c4ea8(SlotMenu *menu);
extern BOOL IsGlobalPackedBitSet_02027304(int bitIndex);
extern BOOL func_ov076_020c503c(SlotMenu *menu);
extern void func_ov076_020c4260(SlotMenu *menu, int markMode, BOOL markFilledPairs);

void SlotMenu_BeginSlotSelection_020c4edc(SlotMenu *menu)
{
    BOOL markFilledPairs;

    SlotMenu_ResetToBrowse_020c4ea8(menu);
    if (!IsGlobalPackedBitSet_02027304(0xf78) && func_ov076_020c503c(menu)) {
        markFilledPairs = TRUE;
    } else {
        markFilledPairs = FALSE;
    }
    func_ov076_020c4260(menu, 0, markFilledPairs);
    menu->tutorialFlagPending = TRUE;
}
