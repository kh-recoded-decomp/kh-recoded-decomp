#include "nitro/types.h"

typedef struct {
    u8 pad_0 : 1;
    u8 doAction : 1;
    u8 doThird : 1;
    u8 pad_3to4 : 2;
    u8 doFirst : 1;
    u8 pad_6to7 : 2;
} PanelFlags98;

typedef struct {
    u8 doSecond : 1;
    u8 pad_1to7 : 7;
} PanelFlags99;

extern void AnimatePanelPageScreens(void);
extern void PulsePanelPaletteColor(void);
extern void ClearOv013SubBg0PanelArea(void);
extern void DrawOv013ListPositionCounter(int a, int b);
extern int gOv013PanelGlobals;

/* Dispatches three pending panel actions from flag bits. */
void DispatchOv013PendingPanelActions(void) {
    if (((PanelFlags98 *)(gOv013PanelGlobals + 0x98))->doFirst) {
        AnimatePanelPageScreens();
    }
    if (((PanelFlags99 *)(gOv013PanelGlobals + 0x99))->doSecond) {
        PulsePanelPaletteColor();
    }
    if (((PanelFlags98 *)(gOv013PanelGlobals + 0x98))->doThird) {
        ClearOv013SubBg0PanelArea();
    }
    if (!((PanelFlags98 *)(gOv013PanelGlobals + 0x98))->doAction) {
        return;
    }
    DrawOv013ListPositionCounter(*(s8 *)(gOv013PanelGlobals + 0x2f0) + 1, *(s8 *)(gOv013PanelGlobals + 0x2ec));
    {
        int flags = *(u8 *)(gOv013PanelGlobals + 0x98);
        flags = flags & ~2;
        *(u8 *)(gOv013PanelGlobals + 0x98) = (u8)flags;
    }
}
