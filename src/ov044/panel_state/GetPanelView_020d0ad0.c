#include "nitro/types.h"

typedef struct {
    u32 words[14];
} PanelSnapshot;

typedef struct {
    PanelSnapshot base;
    u32 flags;
    int angle;
} PanelView;

typedef struct {
    PanelSnapshot base;
    u8 pad38[0x1c];
    int angle;
} Panel;

extern Panel *g_panel_020d0ea0;

void GetPanelView_020d0ad0(PanelView *view)
{
    Panel *panel = g_panel_020d0ea0;

    view->base = panel->base;
    view->flags = 0;
    view->angle = -panel->angle;
}
