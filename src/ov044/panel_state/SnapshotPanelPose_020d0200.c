#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 start;
    VecFx32 end;
} PanelPath;

typedef struct {
    u8 pad00[0x44];
    int state;
    u8 pad48[4];
    VecFx32 transitionPos;
    u8 pad58[0x18];
    VecFx32 forward;
    VecFx32 up;
    VecFx32 savedPos;
    VecFx32 savedForward;
    VecFx32 savedUp;
    VecFx32 pathOut;
    VecFx32 pathOut2;
    VecFx32 savedTarget;
    u8 padd0[0x24];
    VecFx32 target;
} Panel;

extern Panel *g_panel_020d0ea0;
extern PanelPath data_ov044_020d0df0[];

extern void func_ov044_020d0728(const VecFx32 *path, VecFx32 *out, VecFx32 *out2);

void SnapshotPanelPose_020d0200(void)
{
    Panel *panel = g_panel_020d0ea0;

    panel->savedPos = panel->transitionPos;
    panel->savedTarget = panel->target;
    panel->savedForward = panel->forward;
    panel->savedUp = panel->up;
    func_ov044_020d0728(&data_ov044_020d0df0[panel->state].end, &panel->pathOut, &panel->pathOut2);
}
