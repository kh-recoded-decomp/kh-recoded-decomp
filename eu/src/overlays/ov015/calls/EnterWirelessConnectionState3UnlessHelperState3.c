#include "nitro/types.h"

extern void SetWirelessConnectionState(int state);
extern int GetPanelTransitionMode(void);

void EnterWirelessConnectionState3UnlessHelperState3(void) {
    int state;

    state = GetPanelTransitionMode();
    if (state == 3) {
        return;
    }
    SetWirelessConnectionState(3);
}
