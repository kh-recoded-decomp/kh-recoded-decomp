#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    union {
        u32 value;
        struct {
            u16 first;
            u16 second;
        } pair;
    } key;
    s32 kind;
} EntryKey;

typedef struct {
    u8 pad_000[0x60];
    EntryKey entries[24];
    u8 count;
} EntryList;

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    VecFx32 base;
    VecFx32 top;
    VecFx32 axis;
    fx32 radius;
} AxisCylinder;

typedef struct {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct {
    void (*func)(void);
    void *arg;
} QueryCallback;

typedef struct {
    s32 mode;
    s32 mask;
} QueryFilter;

typedef struct {
    u32 words[0x12];
    QueryCallback callback;
    u32 tail[4];
} CollisionQuery;

typedef struct {
    u32 target;
    s32 side;
    s32 strength;
    u8 pad_0c[0xc];
    u32 object;
    u8 pad_1c[0xb8];
} HitResult;

typedef struct {
    u16 id;
    u16 flags;
    u16 kind;
    u16 pad_06;
    VecFx32 position;
    s32 width;
    s32 height;
    s32 displayWidth;
    s32 displayHeight;
} EventTargetInfo;

typedef struct {
    u8 pad_00[0xc];
    s32 unk_0c;
    u8 pad_10[0x15];
    u8 side;
    u8 pad_26[8];
    u16 unk_2e;
    u16 level;
    u8 pad_32[2];
    VecFx32 position;
    u8 pad_40[8];
} StageEventArg;

typedef struct {
    u8 data[0x28];
} PathSegment;

typedef struct {
    u32 owner;
    u8 pad_04[0xc];
    u8 flag;
    u8 pad_11[0x17];
} PathTracker;

typedef struct {
    u8 data[0x18];
} ContactInfo;

typedef struct {
    VecFx32 offset;
    u8 unk_0c;
    u8 unk_0d;
    u32 layer;
    u32 unk_14;
    u32 unk_18;
} HitReaction;

typedef struct {
    u32 flags;
    u8 pad_04[8];
    fx32 radius;
    u8 pad_10[0x20];
    s32 elevated;
    s32 mode;
    u8 pad_38[0x25];
    u8 layer : 4;
    u8 pad_5d_4 : 4;
} ActorInfo;

typedef struct {
    s32 kind;
    u8 pad_04[0xc];
    EntryKey key;
    fx32 height;
    u32 flags;
    u8 pad_20[0x28];
} ActorState;

typedef struct {
    u8 pad_000[2];
    s8 status;
    u8 pad_003[5];
    u32 ownerId;
    u8 pad_00c[0x18];
    VecFx32 velocity;
    u8 pad_030[0xa4];
    VecFx32 position;
    u8 pad_0e0[0x58];
    ActorInfo *info;
    u8 pad_13c[2];
    s16 eventIds[8];
    u8 pad_14e[2];
    ActorState *state;
} Actor;

typedef struct {
    u8 pad_0000[0x230];
    void *model;
    u8 pad_0234[0x15b4 - 0x234];
    EntryList trackList;
    s32 trackLayer;
} World;

typedef struct {
    u8 pad_00[8];
    Actor *actors;
    u8 pad_0c[9];
    u8 count;
    u8 pad_16[0x26];
    ActorState *states;
    u8 pad_40[4];
    World *world;
} ActorManager;

typedef struct HitTarget HitTarget;
typedef struct {
    u8 pad_00[0x24];
    BOOL (*sweep)(HitTarget *target, SweptShape *shape, ContactInfo *contact);
} HitTargetVtable;

struct HitTarget {
    u8 pad_00[4];
    HitTargetVtable *vtable;
};

extern const VecFx32 data_02053438;

extern s32 func_ov031_020bc700(void);
extern VecFx32 *func_ov043_020bca1c(void);
extern fx32 FX_Sqrt_01ff9cfc(fx32 x);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Normalize_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void InitAxisCylinderShape_0203adcc(CollisionShape *shape, AxisCylinder *cylinder, const VecFx32 *base, const VecFx32 *top,
                                           const VecFx32 *axis, fx32 radius);
extern void MakeSphereShape_0203ad14(CollisionShape *shape, Sphere *sphere, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape,
                                         QueryWorkspace *workspace, QueryFilter *filter);
extern void *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void func_ov059_020cdd10(void);
extern void MarkList_AddAtObject_020cde4c(ActorManager *manager, Actor *actor);
extern void SoundRequest_Play_020cd9c0(ActorState *request, VecFx32 *position);
extern u32 func_ov001_020863e0(HitTarget *target, HitReaction *reaction);
extern BOOL func_ov018_020a3470(u32 object);
extern s32 func_ov001_020878b8(s32 eventIndex, SweptShape *shape, ContactInfo *contact, u16 *outResult);
extern void ZeroBytes0x28_020ac0f8(PathTracker *tracker);
extern VecFx32 *Actor_GetModelPosition_020cd0d8(World *world);
extern void InitPathSegment_020ac104(PathSegment *segment, s32 id, s32 count, s32 param, const VecFx32 *start, const VecFx32 *end);
extern void func_ov021_020ac33c(PathTracker *tracker, PathSegment *segment);
extern BOOL StageRecord_IsDefeated_02087cc4(u32 id);
extern int UpdateWidgetLayerDefault_020cd3b8(EntryKey *key, s32 layer);
extern u32 func_ov021_020ac148(HitResult *result);
extern u32 func_ov059_020cf394(EntryList *list, EntryKey *key);
extern HitResult FindStrongestHit_020ab0c8(ActorManager *manager, Actor *actor, VecFx32 *position, const VecFx32 *delta);
extern int IsStageEventReady_02087c78(u32 id);
extern void func_01ff86fc(u32 value, void *dest, u32 size);
extern u32 GetBoundedEntryField_0206db5c(int index);
extern int DispatchStageEventArg_020878d4(u32 id, StageEventArg *arg);
extern u32 EntryList_FindByValue_020cf41c(EntryList *list, u32 value);
extern u32 EntryList_FindByFirstId_020cf490(EntryList *list, u32 id);
extern void GetStageEventTargetInfo_02087960(u32 id, EventTargetInfo *info);
extern BOOL EntryKey_Equals_020cf19c(EntryKey *a, EntryKey *b);
extern u32 SpawnSoundSlot_0204da8c(u32 owner, u32 kind, void *position, u32 flags);

typedef struct {
    u8 pad_000[0x13e];
    s16 id;
} EventSlot;

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

static inline BOOL IsElevatedState(ActorState *state)
{
    if (state->kind >= 3) {
        return TRUE;
    }
    return FALSE;
}

static inline BOOL IsLayerTarget(u16 kind)
{
    switch (kind) {
    case 9:
    case 0x2e:
    case 0x2f:
        return FALSE;
    }
    return TRUE;
}

static inline VecFx32 ZeroVec(void)
{
    return MakeVec(0, 0, 0);
}

static inline VecFx32 VecAdd(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 r;
    VEC_Add_01ff9e0c(a, b, &r);
    return r;
}

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 r;
    VEC_Subtract_01ff9e3c(a, b, &r);
    return r;
}

