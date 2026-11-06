#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x11];
    u8 flags11;
    u8 pad_12[0xb0 - 0x12];
} PanelState;

extern PanelState *gOv002ProfilePanelWork;
extern void CallVirtualHandlerSlot1(void *entry, int mode);

void ResetOv002SubPanelText(int selector) {
    switch (selector) {
    case -1:
        CallVirtualHandlerSlot1((u8 *)gOv002ProfilePanelWork + 0xb0, 0);
        CallVirtualHandlerSlot1((u8 *)gOv002ProfilePanelWork + 0xe4, 0);
        gOv002ProfilePanelWork->flags11 = (gOv002ProfilePanelWork->flags11 & ~0x01) | 0x01;
        gOv002ProfilePanelWork->flags11 |= 0x02;
        return;
    case 0:
        CallVirtualHandlerSlot1((u8 *)gOv002ProfilePanelWork + 0xb0, 0);
        gOv002ProfilePanelWork->flags11 = (gOv002ProfilePanelWork->flags11 & ~0x01) | 0x01;
        return;
    case 1:
        CallVirtualHandlerSlot1((u8 *)gOv002ProfilePanelWork + 0xe4, 0);
        gOv002ProfilePanelWork->flags11 |= 0x02;
        return;
    }
}
