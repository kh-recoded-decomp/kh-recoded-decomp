#pragma optimize_for_size on
#pragma opt_loop_invariants off
#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ShapeParams {
    u32 words[5];
} ShapeParams;

typedef struct CollisionObject {
    u8 pad_00[0x40];
    s32 id;
} CollisionObject;

typedef struct AnimBlock {
    u16 flags;
    u8 pad_02[0x22];
    u8 *model;
    u8 pad_28[0x7c - 0x28];
    u16 shapeId;
    u8 pad_7e[0xa4 - 0x7e];
    VecFx32 position;
} AnimBlock;

typedef struct Entity {
    u32 flags;
    AnimBlock anim;
    u8 pad_b4[0x10c - 0xb4];
    CollisionObject collision;
} Entity;

typedef struct FieldBody {
    u8 pad_00[8];
    u16 flags;
    u8 pad_0a[6];
    Entity entity;
} FieldBody;

typedef struct PatrolPath {
    VecFx32 *points;
    s8 count;
    s8 key;
    u8 pad_06[2];
} PatrolPath;

typedef struct PatrolDef {
    u8 pad_00[0x54];
    s32 tableA;
    s32 tableB;
    u8 pad_5c[0x70 - 0x5c];
    fx32 extentB;
    fx32 extentA;
    fx32 extentC;
    s8 shapeKind;
} PatrolDef;

typedef struct PatrolObject {
    u8 pad_00[8];
    PatrolDef *def;
    FieldBody *body;
    u8 pad_10[0x38 - 0x10];
    u8 slot;
    u8 group;
    u8 index;
    u8 pad_3b[5];
    VecFx32 position;
    u16 extentD;
    u16 flags;
    u16 saveBitOffset;
    u8 saveBitCount;
    s8 animBlend;
    u8 pad_54[0x60 - 0x54];
    PatrolPath *paths;
    VecFx32 forward;
    VecFx32 up;
    s8 pathCount;
    s8 pathIndex;
    s8 pathKey;
    s8 pointIndex;
    s8 previousPoint;
    u8 pad_81[3];
    u8 record[0x188 - 0x84];
    s32 nodeIndex;
} PatrolObject;

typedef struct FieldState {
    u8 pad_000[0x214];
    u32 flags;
} FieldState;

extern FieldState *data_ov001_020a0460;
extern char data_ov001_0209f160[];

extern BOOL func_ov001_0208078c(FieldBody *entry, u8 group, u8 index, u32 slot, ShapeParams *shapeOut, s8 shapeKind,
                                fx32 extentB, fx32 extentA, fx32 extentC, u16 extentD, BOOL visible, BOOL isKind2);
extern void func_020358b0(int index, int a1, int a2, int a3);
extern Entity *func_02036240(int index);
extern void Obj_SetPosition_0203569c(Entity *entity, const VecFx32 *position);
extern void RebindAnimTracks_020809d0(AnimBlock *anim, int blendIndex, int frame);
extern void func_0202f4e8(AnimBlock *anim);
extern s8 GetCtxModeByte_02068084(void);
extern u32 ObjectManager_GetFirstEntryParam_0207ee14(int index);
extern u32 ObjectManager_GetSecondEntryParam_0207ee48(int index);
extern void *RetainOrInitializeSharedRecord_0202c80c(int a, int b);
extern void *func_0202c48c(u32 fileId, u32 mode);
extern void func_0202ed9c(u8 *object, void *value, void *source, int extra);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void func_01ff86fc(u32 value, void *dst, u32 size);
extern int OS_SPrintf_02002428(char *dst, const char *fmt, ...);
extern int FindResourceIndexByName_0201aafc(void *dict, const char *name);
extern BOOL IsObjectFlagClear_0207f7a4(PatrolObject *object);
extern void ActorSlot_SetFlag8ByIndex_02036120(int index, BOOL enable);
extern void func_020359f8(int index, int param2, int param3);
extern void func_02034050(CollisionObject *collision, int a, int b);
extern u16 FieldObject_GetSavedValue_0207f9a8(PatrolObject *object);
extern void SetCollisionObjectPosition_02033f48(CollisionObject *object, const VecFx32 *position);
extern BOOL DetachFromLeaderQuadTree_020836d8(PatrolObject *object);
extern VecFx32 **FindActiveSlotEntry_02083c38(PatrolObject *object);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern u32 random_next_scaled_0202aa04(u32 upperBound);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;

    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

