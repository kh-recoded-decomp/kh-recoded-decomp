#include "nitro/types.h"

extern void SetWirelessPanelModeAndStopSequence(u32 value);
extern u8 *data_ov015_020812e0;

void SetWirelessPanelModeAndPendingMode(u32 flags, u32 mode) {
    SetWirelessPanelModeAndStopSequence(flags);
    *(u32 *)(data_ov015_020812e0 + 0xc) = mode;
}
