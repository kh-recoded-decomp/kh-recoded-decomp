#include "nitro/types.h"

extern u32 LookupPairValue_0206881c(void);
extern s32 func_ov001_02063a38(void);
extern void TryTriggerGroupEvent(u32 param);
extern void StageEvents_Disable(u16 param);
extern void StageEvent_ReleaseHoldBit1(u16 param);

void func_ov001_020688d4(u32 value, s32 hasValue, s32 flag)
{
    s32 mode;

    if (hasValue == 0) {
        value = LookupPairValue_0206881c();
    }
    mode = func_ov001_02063a38();
    if (mode == 6) {
        TryTriggerGroupEvent(value);
    }
    if (flag != 0) {
        StageEvents_Disable(value & 0xffff);
        return;
    }
    StageEvent_ReleaseHoldBit1(value & 0xffff);
}
