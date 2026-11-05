#include "nitro/types.h"

extern u32 GetHudGaugeBlinkActive();

u32 StageScriptExpr_GetHudGauge0BlinkActive(int self)
{
    u32 value;

    *(u16 *)(self + 0x2c) = 1;
    value = GetHudGaugeBlinkActive(0);
    *(u32 *)(self + 0x30) = value;
    return 0;
}
