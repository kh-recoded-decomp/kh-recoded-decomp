#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 words[6];
} PanelTransition;

typedef struct {
    u8 pad00[0x40];
    int prevState;
    int state;
    int savedState;
    PanelTransition transition;
} Panel;

extern Panel *g_panel_020d0ea0;

extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void func_ov044_020d02c0(const PanelTransition *transition, const VecFx32 *target, u32 data);

void StartScaledPanelTransition_020d0cfc(const VecFx32 *target, fx32 distance, u32 data)
{
    Panel *panel = g_panel_020d0ea0;
    PanelTransition transition = panel->transition;
    fx32 scale = FX_Div_01ff9c84(distance, 0x64000);
    fx32 scaled;

    scaled = (fx32)(((s64)transition.words[2] * scale + 0x800) >> 12);
    if (panel->prevState != 6) {
        panel->savedState = panel->prevState;
    }
    transition.words[2] = scaled;
    func_ov044_020d02c0(&transition, target, data);
}


