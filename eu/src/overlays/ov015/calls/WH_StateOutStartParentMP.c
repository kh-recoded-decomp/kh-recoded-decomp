#include "src/overlays/ov015/WirelessMPHelper.h"

#pragma opt_propagation off

extern BOOL func_ov015_02073c48(void);

void WH_StateOutStartParentMP(void *argument)
{
    WMStartMPCallback *callback = argument;
    s32 result;

    if (callback->error != 0) {
        WH_SetError(callback->error);
        WH_ChangeSysState(9);
        return;
    }

    switch (callback->state) {
    case 10:
        if (gWhState.mode == 2) {
            if (gWhState.systemState == 4) {
                if (!func_ov015_02073c48()) {
                    WH_ChangeSysState(9);
                }
                return;
            }
            if (gWhState.systemState == 6) {
                return;
            }
        } else if (gWhState.mode == 4) {
            u16 sharingAidBitmap = 15;
            u16 sharingPort = 13;

            result = WM_StartDataSharing(&data_ov015_0207fbc0, sharingPort,
                                        sharingAidBitmap, 0,
                                        sWirelessDataSharingDoubleMode);
            if (result != 0) {
                WH_SetError(result);
                WH_ChangeSysState(9);
                return;
            }
            WH_ChangeSysState(5);
            if (gWhState.connectCallback != NULL) {
                gWhState.connectCallback(callback);
            }
            return;
        }

        WH_ChangeSysState(4);
        if (gWhState.connectCallback != NULL) {
            gWhState.connectCallback(callback);
        }
        break;
    case 11:
        break;
    case 12:
        break;
    case 13:
        break;
    }
}
