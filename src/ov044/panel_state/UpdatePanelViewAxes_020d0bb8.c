#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    fx32 sideOffset;
    fx32 aspect;
    fx32 tanHalf;
    u8 pad0c[0x100];
    int fieldOfView;
    u8 pad110[0x54];
    VecFx32 upAxis;
    VecFx32 sideAxis;
    VecFx32 rotatedUp;
    VecFx32 reflectedUp;
} Panel;

extern Panel *g_panel_020d0ea0;
extern MtxFx43 data_0205a970;

extern void MTX_Copy43To33_01ff913c(const MtxFx43 *src, MtxFx33 *dst);
extern void func_0204b0ac(VecFx32 *vec, const VecFx32 *axis, fx32 angle);
extern VecFx32 ReflectVectorAcrossNormal_0204adf8(const VecFx32 *vec, const VecFx32 *normal);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);

void UpdatePanelViewAxes_020d0bb8(void)
{
    Panel *panel = g_panel_020d0ea0;
    MtxFx33 view;
    VecFx32 reflectedUp;
    VecFx32 upAxis;
    MtxFx33 fetched;
    VecFx32 up;
    VecFx32 side;
    VecFx32 sum;
    fx32 scale;
    fx32 angle;

    MTX_Copy43To33_01ff913c(&data_0205a970, &fetched);
    view = fetched;
    angle = panel->fieldOfView / 2;
    up = *(VecFx32 *)view.m[1];
    func_0204b0ac(&up, (VecFx32 *)view.m[2], angle);
    panel->rotatedUp = up;
    reflectedUp = ReflectVectorAcrossNormal_0204adf8(&panel->rotatedUp, (VecFx32 *)view.m[2]);
    panel->reflectedUp = reflectedUp;
    scale = FX_Div_01ff9c84(0x1000, panel->tanHalf);
    scale = (fx32)(((s64)panel->aspect * scale + 0x800) >> 12);
    side = *(VecFx32 *)view.m[0];
    ScaleVecFx32InPlace_0204a5e4(&side, scale);
    panel->sideAxis = side;
    VEC_MultAdd_01ffa09c(panel->sideOffset, (VecFx32 *)view.m[2], &panel->sideAxis, &sum);
    panel->sideAxis = sum;
    VEC_Normalize_01ff9f88(&panel->sideAxis, &panel->sideAxis);
    upAxis = ReflectVectorAcrossNormal_0204adf8(&panel->sideAxis, (VecFx32 *)view.m[2]);
    panel->upAxis = upAxis;
}



