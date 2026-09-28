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
extern void func_01ff9e3c(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern void func_0204dc94(VecFx32 *pos, VecFx32 *dir, VecFx32 *up);
extern void func_ov043_020bc820(CamActor *camera);

void UpdateCameraBasisAndCommit_020bc854(int updateBasis)
{
    CamActor *camera = g_activeCamera_020bd2c0;

    if ((camera->flags & 4) == 0) {
        if (updateBasis != 0) {
            VecFx32 direction;
            func_01ff9e3c(&camera->target, &camera->pos, &direction);
            func_0204dc94(&camera->pos, &direction, &camera->up);
        }
        func_ov043_020bc820(camera);
    }
}
