#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_00[0x08];
    u16 flags;
    u8 pad_0a[0x7E];
    MtxFx33 rotation;
} OrientedObject;

extern const s16 data_0205356c[];
extern void MTX_Identity33_01ff90ec(MtxFx33 *mtx);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_RotX33_01ff9220(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_Concat33_01ff9270(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *ab);

void SetObjectYawPitchMatrix_020a8784(OrientedObject *object, int yaw, int pitch)
{
    MtxFx33 yawMtx;
    MtxFx33 pitchMtx;
    MtxFx33 rotation;
    fx32 yawSin;
    fx32 yawCos;
    fx32 pitchSin;
    int index;

    MTX_Identity33_01ff90ec(&rotation);
    index = yaw >> 4;
    yawSin = -data_0205356c[index];
    yawCos = -data_0205356c[(0x400 - index) & 0xfff];
    pitchSin = -data_0205356c[pitch >> 4];
    if (yawSin != 0 || yawCos != 0) {
        MTX_RotY33_01ff923c(&yawMtx, yawSin, yawCos);
        MTX_Concat33_01ff9270(&yawMtx, &rotation, &rotation);
    }
    if (pitchSin != 0) {
        MTX_RotX33_01ff9220(&pitchMtx, -pitchSin, 0);
        MTX_Concat33_01ff9270(&pitchMtx, &rotation, &rotation);
    }
    object->rotation = rotation;
    object->flags &= 0xffdf;
}
