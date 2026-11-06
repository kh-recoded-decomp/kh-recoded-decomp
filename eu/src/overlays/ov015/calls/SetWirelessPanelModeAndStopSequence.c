#include "nitro/types.h"

extern void StopPanelSequence(void);
extern u8 *gWirelessBoardGlobals;

void SetWirelessPanelModeAndStopSequence(u32 value) {
    *(u32 *)(gWirelessBoardGlobals + 8) = value;
    StopPanelSequence();
    *(u32 *)(gWirelessBoardGlobals + 0x18) &= 0xfffeffff;
}
