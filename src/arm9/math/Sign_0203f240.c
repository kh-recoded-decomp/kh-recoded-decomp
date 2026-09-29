#include "nitro/types.h"

s32 Sign_0203f240(s32 value)
{
    if (value == 0) {
        return 0;
    }
    return value > 0 ? 1 : -1;
}
