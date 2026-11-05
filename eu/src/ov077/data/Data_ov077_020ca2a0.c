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
extern void ItemScreen_SwitchToScene0(void);
extern void ItemScreen_OpenSlotMenu(void);
extern void ItemScreen_OpenMatrixMenu(void);

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
    (void *)ItemScreen_SwitchToScene0,
    NULL,
    (void *)UsePartySlotItem,
    (void *)ItemScreen_OpenSlotMenu,
    (void *)ItemScreen_OpenMatrixMenu,
    NULL,
    (void *)ItemScreen_SwitchToScene0,
};
