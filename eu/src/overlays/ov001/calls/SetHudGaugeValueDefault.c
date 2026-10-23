#include "nitro/types.h"

extern void SetHudGaugeValue(int index, u32 value, int notifyIndex, BOOL animate, int mode, BOOL force);

void SetHudGaugeValueDefault(int index, u32 value, int notifyIndex)
{
    SetHudGaugeValue(index, value, notifyIndex, FALSE, 0, FALSE);
}
