#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MtxFx33 {
    fx32 m[3][3];
} MtxFx33;

typedef struct JointAnimResult {
    u32 flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx33 rot;
    VecFx32 trans;
} JointAnimResult;

typedef struct CameraAnim {
    u8 pad_00[8];
    void *anmObj;
    u8 pad_0c[4];
    fx32 sinRoll;
    fx32 cosRoll;
    u8 pad_18[4];
    fx32 nearClip;
    fx32 farClip;
    VecFx32 position;
    VecFx32 target;
    VecFx32 up;
    VecFx32 offset;
} CameraAnim;

extern u8 *data_0205ab60;
extern u32 data_02055d70;
extern VecFx32 data_0205588c;
extern s16 data_0205356c[];

extern void SampleJointAnimationObject_0201ae80(JointAnimResult *result, void *anmObj, u32 index);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern fx32 func_02006450(fx32 a, fx32 b);
extern void AdvanceAnimFrame_0203a99c(CameraAnim *anim);

void CamAnim_ApplyPose_0203a9dc(CameraAnim *anim)
{
    VecFx32 up;
    JointAnimResult roll;
    JointAnimResult eye;
    fx32 scaleX, scaleY, scaleZ;
    fx32 targetX, targetY, targetZ;
    fx32 angle;
    int index;

    *(u32 *)(data_0205ab60 + 0xe8) = data_02055d70;
    SampleJointAnimationObject_0201ae80(&eye, anim->anmObj, 0);
    SampleJointAnimationObject_0201ae80(&roll, anim->anmObj, 1);
    up = data_0205588c;
    targetX = eye.trans.x;
    targetZ = eye.trans.z;
    targetY = eye.trans.y;
    anim->target.x = targetX;
    anim->target.y = targetY;
    anim->target.z = targetZ;
    scaleX = eye.scale.x;
    if (scaleX == 0x7ffff000) {
        anim->position.x = 0;
        anim->position.y = -0x1000;
        anim->position.z = 0;
        MTX_MultVec33_01ff9404(&up, &eye.rot, &anim->up);
        MTX_MultVec33_01ff9404(&anim->position, &eye.rot, &anim->position);
        VEC_Add_01ff9e0c(&anim->position, &anim->target, &anim->position);
    } else {
        scaleY = eye.scale.y;
        scaleZ = eye.scale.z;
        anim->position.y = scaleY;
        anim->position.z = scaleZ;
        anim->position.x = scaleX;
        MTX_MultVec33_01ff9404(&up, &eye.rot, &anim->up);
    }
    VEC_Add_01ff9e0c(&anim->position, &anim->offset, &anim->position);
    VEC_Add_01ff9e0c(&anim->target, &anim->offset, &anim->target);
    angle = func_02006450(FX_Div_01ff9c84(roll.trans.x, 0x2000), 0xc00);
    index = (u16)((angle * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4;
    anim->nearClip = roll.trans.y;
    anim->farClip = roll.trans.z;
    anim->sinRoll = data_0205356c[index];
    anim->cosRoll = data_0205356c[(0x400 - index) & 0xfff];
    AdvanceAnimFrame_0203a99c(anim);
}

