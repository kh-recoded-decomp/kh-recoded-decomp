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
    fx32 timer;
    fx32 duration;
    int easing;
    VecFx32 forward;
    VecFx32 up;
    VecFx32 savedPos;
    VecFx32 savedForward;
    VecFx32 savedUp;
    VecFx32 pathOut;
    VecFx32 pathOut2;
    VecFx32 savedTarget;
    VecFx32 stateTarget;
    u8 paddc[0x18];
    VecFx32 target;
} Panel;

extern Panel *g_panel_020d0ea0;
extern PanelPath data_ov044_020d0df0[];

extern fx32 EaseProgress_0204a174(fx32 time, fx32 duration, int easing);
extern void LerpVecFx32Q27InPlace_0204be6c(VecFx32 *current, const VecFx32 *target, s32 t);
extern s16 AngleBetweenVecs_0204b070(const VecFx32 *a, const VecFx32 *b);
extern void RotateVecTowardVec_0204b0ac(VecFx32 *vec, const VecFx32 *axis, fx32 radians);
extern void EnterPanelState_020d0144(int state);

#define FX_MUL(a, b) ((fx32)(((s64)(a) * (b) + 0x800) >> 12))
#define IDX_TO_RAD(angle) ((fx32)((s64)(angle) * 0x6488 / 0x10000))

void StepPanelTransition_020d032c(void)
{
    VecFx32 defaultTarget;
    fx32 progress;
    s32 lerpT;

    g_panel_020d0ea0->timer += 0x1000;
    if (g_panel_020d0ea0->timer < g_panel_020d0ea0->duration) {
        progress = EaseProgress_0204a174(g_panel_020d0ea0->timer, g_panel_020d0ea0->duration, g_panel_020d0ea0->easing);
        lerpT = progress << 15;
        {
            const VecFx32 *goal = &data_ov044_020d0df0[g_panel_020d0ea0->state].start;
            VecFx32 pos = g_panel_020d0ea0->savedPos;
            LerpVecFx32Q27InPlace_0204be6c(&pos, goal, lerpT);
            g_panel_020d0ea0->path.start = pos;
        }
        {
            fx32 angle = IDX_TO_RAD(AngleBetweenVecs_0204b070(&g_panel_020d0ea0->savedForward, &g_panel_020d0ea0->pathOut));
            VecFx32 rotated = g_panel_020d0ea0->savedForward;
            RotateVecTowardVec_0204b0ac(&rotated, &g_panel_020d0ea0->pathOut, FX_MUL(angle, progress));
            g_panel_020d0ea0->forward = rotated;
        }
        {
            fx32 angle = IDX_TO_RAD(AngleBetweenVecs_0204b070(&g_panel_020d0ea0->savedUp, &g_panel_020d0ea0->pathOut2));
            VecFx32 rotated = g_panel_020d0ea0->savedUp;
            RotateVecTowardVec_0204b0ac(&rotated, &g_panel_020d0ea0->pathOut2, FX_MUL(angle, progress));
            g_panel_020d0ea0->up = rotated;
        }
        if (g_panel_020d0ea0->state == 6) {
            VecFx32 target = g_panel_020d0ea0->savedTarget;
            LerpVecFx32Q27InPlace_0204be6c(&target, &g_panel_020d0ea0->stateTarget, lerpT);
            g_panel_020d0ea0->target = target;
        } else if (g_panel_020d0ea0->prevState == 6) {
            VecFx32 fallback;
            VecFx32 target;
            fallback.x = 0;
            fallback.y = 0;
            fallback.z = -0x2333;
            defaultTarget = fallback;
            target = g_panel_020d0ea0->savedTarget;
            LerpVecFx32Q27InPlace_0204be6c(&target, &defaultTarget, lerpT);
            g_panel_020d0ea0->target = target;
        }
    } else {
        EnterPanelState_020d0144(g_panel_020d0ea0->state);
    }
}
