#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    char _0[0x20];
    VecFx32 pos;
} CamActor;

extern u8 *data_ov043_020bd2c0;
extern void camera_commit_projection_0202a814(CamActor *camera);
extern void func_ov043_020bd0a0(void);

void CommitCameraWithCache_020bc820(CamActor *camera) {
    *(VecFx32 *)(data_ov043_020bd2c0 + 0xfc) = camera->pos;
    camera_commit_projection_0202a814(camera);
    func_ov043_020bd0a0();
}
