#include "nitro/types.h"

extern int IsDeviceReady_02011048(void);

u16 GetTransitionFrame_020115ac(void)
{
    if (IsDeviceReady_02011048() != 0) {
        return 0x8000;
    }
    return *(u16 *)0x2fffcfa;
}
