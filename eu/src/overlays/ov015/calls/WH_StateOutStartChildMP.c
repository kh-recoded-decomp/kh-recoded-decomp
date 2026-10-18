#include "src/overlays/ov015/WirelessMPHelper.h"

#pragma opt_propagation off

extern void WH_Finalize(void);
extern BOOL StartWirelessKeySharing(void);

void WH_StateOutStartChildMP(void *argument)
{
    WMStartMPCallback *callback = argument;
    s32 result;

    if (callback->error != 0) {
        if (callback->error == 15 || callback->error == 9 || callback->error == 13) {
            return;
        }
        WH_SetError(callback->error);
        WH_ChangeSysState(9);
        return;
    }

    switch (callback->state) {
    case 10:
        if (data_ov015_0207e980.mode == 3) {
            if (data_ov015_0207e980.systemState == 6) {
                return;
            }
            if (data_ov015_0207e980.systemState == 4) {
                if (!StartWirelessKeySharing()) {
                    WH_Finalize();
                }
                return;
            }
        } else if (data_ov015_0207e980.mode == 5) {
            u16 sharingAidBitmap = 15;
            u16 sharingPort = 13;

            result = WM_StartDataSharing(&data_ov015_0207fbc0, sharingPort,
                                        sharingAidBitmap, 0,
                                        sWirelessDataSharingDoubleMode);
            if (result != 0) {
                WH_SetError(result);
                WH_Finalize();
                return;
            }
            WH_ChangeSysState(5);
            if (data_ov015_0207e980.connectCallback != NULL) {
                data_ov015_0207e980.connectCallback(callback);
            }
            return;
        }

        WH_ChangeSysState(4);
        if (data_ov015_0207e980.connectCallback != NULL) {
            data_ov015_0207e980.connectCallback(callback);
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
