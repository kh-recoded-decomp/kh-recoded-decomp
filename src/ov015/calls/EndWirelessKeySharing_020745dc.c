#include "nitro/types.h"

typedef struct WirelessHelperState {
    u8 pad_00[0x50];
    int sysState;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern u8 data_ov015_0207f3a0[];
extern void WH_ChangeSysState_020737c4(int state);
extern void WH_SetError_020737d4(int errorCode);
extern int PXI_Init_02012284(void *keySetBuffer);
extern BOOL WH_StateInEndChildMP_02074634(void);

BOOL EndWirelessKeySharing_020745dc(void)
{
    int result;

    if (data_ov015_0207e980.sysState != 6) {
        return FALSE;
    }

    WH_ChangeSysState_020737c4(3);
    result = PXI_Init_02012284(data_ov015_0207f3a0);
    if (result != 0) {
        WH_SetError_020737d4(result);
        return FALSE;
    }

    switch (WH_StateInEndChildMP_02074634()) {
    case FALSE:
        return FALSE;
    default:
        return TRUE;
    }
}
