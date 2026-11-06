#include "nitro/types.h"

typedef struct PanelFlags {
    u8 unused0 : 4;
    u8 pending0 : 1;
    u8 pending1 : 1;
    u8 unused6 : 2;
} PanelFlags;

typedef struct PanelState {
    u8 pad_00[0x10];
    PanelFlags flags10;
    u8 pad_11[0xb0 - 0x11];
} PanelState;

extern PanelState *gOv002ProfilePanelWork;
extern void DestroyFndObjectList(void *entry);

void ReleaseOv002SubPanelTextLayers(void) {
    if (gOv002ProfilePanelWork->flags10.pending0) {
        DestroyFndObjectList((u8 *)gOv002ProfilePanelWork + 0xb0);
    }
    if (gOv002ProfilePanelWork->flags10.pending1) {
        DestroyFndObjectList((u8 *)gOv002ProfilePanelWork + 0xe4);
    }
    gOv002ProfilePanelWork->flags10.pending0 = 0;
    gOv002ProfilePanelWork->flags10.pending1 = 0;
}
