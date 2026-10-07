#include "nitro/types.h"

#pragma explicit_zero_data on

extern void SlotMenu_GetPanelState(void);
extern void SlotMenu_GetPanelStateAlt(void);
extern void SlotMenu_HandleSlotSelect(void);
extern void SlotMenu_UnequipCursorSlot(void);
extern void SlotMenu_Update(void);
extern void func_ov076_020c45c8(void);
extern void func_ov076_020c5f00(void);
extern void func_ov076_020c8d40(void);
extern void func_ov076_020c8e8c(void);
extern void func_ov076_020c8ed0(void);

void *gCommandMatrixMenuDescriptor[17] = {
    (void *)func_ov076_020c45c8,
    (void *)func_ov076_020c5f00,
    (void *)SlotMenu_Update,
    NULL,
    (void *)0x0004A104,
    (void *)SlotMenu_GetPanelState,
    (void *)SlotMenu_GetPanelStateAlt,
    NULL,
    NULL,
    (void *)SlotMenu_HandleSlotSelect,
    (void *)func_ov076_020c8d40,
    NULL,
    (void *)SlotMenu_UnequipCursorSlot,
    (void *)func_ov076_020c8e8c,
    (void *)func_ov076_020c8ed0,
    NULL,
    (void *)func_ov076_020c8d40,
};

u32 data_ov076_020cd2f8[3] = {
    0x01FF522F, 0x00000000, 0x00000000,
};
