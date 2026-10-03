#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeParams {
    s32 kind;
    fx32 sizeY;
    fx32 sizeX;
    fx32 sizeZ;
    s32 angle;
} ShapeParams;

typedef struct FieldObjectDef {
    u8 pad_00[0x54];
    s32 recordParamA;
    s32 recordParamB;
    u8 pad_5c[0x14];
    fx32 sizeX;
    fx32 sizeY;
    fx32 sizeZ;
    s8 shapeKind;
} FieldObjectDef;

typedef struct FieldEntry {
    u8 pad_00[0x1C0];
    s32 soundId;
} FieldEntry;

typedef struct FieldObject {
    u8 pad_00[0x08];
    FieldObjectDef *def;
    FieldEntry *entry;
    u8 pad_10[0x28];
    u8 actorId;
    u8 group;
    u8 index;
    u8 pad_3b[0x05];
    VecFx32 position;
    u16 angle;
    u16 stateFlags;
    u8 pad_50[0x03];
    s8 blendIndex;
    u8 pad_54[0x04];
    u32 unk_58_lo : 15;
    s32 pendingReset : 1;
    u32 unk_58_hi : 16;
} FieldObject;

typedef struct ActorCallback {
    void (*func)(void *);
    void *arg;
} ActorCallback;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x7A];
    u16 angle;
    u8 pad_82[0x8A];
    u8 collision[0x70];
    ActorCallback onTouch;
    ActorCallback onRelease;
} FieldActor;

extern BOOL SpawnFieldActor_0208078c(FieldEntry *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void func_020358b0(int index, int a1, int a2, int a3);
extern void func_ov001_02082714(FieldObject *object, int state);
extern FieldActor *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(FieldActor *entity, const VecFx32 *position);
extern void func_ov001_020825a0(void *arg);
extern void func_ov001_020825bc(void *arg);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4e8(void *anim);
extern BOOL func_ov001_0207f7a4(FieldObject *object);
extern int func_ov001_02063a38(void);
extern void FieldObject_SetEnabled_0207f6f4(FieldObject *object, BOOL enabled);
extern void ApplyRecordOrSetState_020822f8(FieldObject *object, BOOL enabled);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void SetCollisionObjectPosition_02033f48(void *collision, const VecFx32 *position);
extern void func_ov001_02085f18(FieldObject *object);
extern void func_ov001_02085e48(FieldObject *object);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

static inline VecFx32 AddVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 sum;
    VEC_Add_01ff9e0c(a, b, &sum);
    return sum;
}

void ActivateFieldSwitchObject_02082070(FieldObject *object)
{
    FieldObjectDef *def = object->def;
    ShapeParams shape;
    FieldActor *actor;
    ActorCallback touch;
    ActorCallback release;
    BOOL enabled;
    VecFx32 position;
    u16 angle;
    VecFx32 lift;

    SpawnFieldActor_0208078c(object->entry, object->group, object->index, object->actorId, &shape, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, !(object->stateFlags & 8), TRUE);
    func_020358b0(object->actorId, def->recordParamA, def->recordParamB, 3);
    func_ov001_02082714(object, 0);
    actor = func_02036240(object->actorId);
    Obj_SetPosition_0203569c(actor, &object->position);
    angle = object->angle;
    if (!(actor->flags & 0x20)) {
        actor->angle = angle;
        actor->animFlags |= 0x20;
    }
    touch.func = func_ov001_020825a0;
    touch.arg = object;
    actor->onTouch = touch;
    release.func = func_ov001_020825bc;
    release.arg = object;
    actor->onRelease = release;
    object->entry->soundId = 0xB33;
    RebindAnimTracks_020809d0(&actor->animFlags, object->blendIndex, 0);
    func_0202f4e8(&actor->animFlags);
    if (func_ov001_0207f7a4(object) && func_ov001_02063a38() != 7) {
        enabled = TRUE;
    } else {
        enabled = FALSE;
    }
    FieldObject_SetEnabled_0207f6f4(object, enabled);
    ApplyRecordOrSetState_020822f8(object, enabled);
    lift = MakeVec(0, 0xA66, 0);
    position = AddVec(&object->position, &lift);
    SetCollisionObjectPosition_02033f48(actor->collision, &position);
    switch (func_ov001_02063a38()) {
    case 4:
        func_ov001_02085f18(object);
        break;
    case 7:
        func_ov001_02085e48(object);
        break;
    }
    if (object->pendingReset) {
        object->pendingReset = 0;
        object->stateFlags |= 4;
        func_ov001_02082714(object, 2);
    }
}
