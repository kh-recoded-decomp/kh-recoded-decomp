#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraState {
    u8 pad00[0x18];
    VecFx32 target;
} CameraState;

typedef struct CameraParams {
    u8 pad00[0xc];
    VecFx32 target;
} CameraParams;

extern void *ReturnToCommitPage_020c3500(void);
extern u32 func_ov048_020c3510(u32 context, u32 data);

void *InitCameraTarget_020c3858(CameraState *camera, u32 mode, CameraParams *params)
{
    ReturnToCommitPage_020c3500();
    camera->target = params->target;
    return (void *)func_ov048_020c3510;
}
