#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct PathCamera {
    VecFx32 position;
    VecFx32 lookDir;
    u8 pad18[0xc];
    VecFx32 anchor;
    VecFx32 targetDir;
    VecFx32 offset;
    fx32 turnRate;
} PathCamera;

extern void Camera_GetRaisedPlayerPosition_020c14a8(VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *in, VecFx32 *out);
extern void func_0204aea8(VecFx32 *out, const VecFx32 *vec, const VecFx32 *normal);
extern s16 AngleBetweenVecs_0204b070(const VecFx32 *a, const VecFx32 *b);
extern int FixedPointMultiply12(int left, int right);
extern void func_0204b1fc(VecFx32 *vec, const VecFx32 *target, s32 step);

#define FX_MUL_ROUND(a, b) ((fx32)(((s64)(a) * (b) + 0x800) >> 12))

void TrackPlayerCameraDirection_020c3888(PathCamera *camera)
{
    VecFx32 player;
    VecFx32 side;
    VecFx32 up;
    VecFx32 projected;
    VecFx32 forwardTmp;
    VecFx32 dir;
    VecFx32 delta;
    VecFx32 deltaArg;
    VecFx32 upTmp;
    VecFx32 sideTmp;
    VecFx32 sideNorm;
    VecFx32 sideArg;
    s32 angle;
    s32 step;

    Camera_GetRaisedPlayerPosition_020c14a8(&player);
    if (camera->anchor.x == player.x && camera->anchor.y == player.y && camera->anchor.z == player.z) {
        forwardTmp.x = FX32_ONE;
        forwardTmp.y = 0;
        forwardTmp.z = 0;
        camera->targetDir = forwardTmp;
    } else {
        VEC_Subtract_01ff9e3c(&player, &camera->anchor, &delta);
        deltaArg = delta;
        func_01ff9f88(&deltaArg, &dir);
        camera->targetDir = dir;
    }
    upTmp.x = 0;
    upTmp.y = FX32_ONE;
    upTmp.z = 0;
    up = upTmp;
    sideTmp.x = -FX_MUL_ROUND(camera->offset.z, up.y);
    sideTmp.y = 0;
    sideTmp.z = FX_MUL_ROUND(camera->offset.x, up.y);
    sideArg = sideTmp;
    func_01ff9f88(&sideArg, &sideNorm);
    side = sideNorm;
    func_0204aea8(&projected, &camera->targetDir, &side);
    camera->targetDir = projected;
    angle = (s32)(((s64)AngleBetweenVecs_0204b070(&camera->lookDir, &camera->targetDir) * 0x6488) / 0x10000);
    if (angle < 0x10) {
        angle = 0x10;
    }
    step = FixedPointMultiply12(angle, camera->turnRate);
    if (step > 0x595) {
        step = 0x595;
    } else if (step < 0x47) {
        step = 0x47;
    }
    func_0204b1fc(&camera->lookDir, &camera->targetDir, step);
}
