#include "nitro/types.h"

extern int FindWidgetById(int panel, int value);
extern void SetFocusedWidget(int panel, int value);
extern void ResolveWidgetPositionComponents(int panel, int value, void *buffer, int flag);
extern void SetWidgetPosition(int panel, int value, void *buffer, int flag);
extern int gOv013PanelGlobals;

/* Positions cursor widget 0 at x=8 (fx32) and the selected list row. */
void PositionOv013CursorWidget(void) {
    u32 buffer[2];
    int result = FindWidgetById(gOv013PanelGlobals + 0x6818, *(s8 *)(gOv013PanelGlobals + 0x2ee) + 0x14);
    SetFocusedWidget(gOv013PanelGlobals + 0x6818, result);
    ResolveWidgetPositionComponents(gOv013PanelGlobals + 0x6818, result, buffer, 0);
    buffer[1] = *(int *)(gOv013PanelGlobals + 0xa8) + *(int *)(gOv013PanelGlobals + 0x2fc) * 0x1000;
    buffer[0] = 0x8000;
    result = FindWidgetById(gOv013PanelGlobals + 0x6818, 0);
    SetWidgetPosition(gOv013PanelGlobals + 0x6818, result, buffer, 0);
}
