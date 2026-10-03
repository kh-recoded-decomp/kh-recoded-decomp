#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    char _0[0x20];
    VecFx32 pos;
} CamActor;

extern u8 *data_ov042_020be5c0;
extern void camera_commit_explicit_projection_0202a8c4(CamActor *camera, int top, int bottom, int left, int right);

void CommitCameraProjection_020bd020(CamActor *camera, int top, int bottom, int left, int right) {
    *(VecFx32 *)(data_ov042_020be5c0 + 0x110) = camera->pos;
    camera_commit_explicit_projection_0202a8c4(camera, top, bottom, left, right);
}
