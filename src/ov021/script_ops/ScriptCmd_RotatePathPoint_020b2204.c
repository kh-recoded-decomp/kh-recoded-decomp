#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    s16 tag;
    s16 pad_02;
    s32 value;
} TaggedValue;

typedef struct {
    u8 pad_00[0x18e60];
    VecFx32 points[1];
} PathData;

extern const s16 data_0205356c[];
extern TaggedValue *ResolveTaggedValueRef_020b0374(void *context, TaggedValue *value);
extern fx32 TaggedValueToFixed_020b03b0(TaggedValue *tagged);
extern PathData *func_ov001_0209c3c0(void);
extern s64 Mul64_02023d9c(s64 a, s64 b);
extern void MTX_Identity33_01ff90ec(MtxFx33 *mtx);
extern void MTX_RotX33_01ff9220(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_Concat33_01ff9270(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *ab);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);

int ScriptCmd_RotatePathPoint_020b2204(void *context, TaggedValue *operands) {
    TaggedValue *index = ResolveTaggedValueRef_020b0374(context, &operands[0]);
    TaggedValue *pitchArg = ResolveTaggedValueRef_020b0374(context, &operands[1]);
    TaggedValue *yawArg = ResolveTaggedValueRef_020b0374(context, &operands[2]);
    PathData *path;
    VecFx32 *point;
    MtxFx33 pitchMtx;
    MtxFx33 yawMtx;
    MtxFx33 rotation;
    u16 yaw;
    u16 pitch;
    ResolveTaggedValueRef_020b0374(context, &operands[3]);
    path = func_ov001_0209c3c0();
    point = &path->points[index->value];
    MTX_Identity33_01ff90ec(&pitchMtx);
    MTX_Identity33_01ff90ec(&yawMtx);
    pitch = (u16)((Mul64_02023d9c(TaggedValueToFixed_020b03b0(pitchArg), 0xB60B60B60BLL) + 0x80000000000LL) >> 44);
    yaw = (u16)((Mul64_02023d9c(TaggedValueToFixed_020b03b0(yawArg), 0xB60B60B60BLL) + 0x80000000000LL) >> 44);
    MTX_RotX33_01ff9220(&pitchMtx, data_0205356c[pitch >> 4], data_0205356c[(0x400 - (pitch >> 4)) & 0xfff]);
    MTX_RotY33_01ff923c(&yawMtx, data_0205356c[yaw >> 4], data_0205356c[(0x400 - (yaw >> 4)) & 0xfff]);
    MTX_Concat33_01ff9270(&pitchMtx, &yawMtx, &rotation);
    MTX_MultVec33_01ff9404(point, &rotation, point);
    return 0;
}
