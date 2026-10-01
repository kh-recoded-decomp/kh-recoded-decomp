#include "nitro/types.h"

typedef struct WirelessHelperState {
    u16 unk_00;
    u16 autoConnect;
    u8 pad_04[0x4c];
    int sysState;
} WirelessHelperState;

extern WirelessHelperState data_0207e980;
extern void func_020737c4(int state);

BOOL EndWirelessScan_02074118(void)
{
    if (data_0207e980.sysState == 2) {
        data_0207e980.autoConnect = 0;
        func_020737c4(3);
        return TRUE;
    }
    return FALSE;
}
