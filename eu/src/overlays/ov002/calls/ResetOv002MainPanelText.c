#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags10;
    u8 pad_11[0x7c - 0x11];
} PanelState;

extern PanelState *gOv002ProfilePanelWork;
extern void CallVirtualHandlerSlot1(void *entry, int mode);

void ResetOv002MainPanelText(int selector) {
    switch (selector) {
    case -1:
        CallVirtualHandlerSlot1((u8 *)gOv002ProfilePanelWork + 0x48, 0);
        CallVirtualHandlerSlot1((u8 *)gOv002ProfilePanelWork + 0x7c, 0);
        gOv002ProfilePanelWork->flags10 |= 0x80;
        gOv002ProfilePanelWork->flags10 |= 0x40;
        return;
    case 0:
        CallVirtualHandlerSlot1((u8 *)gOv002ProfilePanelWork + 0x48, 0);
        gOv002ProfilePanelWork->flags10 |= 0x40;
        return;
    case 1:
        CallVirtualHandlerSlot1((u8 *)gOv002ProfilePanelWork + 0x7c, 0);
        gOv002ProfilePanelWork->flags10 |= 0x80;
        return;
    }
}
