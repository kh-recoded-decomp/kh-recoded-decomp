#include "nitro/types.h"

typedef struct {
    u8 pad_00[6];
    u8 knownMacs[30][6];
} WirelessContext;

extern BOOL MacAddressesEqual_0206f4f8(u8 *macA, u8 *macB);
extern WirelessContext *data_ov015_0207e960;

BOOL IsKnownMacAddress_02072490(u8 *macAddress) {
    int i;

    i = 0;
    do {
        if (MacAddressesEqual_0206f4f8(macAddress, data_ov015_0207e960->knownMacs[i]) == TRUE) {
            return TRUE;
        }
        i++;
    } while (i < 30);
    return FALSE;
}
