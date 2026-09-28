#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xf4];
    u16 itemColors[6];
    u8 pad_100[0x104 - 0x100];
    u8 highlightMask;
} PanelScene;

extern PanelScene *g_panelScene_020a04c8;

void SetPanelItemHighlight_0207b19c(int index, BOOL highlighted)
{
    PanelScene *panel = g_panelScene_020a04c8;

    if (highlighted) {
        panel->itemColors[index] = 0x1f;
        panel->highlightMask |= (u8)(1 << index);
    } else {
        panel->itemColors[index] = 0x35ad;
        panel->highlightMask &= (u8)~(1 << index);
    }
}
