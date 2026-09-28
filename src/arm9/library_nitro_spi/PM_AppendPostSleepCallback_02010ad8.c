#include "nitro/types.h"

typedef struct PMSleepCallbackInfo PMSleepCallbackInfo;

extern void func_02010a1c(PMSleepCallbackInfo **listp, PMSleepCallbackInfo *info, int priority, int flag);
extern PMSleepCallbackInfo *data_020597d8;

void PM_AppendPostSleepCallback_02010ad8(PMSleepCallbackInfo *info)
{
    func_02010a1c(&data_020597d8, info, 0xff, 0);
}
