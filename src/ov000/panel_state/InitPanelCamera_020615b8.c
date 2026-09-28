#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xc];
    fx32 nearClip;
    fx32 farClip;
    VecFx32 target;
    VecFx32 pos;
    VecFx32 up;
} CamActor;

typedef struct {
    u8 pad_00[0x5c];
    CamActor camera;
} Panel;

extern void LoadDefaultProjectionValues_0202a7b4(CamActor *camera);
extern void camera_commit_explicit_projection_0202a8c4(CamActor *camera, fx32 top, fx32 bottom, fx32 left, fx32 right);

void InitPanelCamera_020615b8(Panel *panel)
{
    LoadDefaultProjectionValues_0202a7b4(&panel->camera);
    panel->camera.nearClip = 0x19a;
    panel->camera.farClip = 0x20000;
    panel->camera.pos.z = 0x10000;
    camera_commit_explicit_projection_0202a8c4(&panel->camera, 0x999a, -0x999a, -0xcccd, 0xcccd);
}
