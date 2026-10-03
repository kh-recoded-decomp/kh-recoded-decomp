#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    u8 pad_000[0x11c];
    u8 surface[0x170];
    u16 stageBits : 11;
    u16 stageEntry : 3;
    u16 stageUnused : 2;
    u8 pad_28e[0x32];
    VecFx32 position;
} PlayerActor;

typedef struct {
    u8 pad_00[8];
    PlayerActor *player;
} FieldContext;

typedef struct {
    u8 pad_00[0x34];
    VecFx32 position;
} ScriptObject;

typedef struct {
    u8 pad_00[8];
    s16 distance[4];
    s16 angle[4];
    s16 flags[4];
} PlaceCommand;

extern FieldContext data_ov021_020b56a4;
extern const s16 data_0205356c[];

extern s16 *ResolveTaggedValueRef_020b0374(ScriptObject *obj, s16 *value);
extern s32 TaggedValueToFixed_020b03b0(s16 *tagged);
extern s32 TaggedValueToInt_020b0398(s16 *tagged);
extern void func_ov001_02091c34(PlayerActor *actor, VecFx32 *out);
extern u32 GetStageEntryParam_02099218(u32 id);
extern fx32 Surface_GetKindValue_02034c24(void *surface);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void GetStageEntryPosition_020992ac(u32 id, VecFx32 *outPosition);
extern void func_01ff90ec(MtxFx33 *mtx);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern BOOL func_ov021_020afd28(VecFx32 *from, VecFx32 *to, VecFx32 *hitNormal, VecFx32 *hitPoint, int mode);

s32 ScriptOp_PlaceAroundPlayer_020b1850(ScriptObject *obj, PlaceCommand *cmd)
{
    s16 *distanceRef = ResolveTaggedValueRef_020b0374(obj, cmd->distance);
    s16 *angleRef = ResolveTaggedValueRef_020b0374(obj, cmd->angle);
    s16 *flagsRef = ResolveTaggedValueRef_020b0374(obj, cmd->flags);
    PlayerActor *player = data_ov021_020b56a4.player;
    fx32 distance;
    fx32 degrees;
    u32 flags;
    int angle;
    fx32 minDistance;
    VecFx32 base;
    VecFx32 direction;
    VecFx32 hitNormal;
    VecFx32 hitPoint;
    MtxFx33 rotation;

    func_ov001_02091c34(player, &base);
    distance = TaggedValueToFixed_020b03b0(distanceRef);
    degrees = TaggedValueToFixed_020b03b0(angleRef);
    flags = TaggedValueToInt_020b0398(flagsRef);
    angle = (u16)(((s64)degrees * 0xb60b60b60bLL + 0x80000000000LL) >> 44);
    minDistance = GetStageEntryParam_02099218(player->stageEntry) + Surface_GetKindValue_02034c24(player->surface);
    if (distance < minDistance) {
        distance = minDistance;
    }
    if (flags & 1) {
        VEC_Subtract_01ff9e3c(&player->position, &base, &direction);
        direction.y = 0;
        func_01ffaff4(&direction, &direction);
    } else {
        GetStageEntryPosition_020992ac(player->stageEntry, &direction);
    }
    if (flags & 2) {
        flags |= 4;
    }
    if (flags & 4) {
        func_01ff90ec(&rotation);
        MTX_RotY33_01ff923c(&rotation, data_0205356c[angle >> 4], data_0205356c[(0x400 - (angle >> 4)) & 0xfff]);
        MTX_MultVec33_01ff9404(&direction, &rotation, &direction);
        VEC_MultAdd_01ffa09c(distance, &direction, &base, &obj->position);
        if (func_ov021_020afd28(&player->position, &obj->position, &hitNormal, &hitPoint, 1)) {
            if (flags & 2) {
                obj->position = player->position;
            } else {
                obj->position = hitPoint;
            }
        }
    }
    return 0;
}
