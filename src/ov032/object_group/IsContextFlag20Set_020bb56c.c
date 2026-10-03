#include "nitro/types.h"

extern int contextData_020c0060[];

u32 IsContextFlag20Set_020bb56c(void)
{
    return *(u16 *)(contextData_020c0060[1] + 6) & 0x20;
}