void func_ov001_02083730(PatrolObject *object)
{
    PatrolDef *def = object->def;
    ShapeParams shape;
    char name[16];
    VecFx32 forward;
    VecFx32 up;
    int key;
    int i;
    Entity *entity;
    void *dict;
    int nodeIndex;
    u16 extentD;
    BOOL visible;
    AnimBlock *anim;

    visible = (s32)((object->flags & 8) ? (void *)0 : (void *)1);
    func_ov001_0208078c(object->body, object->group, object->index, object->slot, &shape, def->shapeKind, def->extentB,
                        def->extentA, def->extentC, object->extentD, visible, TRUE);
    func_020358b0(object->slot, def->tableA, def->tableB, 3);
    entity = func_02036240(object->slot);
    object->body->flags |= 0x200;
    Obj_SetPosition_0203569c(entity, &object->position);
    extentD = object->extentD;
    if (!(entity->flags & 0x20)) {
        entity->anim.shapeId = extentD;
        entity->anim.flags |= 0x20;
    }
    dict = NULL;
    RebindAnimTracks_020809d0(&entity->anim, object->animBlend, 0);
    func_0202f4e8(&entity->anim);
    if (GetCtxModeByte_02068084() != 7) {
        void *record = RetainOrInitializeSharedRecord_0202c80c(ObjectManager_GetFirstEntryParam_0207ee14(0x7c), 3);
        void *buffer = func_0202c48c(ObjectManager_GetSecondEntryParam_0207ee48(0x7c), 3);

        func_0202ed9c(object->record, record, buffer, 3);
        NNSi_FndFreeFromDefaultHeap_0202a1c4(buffer);
        func_01ff86fc(0, name, sizeof(name));
        OS_SPrintf_02002428(name, data_ov001_0209f160);
        if (entity->anim.model != NULL) {
            dict = entity->anim.model + 0x40;
        }
        if (dict != NULL) {
            nodeIndex = FindResourceIndexByName_0201aafc(dict, name);
        } else {
            nodeIndex = -1;
        }
        object->nodeIndex = nodeIndex;
    }
    if (IsObjectFlagClear_0207f7a4(object)) {
        ActorSlot_SetFlag8ByIndex_02036120(object->slot, TRUE);
        func_020359f8(object->slot, 0, 0);
        func_02034050(&entity->collision, 1, 4);
        object->flags |= 0x10;
        object->flags |= 0x20;
    } else {
        ActorSlot_SetFlag8ByIndex_02036120(object->slot, FALSE);
        object->flags &= ~0x10;
        object->flags &= ~0x20;
    }
    key = (FieldObject_GetSavedValue_0207f9a8(object) >> 1) & 0x3f;
    for (i = 0; i < object->pathCount; i++) {
        PatrolPath *paths = object->paths;

        if (key == paths[i].key) {
            object->pathKey = key;
            object->pathIndex = i;
            object->previousPoint = object->pointIndex;
            object->position = paths[object->pathIndex].points[object->pointIndex];
            forward = MakeVec(0, 0, FX32_ONE);
            object->forward = forward;
            up = MakeVec(0, FX32_ONE, 0);
            object->up = up;
            if (object->body->entity.collision.id != -1) {
                SetCollisionObjectPosition_02033f48(&object->body->entity.collision, &object->position);
            }
            anim = &object->body->entity.anim;
            anim->position = object->position;
            break;
        }
    }
    if (DetachFromLeaderQuadTree_020836d8(object)) {
        VecFx32 **points = FindActiveSlotEntry_02083c38(object);
        VecFx32 *target = func_ov001_0206dc4c(0);

        if (func_01ffa0f4(&(*points)[object->pointIndex], target) <= 0x6000) {
            u32 offset = random_next_scaled_0202aa04(object->paths[object->pathIndex].count - 1);

            object->pointIndex = (object->pointIndex + 1 + offset) % object->paths[object->pathIndex].count;
            object->previousPoint = object->pointIndex;
            object->position = object->paths[object->pathIndex].points[object->pointIndex];
            Obj_SetPosition_0203569c(&object->body->entity, &object->position);
        }
        data_ov001_020a0460->flags |= 0x80000;
    }
}
