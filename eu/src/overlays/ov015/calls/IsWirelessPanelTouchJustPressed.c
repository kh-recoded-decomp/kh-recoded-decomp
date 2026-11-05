#include "nitro/types.h"

extern int HasWirelessPanelTouchSamples(void);
extern int IsCursorOffscreen(void);

BOOL IsWirelessPanelTouchJustPressed(void) {
    if ((HasWirelessPanelTouchSamples() != 0) && (IsCursorOffscreen() != 0)) {
        return 1;
    }
    return 0;
}
