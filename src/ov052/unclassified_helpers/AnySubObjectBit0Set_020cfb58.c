#include "nitro/types.h"

extern BOOL IsBit0Set_020a9d1c(u32 *flags);

BOOL AnySubObjectBit0Set_020cfb58(int entity)
{
    BOOL found = FALSE;
    int i;
    for (i = 0; i < 2; i++) {
        if (IsBit0Set_020a9d1c((u32 *)(entity + 0xb68 + i * 0x230))) {
            found = TRUE;
            break;
        }
    }
    return found;
}
