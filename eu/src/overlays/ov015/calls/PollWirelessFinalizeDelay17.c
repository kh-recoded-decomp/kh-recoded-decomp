#include "src/overlays/ov015/Ov015WirelessState.h"

extern int HasIdleActiveEntry(void);
extern void func_ov015_02072ee4(int state);
extern void WH_Finalize(void);

void PollWirelessFinalizeDelay17(void)
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
    func_ov015_02072ee4(3);
}
