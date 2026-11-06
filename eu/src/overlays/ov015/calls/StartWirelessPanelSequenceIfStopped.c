#include "nitro/types.h"

extern void PlaySoundEffect(int a, int b);
extern s8 *gWirelessBoardGlobals;

void StartWirelessPanelSequenceIfStopped(void) {
    if (gWirelessBoardGlobals[0x5f] != 0) {
        return;
    }
    PlaySoundEffect(2, 0xc);
    gWirelessBoardGlobals[0x5f] = 1;
}