static inline CollisionShape MakeAxisShape(AxisCylinder *cylinder, const VecFx32 *top, const VecFx32 *bottom, const VecFx32 *axis,
                                           fx32 length)
{
    CollisionShape shape;

    InitAxisCylinderShape_0203adcc(&shape, cylinder, top, bottom, axis, length);
    return shape;
}

static inline CollisionShape MakeAxisCylinderShape(AxisCylinder *cylinder, const VecFx32 *top, const VecFx32 *bottom)
{
    VecFx32 axis = VecSub(bottom, top);

    return MakeAxisShape(cylinder, top, bottom, &axis, VEC_Normalize_01ffaff4(&axis, &axis));
}

static inline QueryFilter MakeFilter(s32 mode, s32 mask)
{
    QueryFilter f;
    f.mode = mode;
    f.mask = mask;
    return f;
}

static inline QueryCallback MakeCallback(void (*func)(void), void *arg)
{
    QueryCallback c;
    c.func = func;
    c.arg = arg;
    return c;
}

static inline EntryKey MakeValueKey(u32 value)
{
    EntryKey k;
    k.key.value = value;
    k.kind = 1;
    return k;
}

static inline EntryKey MakePairKey(u16 id)
{
    EntryKey k;
    k.key.pair.first = id;
    k.key.pair.second = 0xffff;
    k.kind = 2;
    return k;
}

