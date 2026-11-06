#include "nitro/types.h"

extern u8 *gWirelessBoardGlobals;

BOOL HasWirelessPanelTouchSamples(void) {
    return *(s16 *)(gWirelessBoardGlobals + 0x38) > 0;
}
