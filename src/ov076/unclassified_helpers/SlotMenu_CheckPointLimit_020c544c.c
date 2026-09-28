#include "nitro/types.h"

typedef struct SlotMenu SlotMenu;

extern BOOL SlotMenu_IsPointTotalWithinLimit_020c8b28(SlotMenu *menu);
extern void SlotMenu_ShowPointLimitWarning_020c89a0(SlotMenu *menu);

BOOL SlotMenu_CheckPointLimit_020c544c(SlotMenu *menu, BOOL showWarning)
{
    if (!SlotMenu_IsPointTotalWithinLimit_020c8b28(menu)) {
        if (showWarning) {
            SlotMenu_ShowPointLimitWarning_020c89a0(menu);
        }
        return FALSE;
    }
    return TRUE;
}
