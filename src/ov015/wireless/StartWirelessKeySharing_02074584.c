#include "nitro/types.h"

typedef struct WirelessHelperState {
    u8 pad_00[0x50];
    int sysState;
} WirelessHelperState;

extern WirelessHelperState data_0207e980;
extern u8 data_0207f3a0[];
extern void func_020737c4(int state);
extern void func_020737d4(int errorCode);
extern int func_02012270(void *keySetBuffer, u16 port);

BOOL StartWirelessKeySharing_02074584(void)
{
    int result;

    if (data_0207e980.sysState == 6) {
        return TRUE;
    }
    if (data_0207e980.sysState != 4) {
        return FALSE;
    }
    func_020737c4(6);
    result = func_02012270(data_0207f3a0, 13);
    if (result != 0) {
        func_020737d4(result);
        return FALSE;
    }
    return TRUE;
}
