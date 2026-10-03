#include "nitro/types.h"

extern u32 GetPanelTransitionMode_020748e4(void);
extern void func_ov015_02072ee4(char nextState);
extern BOOL WH_StartTransitionStep_02074fd0(void);
extern void func_ov015_02074ec8(void);

void DispatchPanelTransition_02072fb4(void)
{
    switch (GetPanelTransitionMode_020748e4()) {
    case 9:
    case 10:
        func_ov015_02074ec8();
        break;
    case 1:
        WH_StartTransitionStep_02074fd0();
        break;
    case 0:
        func_ov015_02072ee4(1);
        break;
    case 3:
        break;
    default:
        func_ov015_02074ec8();
        break;
    }
}
