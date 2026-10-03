#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    VecFx32 position;
    VecFx32 direction;
} CameraView;

extern void func_ov046_020c2bf8(const VecFx32 *direction, VecFx32 *out);

void Camera_FollowAlongViewDirection_020c2bec(CameraView *view)
{
    func_ov046_020c2bf8(&view->direction, &view->position);
}
