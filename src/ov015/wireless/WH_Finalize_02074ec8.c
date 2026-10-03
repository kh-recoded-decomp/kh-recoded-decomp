#include "nitro/types.h"

typedef struct WirelessHelperState {
    u8 pad_00[0x40];
    int connectMode;
    u8 pad_44[0xc];
    int sysState;
} WirelessHelperState;

extern WirelessHelperState data_ov015_0207e980;
extern u8 data_ov015_0207fbc0[];
extern void SetPanelTransitionMode_020737c4(int state);
extern void PollPanelTransition_02074e80(void);
extern BOOL EndWirelessScan_02074118(void);
extern BOOL EndWirelessKeySharing_020745dc(void);
extern int ClearSlotEventHandler_02011ea4(void *dataSharingInfo);
extern BOOL func_ov015_02074634(void);
extern BOOL WH_EndChildStep_02073c7c(void);
extern BOOL func_ov015_02073cbc(void);

void WH_Finalize_02074ec8(void)
{
    if (data_ov015_0207e980.sysState == 1) {
        return;
    }

    if (data_ov015_0207e980.sysState == 2) {
        if (!EndWirelessScan_02074118()) {
            PollPanelTransition_02074e80();
        }
        return;
    }

    if (data_ov015_0207e980.sysState != 6 && data_ov015_0207e980.sysState != 5 && data_ov015_0207e980.sysState != 4) {
        SetPanelTransitionMode_020737c4(3);
        PollPanelTransition_02074e80();
        return;
    }

    SetPanelTransitionMode_020737c4(3);

    switch (data_ov015_0207e980.connectMode) {
    case 3:
        if (!EndWirelessKeySharing_020745dc()) {
            PollPanelTransition_02074e80();
        }
        break;
    case 5:
        if (ClearSlotEventHandler_02011ea4(data_ov015_0207fbc0) != 0) {
            PollPanelTransition_02074e80();
            break;
        }
    case 1:
        if (!func_ov015_02074634()) {
            PollPanelTransition_02074e80();
        }
        break;
    case 2:
        if (!WH_EndChildStep_02073c7c()) {
            PollPanelTransition_02074e80();
        }
        break;
    case 4:
        if (ClearSlotEventHandler_02011ea4(data_ov015_0207fbc0) != 0) {
            PollPanelTransition_02074e80();
            break;
        }
    case 0:
        if (!func_ov015_02073cbc()) {
            PollPanelTransition_02074e80();
        }
        break;
    }
}
