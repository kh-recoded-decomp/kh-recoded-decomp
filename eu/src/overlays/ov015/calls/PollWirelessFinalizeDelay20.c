#include "src/overlays/ov015/Ov015WirelessState.h"

extern int HasIdleActiveEntry(void);
extern void SetWirelessConnectionState(int state);
extern void WH_Finalize(void);

void PollWirelessFinalizeDelay20(void)
{
    int result;

    gOv015WirelessState->finalizeDelay--;
    if (gOv015WirelessState->finalizeDelay > 0) {
        return;
    }
    result = HasIdleActiveEntry();
    if (result != 0) {
        return;
    }
    WH_Finalize();
    SetWirelessConnectionState(3);
}
