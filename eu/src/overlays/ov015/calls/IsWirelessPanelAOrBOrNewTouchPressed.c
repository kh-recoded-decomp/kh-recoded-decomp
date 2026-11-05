#include "nitro/types.h"

extern int IsGlobalBit0Set(void);
extern int IsButtonBPressed(void);
extern int IsWirelessPanelTouchJustPressed(void);

BOOL IsWirelessPanelAOrBOrNewTouchPressed(void) {
    BOOL result;

    result = 0;
    if ((IsGlobalBit0Set() != 0) || (IsButtonBPressed() != 0) ||
        (IsWirelessPanelTouchJustPressed() != 0)) {
        result = 1;
    }
    return result;
}
