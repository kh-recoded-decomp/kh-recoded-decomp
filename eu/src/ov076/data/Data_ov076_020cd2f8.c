#include "nitro/types.h"

#pragma explicit_zero_data on

extern void SlotMenu_GetPanelState(void);
extern void SlotMenu_GetPanelStateAlt(void);
extern void SlotMenu_HandleSlotSelect(void);
extern void SlotMenu_UnequipCursorSlot(void);
extern void SlotMenu_Update(void);
extern void SlotMenu_Init(void);
extern void SlotMenu_Shutdown(void);
extern void SlotMenu_SwitchToScene0(void);
extern void SlotMenu_OpenMatrixMenu(void);
extern void SlotMenu_OpenItemScreen(void);

void *gCommandMatrixMenuDescriptor[17] = {
    (void *)SlotMenu_Init,
    (void *)SlotMenu_Shutdown,
    (void *)SlotMenu_Update,
    NULL,
    (void *)0x0004A104,
    (void *)SlotMenu_GetPanelState,
    (void *)SlotMenu_GetPanelStateAlt,
    NULL,
    NULL,
    (void *)SlotMenu_HandleSlotSelect,
    (void *)SlotMenu_SwitchToScene0,
    NULL,
    (void *)SlotMenu_UnequipCursorSlot,
    (void *)SlotMenu_OpenMatrixMenu,
    (void *)SlotMenu_OpenItemScreen,
    NULL,
    (void *)SlotMenu_SwitchToScene0,
};

u32 data_ov076_020cd2f8[3] = {
    0x01FF522F, 0x00000000, 0x00000000,
};
