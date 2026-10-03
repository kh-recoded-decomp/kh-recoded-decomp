#include "nitro/types.h"

typedef struct WirelessHelper {
    u8 pad_00[8];
    u16 measuredChannel;
} WirelessHelper;

extern WirelessHelper data_ov015_0207e980;
extern void SetPanelTransitionMode_020737c4(u32 mode);
extern int RunTransitionSlot2_0201170c(void (*callback)(void *));
extern void ChoosePanelModeFromSelection_020748ac(void *context);

BOOL WH_StartTransitionStep_02074fd0(void)
{
    SetPanelTransitionMode_020737c4(3);
    if (RunTransitionSlot2_0201170c(ChoosePanelModeFromSelection_020748ac) == 2) {
        data_ov015_0207e980.measuredChannel = 0;
        return TRUE;
    }
    SetPanelTransitionMode_020737c4(9);
    return FALSE;
}
