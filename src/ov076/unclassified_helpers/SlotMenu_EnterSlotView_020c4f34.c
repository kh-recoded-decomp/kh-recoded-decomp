#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
} SlotMenu;

extern void SlotMenu_ResetToBrowse_020c4ea8(SlotMenu *menu);
extern void func_ov076_020c4260(SlotMenu *menu, int markMode, BOOL markFilledPairs);
extern void func_ov076_020c4444(SlotMenu *menu);
extern void func_ov076_020c53c8(SlotMenu *menu);

#define REG_BG1CNT (*(vu16 *)0x0400000a)
#define REG_DISPCNT (*(vu32 *)0x04000000)

void SlotMenu_EnterSlotView_020c4f34(SlotMenu *menu)
{
    SlotMenu_ResetToBrowse_020c4ea8(menu);
    func_ov076_020c4260(menu, -1, FALSE);
    REG_BG1CNT = (REG_BG1CNT & 0x43) | 0x10;
    func_ov076_020c4444(menu);
    func_ov076_020c53c8(menu);
    REG_DISPCNT = (REG_DISPCNT & 0xffffe0ff) | 0x1f00;
}
