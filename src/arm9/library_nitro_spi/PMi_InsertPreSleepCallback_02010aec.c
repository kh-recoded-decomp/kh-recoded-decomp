#include "nitro/types.h"

typedef struct PMSleepCallbackInfo PMSleepCallbackInfo;

extern void func_02010a1c(PMSleepCallbackInfo **listp, PMSleepCallbackInfo *info, int priority, int flag);
extern PMSleepCallbackInfo *data_020597d0;

void PMi_InsertPreSleepCallback_02010aec(PMSleepCallbackInfo *info, int priority)
{
    func_02010a1c(&data_020597d0, info, priority, 0);
}
