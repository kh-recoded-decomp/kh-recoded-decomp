#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct ShapeStorage {
    u8 data[0x28];
} ShapeStorage;

typedef struct QueryWorkspace {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct QueryCallback {
    void (*func)(void);
    void *arg;
} QueryCallback;

typedef struct CollisionQuery {
    u32 words[0x12];
    QueryCallback filter;
    QueryCallback callback;
    u32 tail[2];
} CollisionQuery;

typedef struct PlayerEntry {
    u8 pad_000[0x214];
    void (*push)(struct PlayerEntry *self, VecFx32 *force);
} PlayerEntry;

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x38 - 0x33];
    VecFx32 position;
    u8 pad_44[0x3];
    s8 pose;
    u8 pad_48[0x70 - 0x48];
    u16 unk_70_lo : 7;
    u16 facing : 2;
    u16 unk_70_hi : 7;
    u8 pad_72[0xc0 - 0x72];
    u32 flags;
} FieldObject;

extern PlayerEntry *GetBoundedEntryField_0206db5c(int index);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern void func_ov001_02086434(FieldObject *object, int pose);
extern void *func_02036240(int actorId);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape func_0203adcc(ShapeStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void func_ov016_020a4448(void);
extern void StartFieldUnitMotion_020a2b38(FieldObject *object, fx32 speed, int angle);

static inline void BuildSegmentShape(CollisionShape *shape, ShapeStorage *storage, const VecFx32 *start, const VecFx32 *end)
{
    VecFx32 axis;
    VecFx32 delta;
    fx32 length;

    VEC_Subtract_01ff9e3c(end, start, &delta);
    axis = delta;
    length = func_01ffaff4(&axis, &axis);
    *shape = func_0203adcc(storage, start, end, &axis, length);
}

static inline int RadiansToIndex(fx32 radians)
{
    return (u32)((int)(((s64)radians * 0x28be60db9391LL + 0x80000000000LL) >> 32) << 4) >> 16;
}

static inline VecFx32 ScaleVec(const VecFx32 *vec, fx32 scale)
{
    VecFx32 result = *vec;

    ScaleVecFx32InPlace_0204a5e4(&result, scale);
    return result;
}

void ApplyFieldObjectForceToPlayer_020a446c(FieldObject *object)
{
    CollisionQuery query;
    QueryWorkspace workspace;
    VecFx32 player;
    VecFx32 center;
    CollisionShape shape;
    ShapeStorage storage;
    void *actor;
    int facing;
    fx32 offset;

    GetBoundedEntryField_0206db5c(0);
    player = *func_ov001_0206dc4c(0);
    object->flags &= ~0x80000;
    if (object->pose != 1) {
        func_ov001_02086434(object, 1);
    }
    if (object->position.y - 0x10 > player.y + 0x1333) {
        return;
    }
    if (object->position.y + 0x1780 <= player.y) {
        return;
    }
    facing = object->facing;
    switch (facing & 1) {
    case 0:
        offset = object->position.x;
        if (offset - 0xccd > player.x) {
            return;
        }
        if (player.x > offset + 0xccd) {
            return;
        }
        offset = player.z - object->position.z;
        if (facing == 0 && offset > 0) {
            return;
        }
        if (facing == 2 && offset < 0) {
            return;
        }
        break;
    case 1:
        offset = object->position.z;
        if (offset - 0xccd > player.z) {
            return;
        }
        if (player.z > offset + 0xccd) {
            return;
        }
        offset = player.x - object->position.x;
        if (facing == 1 && offset > 0) {
            return;
        }
        if (facing == 3 && offset < 0) {
            return;
        }
        break;
    }
    actor = func_02036240(object->actorId);
    center = object->position;
    center.y += 0xc00;
    player.y = center.y;
    BuildSegmentShape(&shape, &storage, &center, &player);
    CollisionQuery_Init_02034c74(&query, 0, actor, 0xf, 2, 0, &shape, &workspace, NULL);
    query.filter.func = func_ov016_020a4448;
    query.filter.arg = object;
    if (SweepWorldCollision_020364a0(&query) == NULL) {
        VecFx32 away;
        VecFx32 normal;
        VecFx32 force;
        PlayerEntry *entry;

        VEC_Subtract_01ff9e3c(&player, &object->position, &away);
        VEC_Normalize_01ff9f88(&away, &normal);
        force = ScaleVec(&normal, -0xcd);
        entry = GetBoundedEntryField_0206db5c(0);
        if (entry->push != NULL) {
            entry->push(entry, &force);
        }
        StartFieldUnitMotion_020a2b38(object, 0x1000, RadiansToIndex((((object->facing + 2) & 3) * 0x3244) / 2));
        object->flags |= 0x80000;
    }
}
