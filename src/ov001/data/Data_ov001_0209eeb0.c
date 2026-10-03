#include "nitro/types.h"

extern void DrawFieldMenuSlotsAlt_0207639c(void);
extern void DrawFieldMenuSlots_0207621c(void);
extern void RefreshFieldMenuSlotsWrapped_020767ec(void);
extern void RefreshFieldMenuSlots_0207651c(void);
extern void UpdateGaugeFrameState_020761d8(void);
extern void func_ov001_020761a4(void);

void (*data_ov001_0209eeb0[6])(void) = {
    func_ov001_020761a4,
    UpdateGaugeFrameState_020761d8,
    DrawFieldMenuSlots_0207621c,
    DrawFieldMenuSlotsAlt_0207639c,
    RefreshFieldMenuSlots_0207651c,
    RefreshFieldMenuSlotsWrapped_020767ec,
};