BOOL Projectile_UpdateCollision_020ce3bc(ActorManager *manager, Actor *actor, VecFx32 *base, BOOL useVelocity)
{
    SweptShape sweptCopy;
    QueryWorkspace workspace;
    CollisionQuery query;
    HitResult hit;
    SweptShape sphereCopy;
    HitResult emptyHit;
    StageEventArg eventArg;
    SweptShape swept;
    CollisionQuery queryInit;
    SweptShape sphereSweep;
    AxisCylinder cylinder;
    VecFx32 top;
    VecFx32 bottom;
    VecFx32 posCopy;
    Sphere sphere;
    ContactInfo contact;
    HitReaction reaction;
    PathTracker tracker;
    PathSegment segment;
    EventTargetInfo targetInfo;
    VecFx32 upOffset;
    VecFx32 downOffset;
    VecFx32 diff;
    VecFx32 zeroCopy;
    QueryFilter filter;
    EntryKey defeatedKey;
    EntryKey objectKey;
    EntryKey hitKey;
    EntryKey eventKey;
    s32 layer;
    BOOL blocked;
    int k;
    int j;
    BOOL moved;
    VecFx32 *pos;
    EventSlot *firstSlot;
    EventSlot *secondSlot;
    BOOL found;
    int i;
    ActorState *state;
    const VecFx32 *delta;
    u32 eventId;
    ActorState *other;

    state = actor->state;
    pos = &actor->position;
    if (state->kind != 2) {
        if (pos->z < -func_ov031_020bc700() - 0xc00 || pos->z > func_ov043_020bca1c()->z ||
            FX_Sqrt_01ff9cfc((fx32)(((s64)pos->x * pos->x + (s64)pos->y * pos->y) >> 12)) > 0xa000) {
            state->key.kind = 0;
            return TRUE;
        }
    }
    blocked = FALSE;
    if (state->kind != 3 && state->kind != 4 && !(state->flags & 4)) {
        upOffset = MakeVec(0, 0xa000, 0);
        top = VecAdd(base, &upOffset);
        downOffset = MakeVec(0, -0x8cd, 0);
        bottom = VecAdd(base, &downOffset);
        diff = VecSub(pos, base);
        swept.shape = MakeAxisCylinderShape(&cylinder, &top, &bottom);
        swept.delta = diff;
        OffsetBoxByDelta_0203ac70(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
        sweptCopy = swept;
        filter = MakeFilter(0, 0x10);
        CollisionQuery_Init_02034c74(&queryInit, 0, manager->world->model, 8, 2, 1, &sweptCopy, &workspace, &filter);
        query = queryInit;
        query.callback = MakeCallback(func_ov059_020cdd10, NULL);
        if (SweepWorldCollision_020364a0(&query)) {
            blocked = TRUE;
        } else if (pos->y < 0) {
            MarkList_AddAtObject_020cde4c(manager, actor);
            SoundRequest_Play_020cd9c0(state, pos);
            actor->status = -1;
            state->key.kind = 0;
            return FALSE;
        }
    }
    posCopy = *pos;
    actor->info->flags = state->flags;
    if (blocked) {
        actor->info->flags |= 4;
    }
    actor->info->layer = (u8)((state->height + 0x71f) / 0x1000);
    actor->info->radius = 0x8cd;
    if (state->kind >= 3) {
        actor->info->elevated = TRUE;
    } else {
        actor->info->elevated = FALSE;
    }
    if (state->kind == 2) {
        MakeSphereShape_0203ad14(&sphereSweep.shape, &sphere, pos, actor->info->radius);
        sphereSweep.delta = actor->velocity;
        OffsetBoxByDelta_0203ac70(&sphereSweep.shape.bounds, &sphereSweep.sweptBounds, &sphereSweep.delta);
        sphereCopy = sphereSweep;
        {
        switch (state->key.kind) {
        case 1:
            found = ((HitTarget *)state->key.key.value)->vtable->sweep((HitTarget *)state->key.key.value, &sphereCopy, &contact);
            if (found) {
                *(VecFx32 *)&reaction.offset = data_02053438;
                reaction.unk_0c = 0;
                reaction.unk_0d = 0;
                reaction.layer = actor->info->layer;
                reaction.unk_14 = 0;
                reaction.unk_18 = 0;
                func_ov001_020863e0((HitTarget *)state->key.key.value, &reaction);
                if (func_ov018_020a3470(state->key.key.value)) {
                    UpdateWidgetLayerDefault_020cd3b8(&state->key, manager->world->trackLayer);
                }
            }
            break;
        case 2:
            eventId = func_ov001_020878b8(state->key.key.pair.first, &sphereCopy, &contact, NULL);
            found = FALSE;
            if (eventId) {
                found = TRUE;
            }
            if (eventId) {
                ZeroBytes0x28_020ac0f8(&tracker);
                tracker.owner = actor->ownerId;
                tracker.flag = 0;
                InitPathSegment_020ac104(&segment, eventId, -1, 0, Actor_GetModelPosition_020cd0d8(manager->world), NULL);
                func_ov021_020ac33c(&tracker, &segment);
                if (StageRecord_IsDefeated_02087cc4(eventId)) {
                    UpdateWidgetLayerDefault_020cd3b8(&state->key, manager->world->trackLayer);
                }
            }
            break;
        }
        if (found) {
            func_ov021_020ac148(&emptyHit);
            MarkList_AddAtObject_020cde4c(manager, actor);
            SoundRequest_Play_020cd9c0(state, pos);
            func_ov059_020cf394(&manager->world->trackList, &state->key);
            actor->status = -1;
        }
        }
    } else {
    switch (state->kind) {
    case 3:
        actor->info->mode = 1;
        actor->info->flags |= 6;
        break;
    case 4:
        actor->info->mode = 2;
        actor->info->flags |= 4;
        break;
    default:
        actor->info->mode = 0;
        break;
    }
    if (useVelocity) {
        delta = &actor->velocity;
    } else {
        zeroCopy = ZeroVec();
        delta = &zeroCopy;
    }
    hit = FindStrongestHit_020ab0c8(manager, actor, &posCopy, delta);
    if (state->kind == 3 || state->kind == 4) {
        if (hit.strength == 4) {
            for (i = 0; i < 8; i++) {
                firstSlot = (EventSlot *)((s16 *)actor + i);
                if (firstSlot->id != -1 && IsStageEventReady_02087c78((u16)firstSlot->id) &&
                    !StageRecord_IsDefeated_02087cc4((u16)firstSlot->id)) {
                    func_01ff86fc(0, &eventArg, sizeof(StageEventArg));
                    switch (state->kind) {
                    case 3:
                        eventArg.side = 1;
                        break;
                    case 4:
                        eventArg.side = 2;
                        break;
                    }
                    eventArg.unk_2e = 0;
                    eventArg.level = (*(u8 **)(GetBoundedEntryField_0206db5c(0) + 0x1d4))[1];
                    eventArg.position = *pos;
                    eventArg.unk_0c = 0;
                    DispatchStageEventArg_020878d4((u16)firstSlot->id, &eventArg);
                }
            }
        }
        if (state->kind == 3 && (hit.strength == 3 || hit.strength == 4)) {
            MarkList_AddAtObject_020cde4c(manager, actor);
            SoundRequest_Play_020cd9c0(state, pos);
            if (hit.strength == 4) {
                for (i = 0; i < 8; i++) {
                    secondSlot = (EventSlot *)((s16 *)actor + i);
                    if (secondSlot->id != -1 && StageRecord_IsDefeated_02087cc4((u16)secondSlot->id)) {
                        defeatedKey = MakePairKey(secondSlot->id);
                        UpdateWidgetLayerDefault_020cd3b8(&defeatedKey, 0);
                    }
                }
            } else if (hit.strength == 3) {
                objectKey = MakeValueKey(hit.object);
                if (func_ov018_020a3470(hit.object)) {
                    UpdateWidgetLayerDefault_020cd3b8(&objectKey, 0);
                }
            }
        }
    }
    if (actor->status == 2) {
        if (hit.strength == 3 && func_ov018_020a3470(hit.object)) {
            if (state->kind == 2 && manager->world->trackList.count != 0 &&
                EntryList_FindByValue_020cf41c(&manager->world->trackList, hit.object) != -1) {
                layer = manager->world->trackLayer;
            } else {
                layer = 0;
            }
            hitKey = MakeValueKey(hit.object);
            UpdateWidgetLayerDefault_020cd3b8(&hitKey, layer);
            if (state->kind == 2) {
                func_ov059_020cf394(&manager->world->trackList, &hitKey);
            }
            if (EntryKey_Equals_020cf19c(&state->key, &hitKey)) {
                state->key.kind = 0;
            }
        }
        for (k = 0; k < 8; k++) {
            if (actor->eventIds[k] != -1 && StageRecord_IsDefeated_02087cc4((u16)actor->eventIds[k])) {
                if (state->kind == 2 && manager->world->trackList.count != 0 &&
                    EntryList_FindByFirstId_020cf490(&manager->world->trackList, (u16)actor->eventIds[k]) != -1) {
                    GetStageEventTargetInfo_02087960((u16)actor->eventIds[k], &targetInfo);
                    if (targetInfo.id == 9 || (u16)(targetInfo.id + 0xffd2) <= 1) {
                        layer = 0;
                    } else {
                        layer = manager->world->trackLayer;
                    }
                } else {
                    layer = 0;
                }
                eventKey = MakePairKey(actor->eventIds[k]);
                UpdateWidgetLayerDefault_020cd3b8(&eventKey, layer);
                if (state->kind == 2) {
                    func_ov059_020cf394(&manager->world->trackList, &eventKey);
                }
                if (EntryKey_Equals_020cf19c(&state->key, &eventKey)) {
                    state->key.kind = 0;
                }
            }
        }
        if (state->kind == 2 && state->key.kind != 0) {
            for (j = 0; j < manager->count; j++) {
                other = &manager->states[j];
                if (other != state && manager->actors[j].status != -1 && other->kind == 2 && other->key.kind != 0) {
                    moved = FALSE;
                    switch (other->key.kind) {
                    case 1:
                        if (func_ov018_020a3470(other->key.key.value)) {
                            other->key = state->key;
                            moved = TRUE;
                        }
                        break;
                    case 2:
                        if (StageRecord_IsDefeated_02087cc4(other->key.key.pair.first)) {
                            other->key = state->key;
                            moved = TRUE;
                        }
                        break;
                    }
                    if (moved) {
                        break;
                    }
                }
            }
            if (j == manager->count) {
                func_ov059_020cf394(&manager->world->trackList, &state->key);
            }
            state->key.kind = 0;
        }
        MarkList_AddAtObject_020cde4c(manager, actor);
        actor->status = -1;
        SpawnSoundSlot_0204da8c(0x19d, 2, &actor->position, 0);
    }
    }
    return FALSE;
}
