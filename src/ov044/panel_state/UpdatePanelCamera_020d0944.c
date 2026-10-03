#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    VecFx32 axes[3];
} Basis;

typedef struct {
    fx32 sine;
    fx32 cosine;
    u8 pad08[0xc];
    VecFx32 position;
    VecFx32 lookAt;
    VecFx32 up;
    u8 pad38[0x14];
    fx32 weights[3];
    u8 pad58[0x24];
    VecFx32 forwardUp;
    u8 pad88[0x54];
    VecFx32 lookAtOffset;
    VecFx32 positionOffset;
    VecFx32 target;
    VecFx32 origin;
    int fieldOfView;
    int particle[4];
    VecFx32 particleOrigin;
} Panel;

extern Panel *g_panel_020d0ea0;
extern const s16 data_0205356c[];

extern void func_ov044_020d08d8(Basis *out);
extern void CombineBasisAxes_020d06b8(const Basis *basis, const fx32 *weights, VecFx32 *out, VecFx32 *partial);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL UpdateDriftParticle_020afb94(void *particle);
extern void func_ov044_020d0090(BOOL shouldBlend);

#define PANEL_ANGLE_INDEX(fov) ((int)((((s64)((fov) / 2) << 16) / 0x6488) & 0xffff) >> 4)

void UpdatePanelCamera_020d0944(void)
{
    Panel *panel = g_panel_020d0ea0;
    Panel *camera;
    Basis basis;
    VecFx32 full;
    VecFx32 partial;
    VecFx32 positionSum;
    VecFx32 lookAtSum;

    func_ov044_020d08d8(&basis);
    CombineBasisAxes_020d06b8(&basis, panel->weights, &full, &partial);
    VEC_Add_01ff9e0c(&panel->target, &partial, &panel->positionOffset);
    VEC_Add_01ff9e0c(&panel->target, &full, &panel->lookAtOffset);
    panel->sine = data_0205356c[PANEL_ANGLE_INDEX(panel->fieldOfView)];
    panel->cosine = data_0205356c[(0x400 - PANEL_ANGLE_INDEX(panel->fieldOfView)) & 0xfff];
    if (panel->particle[0] != 0) {
        UpdateDriftParticle_020afb94(panel->particle);
        panel->origin = panel->particleOrigin;
    }
    camera = g_panel_020d0ea0;
    VEC_Add_01ff9e0c(&g_panel_020d0ea0->lookAtOffset, &g_panel_020d0ea0->origin, &lookAtSum);
    camera->lookAt = lookAtSum;
    VEC_Add_01ff9e0c(&g_panel_020d0ea0->positionOffset, &g_panel_020d0ea0->origin, &positionSum);
    camera->position = positionSum;
    camera->up = g_panel_020d0ea0->forwardUp;
    func_ov044_020d0090(TRUE);
}


