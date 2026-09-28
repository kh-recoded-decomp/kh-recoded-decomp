#include "nitro/types.h"

extern u32 PM_ForceToPowerOffSync_02010550(void);
extern void func_020049b4(int param1);
extern u32 func_02004938(void);
extern void ResetFourChannels_020052dc(void);
extern void func_02004d30(void);

void ForcePowerOffAndHalt_0201057c(void)
{
    while (PM_ForceToPowerOffSync_02010550() != 0) {
        func_020049b4(0x51d23);
    }

    func_02004938();
    ResetFourChannels_020052dc();

    while (TRUE) {
        func_02004d30();
    }
}
