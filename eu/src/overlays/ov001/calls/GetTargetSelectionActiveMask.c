#include "nitro/types.h"

extern u32 GetTargetSelectionFlag2(void);
extern u32 GetTargetSelectionFlag1(void);

u32 GetTargetSelectionActiveMask(void)
{
    u32 a;
    u32 b;

    a = GetTargetSelectionFlag2();
    b = GetTargetSelectionFlag1();
    return b | a;
}
