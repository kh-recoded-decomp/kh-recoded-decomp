#include "nitro/types.h"

BOOL MacAddressesEqual_0206f4f8(u8 *macA, u8 *macB)
{
    int i = 0;
    do {
        if (macA[i] != macB[i]) {
            return FALSE;
        }
        i++;
    } while (i < 6);
    return TRUE;
}
