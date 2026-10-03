#include "nitro/types.h"

extern u32 GetPanelTransitionMode_020748e4(void);
extern void BeginWirelessChannelMeasurement_020748f4(void);
extern u16 FinishWirelessChannelSelection_02074b24(void);
extern void WH_SetReceiver_02074e3c(void (*receiver)(u16 aid, u16 *data, u16 size));
extern void func_ov015_02073284(u16 aid, u16 *data, u16 size);
extern u16 WM_GetNextTgid_02011658(void);
extern BOOL func_ov015_02074d98(int mode, u16 tgid, u16 channel);
extern void func_ov015_02072ee4(char nextState);

void UpdateWirelessParentState_020730ac(void)
{
    u16 channel;

    switch (GetPanelTransitionMode_020748e4()) {
    case 9:
    case 10:
        func_ov015_02072ee4(3);
        break;
    case 1:
        BeginWirelessChannelMeasurement_020748f4();
        break;
    case 7:
        channel = FinishWirelessChannelSelection_02074b24();
        WH_SetReceiver_02074e3c(func_ov015_02073284);
        if (func_ov015_02074d98(0, WM_GetNextTgid_02011658(), channel)) {
            func_ov015_02072ee4(6);
        } else {
            func_ov015_02072ee4(3);
        }
        break;
    }
}
