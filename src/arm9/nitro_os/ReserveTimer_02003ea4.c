#include "nitro/types.h"

extern u16 data_02056e90;

void ReserveTimer_02003ea4(int timerIndex)
{
    data_02056e90 |= (u16)(1 << timerIndex);
}
