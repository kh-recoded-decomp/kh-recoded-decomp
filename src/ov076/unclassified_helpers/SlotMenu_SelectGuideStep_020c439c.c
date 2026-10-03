#include "nitro/types.h"

typedef struct SlotMenu {
    u8 pad_00000[0x4a06c];
    s32 hasEquippedSlots;
} SlotMenu;

extern BOOL IsGlobalPackedBitSet_02027304(int bit);
extern BOOL func_ov076_020c50e8(SlotMenu *menu);
extern BOOL func_ov076_020c503c(SlotMenu *menu);
extern void func_ov076_020c4260(SlotMenu *menu, int step, BOOL extra);

void SlotMenu_SelectGuideStep_020c439c(SlotMenu *menu)
{
    int step = -1;
    BOOL extra;

    if (IsGlobalPackedBitSet_02027304(0xf75) && menu->hasEquippedSlots != 0) {
        step = 0;
    } else if (!IsGlobalPackedBitSet_02027304(0xf79)) {
        if (func_ov076_020c50e8(menu)) {
            step = 1;
        }
    } else if (!IsGlobalPackedBitSet_02027304(0xf78)) {
        if (func_ov076_020c503c(menu)) {
            step = 2;
        }
    }
    if (step == 0 && !IsGlobalPackedBitSet_02027304(0xf78) && func_ov076_020c503c(menu)) {
        extra = TRUE;
    } else {
        extra = FALSE;
    }
    func_ov076_020c4260(menu, step, extra);
}
