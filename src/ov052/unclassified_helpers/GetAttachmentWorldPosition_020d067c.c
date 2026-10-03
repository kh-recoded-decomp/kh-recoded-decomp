#include "nitro/types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad0[0x7e];
    u16 roll;
} BodyPose;

typedef struct {
    u32 flags;
    BodyPose pose;
} BodyModel;

extern s16 data_0205356c[];
extern u16 func_ov052_020ceb7c(int entity);
extern VecFx32 *func_ov052_020ceb54(int entity);
extern void GetAttachmentOffset_020cbf88(VecFx32 *out, int owner, int slot);
extern void MTX_RotZ33_01ff9258(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

void GetAttachmentWorldPosition_020d067c(VecFx32 *out, int entity, int slot)
{
    VecFx32 result;
    VecFx32 offset;
    VecFx32 base;
    MtxFx33 facing;
    MtxFx33 roll;
    BodyPose *pose = &(*(BodyModel **)(entity + 0x230))->pose;
    int angle = func_ov052_020ceb7c(entity);
    int index;
    GetAttachmentOffset_020cbf88(&base, entity, 2);
    GetAttachmentOffset_020cbf88(&offset, entity, slot);
    index = pose->roll >> 4;
    MTX_RotZ33_01ff9258(&roll, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
    index = angle >> 4;
    MTX_RotY33_01ff923c(&facing, -data_0205356c[index], -data_0205356c[(0x400 - index) & 0xfff]);
    MTX_MultVec33_01ff9404(&offset, &roll, &offset);
    MTX_MultVec33_01ff9404(&offset, &facing, &offset);
    VEC_Add_01ff9e0c(&offset, func_ov052_020ceb54(entity), &result);
    *out = result;
}
