#include "nitro/types.h"

extern u32 GetPanelTransitionMode_020748e4(void);
extern void func_ov015_02072ee4(char nextState);
extern void WH_SetReceiver_02074e3c(void (*receiver)(u16 aid, u16 *data, u16 size));
extern void func_ov015_02073348(u16 aid, u16 *data, u16 size);
extern int func_ov015_02073d68(int mode, int arg1, int arg2);

void HandleConnectTransition_02073150(void)
{
    switch (GetPanelTransitionMode_020748e4()) {
    case 9:
    case 10:
        func_ov015_02072ee4(3);
        break;
    case 1:
        WH_SetReceiver_02074e3c(func_ov015_02073348);
        if (func_ov015_02073d68(1, 0, 0) != 0) {
            func_ov015_02072ee4(7);
        } else {
            func_ov015_02072ee4(3);
        }
        break;
    }
}
