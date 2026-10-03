#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraPose {
    fx32 angleX;
    fx32 angleY;
    u8 pad_08[0xc];
    VecFx32 target;
    VecFx32 position;
    VecFx32 up;
} CameraPose;

typedef struct FieldCamera {
    CameraPose pose;
    u8 pad_38[0x98 - 0x38];
    s32 mode;
    u8 pad_9c[0x140 - 0x9c];
    u8 anim[0x10];
    CameraPose altPose;
    u8 pad_188[0x1e4 - 0x188];
    s32 animActive;
} FieldCamera;

extern FieldCamera *data_ov001_020a04f4;

extern void func_ov001_0208afb8(void);
extern void func_ov001_0208b5a8(void);
extern void func_ov001_0208b6c4(void);
extern void func_ov001_0208b0d8(int a, int b, int c, int d);
extern void func_ov021_020af4ac(CameraPose *pose);
extern void CamAnim_EvalDelta_0203ab24(void *anim, CameraPose *delta);
extern void MI_CpuCopy32_01ff89a8(const void *src, void *dest, u32 size);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetSoundListenerFrame_0204dc94(const VecFx32 *position, const VecFx32 *forward, const VecFx32 *up);

int UpdateFieldCamera_0208b780(void)
{
    CameraPose current;
    VecFx32 forward;
    CameraPose delta;
    CameraPose pose;
    FieldCamera *camera = data_ov001_020a04f4;

    switch (camera->mode) {
    case -1:
        return 0;
    case 0:
        func_ov021_020af4ac(&camera->pose);
        MI_CpuCopy32_01ff89a8(&camera->pose, &current, sizeof(CameraPose));
        goto apply;
    case 1:
        func_ov001_0208afb8();
        MI_CpuCopy32_01ff89a8(&camera->altPose, &current, sizeof(CameraPose));
        goto apply;
    case 6:
        func_ov001_0208b5a8();
        goto useBase;
    case 7:
        func_ov001_0208b6c4();
        goto useBase;
    default:
        func_ov001_0208b0d8(0, 0, 0, 0);
        if (camera->animActive != 0) {
            goto animate;
        }
    useBase:
        func_ov021_020af4ac(&camera->pose);
        MI_CpuCopy32_01ff89a8(&camera->pose, &current, sizeof(CameraPose));
        goto apply;
    animate:
        CamAnim_EvalDelta_0203ab24(camera->anim, &delta);
        MI_CpuCopy32_01ff89a8(&camera->pose, &pose, sizeof(CameraPose));
        VEC_Add_01ff9e0c(&camera->pose.position, &delta.position, &pose.position);
        VEC_Add_01ff9e0c(&camera->pose.target, &delta.target, &pose.target);
        VEC_Add_01ff9e0c(&camera->pose.up, &delta.up, &pose.up);
        pose.angleX += delta.angleX;
        pose.angleY += delta.angleY;
        func_ov021_020af4ac(&pose);
        MI_CpuCopy32_01ff89a8(&pose, &current, sizeof(CameraPose));
        break;
    }
apply:
    VEC_Subtract_01ff9e3c(&current.target, &current.position, &forward);
    SetSoundListenerFrame_0204dc94(&current.position, &forward, &current.up);
    return 0;
}
