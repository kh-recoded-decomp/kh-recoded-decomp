#include "nitro/types.h"

extern void func_ov001_020747fc(int index, u32 value, int notifyIndex, BOOL animate, int mode, BOOL force);

void SetHudGaugeValueDefault_02074fa8(int index, u32 value, int notifyIndex)
{
    func_ov001_020747fc(index, value, notifyIndex, FALSE, 0, FALSE);
}
