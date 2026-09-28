#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
} SlotMenu;

extern void SlotMenu_OpenMessage_020c6308(SlotMenu *menu, int windowType, int arg2, int arg3, int messageId);
extern void *func_ov039_020bc1bc(void);
extern void SetNavigationElementsVisible_020ccd30(void *container, BOOL visible);

void SlotMenu_ShowPointLimitWarning_020c89a0(SlotMenu *menu)
{
    SlotMenu_OpenMessage_020c6308(menu, 1, 0, 9, 0x5d);
    menu->state = 9;
    SetNavigationElementsVisible_020ccd30(func_ov039_020bc1bc(), FALSE);
}
