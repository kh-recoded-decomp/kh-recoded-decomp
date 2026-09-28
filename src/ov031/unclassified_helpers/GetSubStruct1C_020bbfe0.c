#include "nitro/types.h"

extern u32 g_activeState_020bc800;

int GetSubStruct1C_020bbfe0(void)
{
    if (g_activeState_020bc800 != 0) {
        return g_activeState_020bc800 + 0x1c;
    }
    return 0;
}
