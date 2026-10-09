#include "nitro/types.h"

typedef struct WirelessHelperState {
    u8 pad_00[0x50];
    int sysState;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern u8 data_ov015_0207f3a0[];
extern void SetPanelTransitionMode(int state);
extern void WH_SetError(int errorCode);
extern int PXI_Init_02012298(void *keySetBuffer);
extern BOOL func_ov015_02074634(void);

BOOL EndWirelessKeySharing(void)
{
    int result;

    if (data_ov015_0207e980.sysState != 6) {
        return FALSE;
    }

    SetPanelTransitionMode(3);
    result = PXI_Init_02012298(data_ov015_0207f3a0);
    if (result != 0) {
        WH_SetError(result);
        return FALSE;
    }

    switch (func_ov015_02074634()) {
    case FALSE:
        return FALSE;
    default:
        return TRUE;
    }
}
