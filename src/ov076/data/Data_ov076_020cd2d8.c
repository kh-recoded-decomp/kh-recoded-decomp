#include "nitro/types.h"

#pragma explicit_zero_data on

extern void SlotMenu_HandleSlotSelect_020c8b60(void);
extern void SlotMenu_Init_020c45a8(void);
extern void SlotMenu_Shutdown_020c5ee0(void);
extern void SlotMenu_UnequipCursorSlot_020c8d70(void);
extern void SlotMenu_Update_020c4b48(void);
extern void func_ov076_020c8b50(void);
extern void func_ov076_020c8b58(void);
extern void func_ov076_020c8d20(void);
extern void func_ov076_020c8e6c(void);
extern void func_ov076_020c8eb0(void);

void *data_ov076_020cd2e4[17] = {
    (void *)SlotMenu_Init_020c45a8,
    (void *)SlotMenu_Shutdown_020c5ee0,
    (void *)SlotMenu_Update_020c4b48,
    NULL,
    (void *)0x0004A104,
    (void *)func_ov076_020c8b50,
    (void *)func_ov076_020c8b58,
    NULL,
    NULL,
    (void *)SlotMenu_HandleSlotSelect_020c8b60,
    (void *)func_ov076_020c8d20,
    NULL,
    (void *)SlotMenu_UnequipCursorSlot_020c8d70,
    (void *)func_ov076_020c8e6c,
    (void *)func_ov076_020c8eb0,
    NULL,
    (void *)func_ov076_020c8d20,
};

u32 data_ov076_020cd2d8[3] = {
    0x01FF522F, 0x00000000, 0x00000000,
};
