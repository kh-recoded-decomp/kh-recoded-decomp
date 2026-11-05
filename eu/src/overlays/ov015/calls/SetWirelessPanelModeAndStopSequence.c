#include "nitro/types.h"

extern void StopPanelSequence(void);
extern u8 *data_ov015_020812e0;

void SetWirelessPanelModeAndStopSequence(u32 value) {
    *(u32 *)(data_ov015_020812e0 + 8) = value;
    StopPanelSequence();
    *(u32 *)(data_ov015_020812e0 + 0x18) &= 0xfffeffff;
}
