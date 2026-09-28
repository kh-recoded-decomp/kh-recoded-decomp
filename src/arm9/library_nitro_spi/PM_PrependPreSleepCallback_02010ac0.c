#include "nitro/types.h"

typedef struct PMSleepCallbackInfo PMSleepCallbackInfo;

extern void func_02010a1c(PMSleepCallbackInfo **listp, PMSleepCallbackInfo *info, int priority, int flag);
extern PMSleepCallbackInfo *data_020597d0;

void PM_PrependPreSleepCallback_02010ac0(PMSleepCallbackInfo *info)
{
    func_02010a1c(&data_020597d0, info, 0xffffff01, 1);
}
