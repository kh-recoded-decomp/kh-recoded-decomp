#include "nitro/fx_types.h"
#include "nitro/types.h"

typedef struct CameraProjection {
    fx32 fovySin;
    fx32 fovyCos;
    fx32 aspect;
    fx32 nearClip;
    fx32 farClip;
    VecFx32 position;
    VecFx32 target;
    VecFx32 up;
} CameraProjection;

typedef struct CameraAnim {
    u8 pad_00[0x10];
    CameraProjection projection;
    u8 pad_48[0x10];
    fx32 playbackStep;
} CameraAnim;

extern void LoadDefaultProjectionValues(CameraProjection *projection);

void CamAnim_ResetProjection(CameraAnim *anim)
{
    CameraProjection *projection = &anim->projection;

    LoadDefaultProjectionValues(projection);
    projection->fovySin = 0x5fe;
    projection->fovyCos = 0xed6;
    projection->position.x = 0;
    projection->position.y = 0;
    projection->position.z = 0;
    projection->target.x = 0;
    projection->target.y = 0;
    projection->target.z = 0x1000;
    projection->nearClip = 0x1000;
    projection->farClip = 0x3e8000;
    projection->up.y = 0;
    projection->up.x = 0;
    projection->up.z = -0x1000;
    anim->playbackStep = 0x1000;
}
