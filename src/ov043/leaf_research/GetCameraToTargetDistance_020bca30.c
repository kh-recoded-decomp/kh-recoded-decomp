#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 perspectiveParams[4];
    fx32 farClip;
    VecFx32 target;
    VecFx32 pos;
    VecFx32 up;
    u32 flags;
} CamActor;

extern CamActor *g_activeCamera_020bd2c0;
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

fx32 GetCameraToTargetDistance_020bca30(void)
{
    CamActor *camera = g_activeCamera_020bd2c0;
    return func_01ffa0f4(&camera->pos, &camera->target);
}
