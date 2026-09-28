#include "nitro/types.h"

extern void PMi_PrepareForcePowerOff_02010b24(void);
extern u32 func_02010418(u32 command, u32 arg1, u32 arg2, void (*callback)(void *), void *arg);

void PM_ForceToPowerOffAsync_02010534(void (*callback)(void *), void *arg)
{
    PMi_PrepareForcePowerOff_02010b24();
    func_02010418(0xe, 0, 0, callback, arg);
}
