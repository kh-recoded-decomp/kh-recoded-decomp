#include "nitro/types.h"

extern BOOL func_ov021_020a9d04(u32 *flags);

BOOL AnySubObjectFlagsActive_020cfb28(int entity)
{
    BOOL found = FALSE;
    int i;
    for (i = 0; i < 2; i++) {
        if (func_ov021_020a9d04((u32 *)(entity + 0xb68 + i * 0x230))) {
            found = TRUE;
            break;
        }
    }
    return found;
}
