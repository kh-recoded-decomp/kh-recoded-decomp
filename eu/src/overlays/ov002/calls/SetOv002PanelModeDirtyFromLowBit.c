#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags10;
} PanelState;

extern PanelState *gOv002ProfilePanelWork;

void SetOv002PanelModeDirtyFromLowBit(int value) {
    u8 byteValue = (u8)value;
    gOv002ProfilePanelWork->flags10 =
        (gOv002ProfilePanelWork->flags10 & ~0x02) | (((u32)byteValue << 31) >> 30);
}
