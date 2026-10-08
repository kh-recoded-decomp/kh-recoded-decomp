#include "nitro/types.h"

#pragma explicit_zero_data on

extern void BeginSlotItemSelection(void);
extern void UsePartySlotItem(void);
extern void func_ov077_020c42a4(void);
extern void func_ov077_020c479c(void);
extern void ShutdownItemMenu(void);
extern void func_ov077_020c5cc0(void);
extern void func_ov077_020c5cd4(void);
extern void func_ov077_020c5db8(void);
extern void func_ov077_020c5f14(void);
extern void func_ov077_020c5f48(void);

void *gEquipmentMatrixMenuDescriptor[17] = {
    (void *)func_ov077_020c42a4,
    (void *)ShutdownItemMenu,
    (void *)func_ov077_020c479c,
    NULL,
    (void *)0x00014D2C,
    (void *)func_ov077_020c5cc0,
    (void *)func_ov077_020c5cd4,
    NULL,
    NULL,
    (void *)BeginSlotItemSelection,
    (void *)func_ov077_020c5db8,
    NULL,
    (void *)UsePartySlotItem,
    (void *)func_ov077_020c5f14,
    (void *)func_ov077_020c5f48,
    NULL,
    (void *)func_ov077_020c5db8,
};

u32 data_ov077_020ca2a0[3] = {
    0x0102514A, 0x00580040, 0x00000000,
};
