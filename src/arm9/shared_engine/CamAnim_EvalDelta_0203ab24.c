#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraPose {
    fx32 fovySin;
    fx32 fovyCos;
    u8 pad_08[0xc];
    VecFx32 position;
    VecFx32 target;
    VecFx32 up;
} CameraPose;

typedef struct CameraAnim {
    u8 pad_00[0x10];
    CameraPose pose;
} CameraAnim;

extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void CamAnim_Update_0203aafc(CameraAnim *anim);

void CamAnim_EvalDelta_0203ab24(CameraAnim *anim, CameraPose *delta)
{
    CameraPose *pose = &anim->pose;
    CameraPose previous;

    MI_CpuCopy8_01ff89a8(pose, &previous, sizeof(CameraPose));
    CamAnim_Update_0203aafc(anim);
    VEC_Subtract_01ff9e3c(&pose->target, &previous.target, &delta->target);
    VEC_Subtract_01ff9e3c(&pose->position, &previous.position, &delta->position);
    VEC_Subtract_01ff9e3c(&pose->up, &previous.up, &delta->up);
    delta->fovySin = anim->pose.fovySin - previous.fovySin;
    delta->fovyCos = pose->fovyCos - previous.fovyCos;
}
