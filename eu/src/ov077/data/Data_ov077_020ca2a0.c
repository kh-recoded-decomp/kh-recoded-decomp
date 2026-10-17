#include "nitro/types.h"

#pragma explicit_zero_data on

extern void BeginSlotItemSelection(void);
extern void UsePartySlotItem(void);
typedef struct ItemScreen ItemScreen;
extern BOOL InitItemScreen(ItemScreen *screen);
extern void UpdateItemScreen(void);
extern void ShutdownItemMenu(void);
extern void HandleEquipmentCursorUp(void);
extern void HandleEquipmentCursorDown(void);
extern void func_ov077_020c5db8(void);
extern void func_ov077_020c5f14(void);
extern void func_ov077_020c5f48(void);

void *gEquipmentMatrixMenuDescriptor[17] = {
    (void *)InitItemScreen,
    (void *)ShutdownItemMenu,
    (void *)UpdateItemScreen,
    NULL,
    (void *)0x00014D2C,
    (void *)HandleEquipmentCursorUp,
    (void *)HandleEquipmentCursorDown,
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
