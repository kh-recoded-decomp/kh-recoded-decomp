#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 start;
    VecFx32 end;
} PanelPath;

typedef struct {
    u8 pad00[0x40];
    int prevState;
    int state;
    u8 pad48[4];
    PanelPath path;
    u8 pad64[0xc];
    VecFx32 forward;
    VecFx32 up;
    u8 pad88[0x48];
    VecFx32 stateTarget;
    u8 paddc[0x18];
    VecFx32 target;
} Panel;

extern Panel *g_panel_020d0ea0;
extern PanelPath data_ov044_020d0df0[];

extern void func_ov044_020d0728(const VecFx32 *path, VecFx32 *out, VecFx32 *out2);

void EnterPanelState_020d0144(int state)
{
    g_panel_020d0ea0->prevState = state;
    g_panel_020d0ea0->state = state;
    g_panel_020d0ea0->path = data_ov044_020d0df0[state];
    func_ov044_020d0728(&g_panel_020d0ea0->path.end, &g_panel_020d0ea0->forward, &g_panel_020d0ea0->up);
    if (g_panel_020d0ea0->state == 6) {
        g_panel_020d0ea0->target = g_panel_020d0ea0->stateTarget;
    } else if (g_panel_020d0ea0->prevState == 6) {
        VecFx32 defaultTarget;

        defaultTarget.x = 0;
        defaultTarget.y = 0;
        defaultTarget.z = -0x2333;

        g_panel_020d0ea0->target = defaultTarget;
    }
}

