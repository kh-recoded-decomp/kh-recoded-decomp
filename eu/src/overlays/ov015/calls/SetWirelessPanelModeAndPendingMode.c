#include "nitro/types.h"

extern void SetWirelessPanelModeAndStopSequence(u32 value);
extern u8 *gWirelessBoardGlobals;

void SetWirelessPanelModeAndPendingMode(u32 flags, u32 mode) {
    SetWirelessPanelModeAndStopSequence(flags);
    *(u32 *)(gWirelessBoardGlobals + 0xc) = mode;
}
