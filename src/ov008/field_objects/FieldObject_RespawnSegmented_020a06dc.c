#include "nitro/types.h"
#include "nitro/fx_types.h"
#pragma opt_dead_assignments off
#pragma opt_rotateloops off
#pragma opt_loop_invariants off

typedef struct ShapeParams {
    s32 kind;
    fx32 sizeY;
    fx32 sizeX;
    fx32 sizeZ;
    s32 angle;
} ShapeParams;

typedef struct FxPair {
    fx32 x;
    fx32 y;
} FxPair;

typedef struct ModelResource {
    u8 pad_00[0x17];
    u8 jointCount;
    u8 pad_18[0x28];
    u8 resources[4];
} ModelResource;

typedef struct ActorModelRef {
    u8 pad_00[4];
    ModelResource *model;
    u8 pad_08[0x2c];
    void *jointBuffer;
} ActorModelRef;

typedef struct FieldActor {
    u32 flags;
    u16 animFlags;
    u8 pad_06[0x1e];
    ActorModelRef modelRef;
    u8 pad_5c[0x24];
    u16 angle;
    u8 pad_82[0x8a];
    u8 collision[0x68];
    FxPair extraPosition;
    u8 pad_17c[0x1b];
    u8 tag;
    u8 pad_198[0x28];
} FieldActor;

typedef struct ActorEntry {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0a[6];
    FieldActor actor;
} ActorEntry;

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

typedef struct FieldSegment {
    u8 pad_00[4];
    ActorEntry *entry;
    int jointIndex;
    u8 pad_0c[0xc];
} FieldSegment;

typedef struct FieldObject {
    u8 pad_00[0x08];
    FieldObjectDef *def;
    ActorEntry *entry;
    u8 pad_10[0x28];
    u8 actorId;
    u8 group;
    u8 index;
    u8 pad_3b[0x05];
    VecFx32 position;
    u16 angle;
    u16 stateFlags;
    u8 pad_50[3];
    s8 blendIndex;
    u8 pad_54[8];
    void *jointBuffer;
    int rootJoint;
    u8 pad_64[4];
    FieldSegment segments[24];
} FieldObject;

extern const s8 data_ov008_020a13ee[];
extern const char data_ov008_020a1408[];
extern const char data_ov008_020a1410[];
extern const char data_ov008_020a1394[];

extern BOOL SpawnFieldActor_0208078c(ActorEntry *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL flag20, BOOL isKind2);
extern void func_020358b0(int index, int a1, int a2, int a3);
extern FieldActor *func_02036240(u32 actorId);
extern void Obj_SetPosition_0203569c(FieldActor *entity, const VecFx32 *position);
extern void RebindAnimTracks_020809d0(void *anim, int blendIndex, int frame);
extern void func_0202f4d8(void *anim);
extern BOOL func_ov001_0207f7a4(FieldObject *object);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void func_020359f8(int index, int a1, int a2);
extern void func_02034050(void *collision, int kind, int mask);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff86fc(u32 value, void *dest, u32 size);
extern void ActorSlot_PlaceAndLink_02035a18(ActorEntry *slot, int anchor, const VecFx32 *offset);
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern int FindResourceIndexByName_0201aafc(void *resources, const char *name);
extern void func_ov001_0207f050(u32 bit);
extern void func_020369c8(u32 id, fx32 x, fx32 y);


static inline int FindModelResource(ModelResource *model, const char *name)
{
    void *resources = model != NULL ? model->resources : NULL;
    return resources != NULL ? FindResourceIndexByName_0201aafc(resources, name) : -1;
}

void FieldObject_RespawnSegmented_020a06dc(FieldObject *object)
{
    FieldObjectDef *def = object->def;
    ShapeParams shape;
    VecFx32 origin;
    char name[16];
    FxPair position;
    FxPair pair;
    FieldActor *actor;
    ActorModelRef *modelRef;
    int i;
    u16 angle;
    FieldSegment *segment;

    SpawnFieldActor_0208078c(object->entry, object->group, object->index, object->actorId, &shape, def->shapeKind, def->sizeX, def->sizeY, def->sizeZ, object->angle, TRUE, TRUE);
    func_020358b0(object->actorId, def->recordParamA, def->recordParamB, 3);
    actor = func_02036240(object->actorId);
    actor->tag = 0xff;
    Obj_SetPosition_0203569c(actor, &object->position);
    angle = object->angle;
    if (!(actor->flags & 0x20)) {
        actor->angle = angle;
        actor->animFlags |= 0x20;
    }
    RebindAnimTracks_020809d0(&actor->animFlags, object->blendIndex, 0);
    func_0202f4d8(&actor->animFlags);
    if (func_ov001_0207f7a4(object)) {
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, TRUE);
        func_020359f8(object->actorId, 0, 0);
    } else {
        ActorSlot_SetFlag8ByIndex_02036120(object->actorId, FALSE);
    }
    object->entry->flags |= 0x200;
    func_02034050(actor->collision, 3, 0xc);
    origin = object->position;
    modelRef = &actor->modelRef;
    for (i = 0; i < 24; i++) {
        segment = &object->segments[i];
        segment->entry = NNSi_FndAllocFromDefaultHeap_0202a178(sizeof(ActorEntry));
        func_01ff86fc(0, segment->entry, sizeof(ActorEntry));
        SpawnFieldActor_0208078c(segment->entry, object->group, object->index, -1, &shape, 3, 0x1800, 0x1800, 0x1800, 0, TRUE, TRUE);
        segment->entry->actor.tag = i;
        ActorSlot_PlaceAndLink_02035a18(segment->entry, 0, NULL);
        func_01ff86fc(0, name, sizeof(name));
        OS_SPrintf_02002428(name, data_ov008_020a1408, data_ov008_020a1410, data_ov008_020a13ee[i]);
        segment->jointIndex = FindModelResource(modelRef->model, name);
        func_02034050(segment->entry->actor.collision, 3, 0xc);
        pair.x = 0;
        pair.y = 0x25;
        position = pair;
        segment->entry->actor.extraPosition = position;
    }
    object->jointBuffer = NNSi_FndAllocFromDefaultHeap_0202a178(modelRef->model->jointCount * 0x58);
    modelRef->jointBuffer = object->jointBuffer;
    object->rootJoint = FindModelResource(modelRef->model, data_ov008_020a1394);
    func_ov001_0207f050(0xc);
    func_020369c8(object->actorId, 0, 0x25);
}
