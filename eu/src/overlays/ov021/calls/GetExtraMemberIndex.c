#include "nitro/types.h"

s32 GetExtraMemberIndex(int self)
{
    s32 result = -1;
    if (*(s32 *)(self + 0xc) != 0) {
        result = *(s32 *)(self + 4) + -1;
    }
    return result;
}
