#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct Box {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct HitQuery {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} HitQuery;

typedef struct TrackState {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 flag24;
    u8 flag25;
    u8 pad_26[2];
    s16 prevIndex;
    s16 index;
} TrackState;

typedef struct PathRequest {
    fx32 speed;
    u8 pad_04[0xc];
    u8 enabled;
    u8 mode;
    u8 pad_12[0x16];
} PathRequest;

typedef struct PathSegment {
    s32 id;
    s32 count;
    s32 param;
    VecFx32 start;
    VecFx32 end;
    u32 pad_24;
} PathSegment;

typedef struct EventTargetInfo {
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

typedef struct PushParams {
    VecFx32 offset;
    u8 flag0c;
    u8 flag0d;
    u8 pad_0e[2];
    s32 count;
    s32 unk_14;
    s32 unk_18;
} PushParams;

typedef struct HitTarget HitTarget;

typedef struct HitTargetClass {
    u8 pad_00[0x24];
    BOOL (*collide)(HitTarget *target, HitQuery *query, int arg);
    u8 pad_28[0x5a - 0x28];
    u8 kind;
} HitTargetClass;

struct HitTarget {
    HitTarget *next;
    HitTargetClass *cls;
    u8 pad_08[0x38 - 0x8];
    VecFx32 position;
    u8 pad_44[0x64 - 0x44];
    VecFx32 velocity;
    u8 pad_70[0xa0 - 0x70];
    int state;
};

typedef struct TargetRef {
    union {
        HitTarget *object;
        struct {
            u16 eventId;
            u16 subId;
        } event;
    } u;
    int type;
} TargetRef;

typedef struct QuadTreeRef {
    int *root;
} QuadTreeRef;

typedef struct FieldSystem {
    u8 pad_00[4];
    QuadTreeRef *tree;
} FieldSystem;

typedef struct Actor {
    u8 pad_0000[0x1720];
    fx32 effectTimer;
    u8 pad_1724[0x1748 - 0x1724];
    CollisionCylinder cylinder;
    u8 quadNode[0xc];
    u8 quadFlags;
    u8 pad_1781[0x1798 - 0x1781];
    HitQuery hitQuery;
    u8 pad_17dc[0x1816 - 0x17dc];
    s16 effectGroup;
    u8 pad_1818[2];
    s16 trackGroup;
} Actor;

extern const VecFx32 data_02053438;

extern VecFx32 *Actor_GetModelPosition_020cd0d8(Actor *actor);
extern FieldSystem *func_02036230(void);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Normalize_01ffaff4(const VecFx32 *source, VecFx32 *destination);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *source, VecFx32 *destination);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void InitCylinderShape_0203aeac(CollisionShape *shape, CollisionCylinder *cylinder, const VecFx32 *start,
                                       const VecFx32 *end, const VecFx32 *direction, fx32 length, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const s32 *src, Box *dst, const VecFx32 *delta);
extern void QuadTree_ReinsertNodeIfFlagSet_02033f10(int *tree, void *node);
extern void *GetGroupMemberData_020a8eec(s32 group, s32 index);
extern int Anim_GetFrame_0202f4a0(void *anim, int channel);
extern int func_0202f4b8(void *anim, int channel);
extern void InvokeHandlerOnIndexedRecord_020a8e88(s32 group, s32 index, u32 value);
extern void SetSlotEntryValue_020a8f4c(s32 group, s32 index, u16 value);
extern HitTarget *func_ov001_0208723c(void);
extern BOOL IsTargetInVerticalRange_020cf100(TargetRef *ref);
extern void func_ov001_020863e0(HitTarget *target, PushParams *params);
extern int UpdateWidgetLayerDefault_020cd3b8(TargetRef *ref, int arg);
extern BOOL TestFlagBit10_020a380c(HitTarget *target);
extern void SetFlagBit10_020a37f8(HitTarget *target);
extern void TurnVecTowardVecLimited_0204b1fc(VecFx32 *vec, const VecFx32 *target, fx32 maxAngle);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern fx32 GetField28_020bbff4(void);
extern const VecFx32 *GetSubStruct1C_020bbfe0(void);
extern void func_ov021_020a8ab4(TrackState *state);
extern void func_ov021_020a8ca0(TrackState *state, s32 group);
extern s32 func_ov001_02087928(void);
extern s32 func_ov001_02087944(s32 eventId);
extern u16 func_ov001_020878b8(s32 eventId, HitQuery *query, s32 arg, u16 *out);
extern void ZeroBytes0x28_020ac0f8(PathRequest *request);
extern void InitPathSegment_020ac104(PathSegment *segment, s32 id, s32 count, s32 param, const VecFx32 *start,
                                     const VecFx32 *end);
extern void func_ov021_020ac33c(PathRequest *request, PathSegment *segment);
extern BOOL StageRecord_IsDefeated_02087cc4(u32 id);
extern BOOL GetStageEventTargetInfo_02087960(u32 id, EventTargetInfo *out);
extern void PlaySoundChecked_0204d8d0(int sound, int arg);
extern void Actor_ExtendCountdown_020c89fc(Actor *actor, fx32 duration);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 v;

    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

static inline VecFx32 Vec_Sum(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;

    VEC_Add_01ff9e0c(a, b, &result);
    return result;
}

static inline VecFx32 Vec_Difference(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;

    VEC_Subtract_01ff9e3c(a, b, &result);
    return result;
}

static inline CollisionShape MakeCylinderShape(CollisionCylinder *cylinder, const VecFx32 *start, const VecFx32 *end,
                                               const VecFx32 *direction, fx32 length, fx32 radius)
{
    CollisionShape shape;

    InitCylinderShape_0203aeac(&shape, cylinder, start, end, direction, length, radius);
    return shape;
}

static inline TargetRef MakeObjectRef(HitTarget *object)
{
    TargetRef ref;

    ref.u.object = object;
    ref.type = 1;
    return ref;
}

static inline TargetRef MakeEventRef(u16 eventId, u16 subId)
{
    TargetRef ref;

    ref.u.event.eventId = eventId;
    ref.u.event.subId = subId;
    ref.type = 2;
    return ref;
}

static inline BOOL IsObjectInRange(HitTarget *object)
{
    TargetRef ref = MakeObjectRef(object);

    return IsTargetInVerticalRange_020cf100(&ref);
}

static inline void RefreshObjectWidget(HitTarget *object)
{
    TargetRef ref = MakeObjectRef(object);

    UpdateWidgetLayerDefault_020cd3b8(&ref, 0);
}

static inline void RefreshEventWidget(u16 eventId)
{
    TargetRef ref = MakeEventRef(eventId, 0);

    UpdateWidgetLayerDefault_020cd3b8(&ref, 0);
}

#define OffsetPoint(point, offset, pos, dy)     ((offset) = MakeVec(0, (dy), 0), (point) = Vec_Sum((pos), &(offset)), &(point))

static inline CollisionShape MakeSweepShape(CollisionCylinder *cylinder, const VecFx32 *start, const VecFx32 *end,
                                            fx32 radius)
{
    VecFx32 direction = Vec_Difference(end, start);

    return MakeCylinderShape(cylinder, start, end, &direction, VEC_Normalize_01ffaff4(&direction, &direction), radius);
}

static inline void PushTarget(HitTarget *target, const VecFx32 *origin, VecFx32 *velocity, VecFx32 *push, VecFx32 *up)
{
    *velocity = target->velocity;
    *push = Vec_Difference(&target->position, origin);
    if (push->y < 0) {
        push->y = 0;
    }
    VEC_NormalizeUnchecked_01ff9f88(push, push);
    if (push->x == 0 && push->y == 0 && push->z == 0) {
        *push = MakeVec(0, FX32_ONE, 0);
    } else {
        *up = MakeVec(0, FX32_ONE, 0);
        TurnVecTowardVecLimited_0204b1fc(push, up, 0x430);
    }
    ScaleVecFx32InPlace_0204a5e4(push, 0x4cd);
    VEC_MultAdd_01ffa09c(-GetField28_020bbff4(), GetSubStruct1C_020bbfe0(), velocity, velocity);
    target->velocity = Vec_Sum(velocity, push);
}

#define FX_MUL_ROUND(a, b) ((fx32)(((fx64)(a) * (b) + (FX32_ONE >> 1)) >> 12))

void Actor_UpdateSweepHits_020c9d14(Actor *actor)
{
    HitQuery query;
    PushParams params;
    VecFx32 velocity;
    VecFx32 push;
    TrackState spark;
    PathRequest path;
    PathSegment segment;
    TrackState eventSpark;
    EventTargetInfo info;
    VecFx32 bottom;
    VecFx32 lowOffset;
    VecFx32 top;
    VecFx32 highOffset;
    VecFx32 up;
    VecFx32 zero;
    VecFx32 *modelPos;
    FieldSystem *system;
    HitTarget *target;
    s32 eventId;
    fx32 t;
    fx32 inv;
    BOOL hit;

    modelPos = Actor_GetModelPosition_020cd0d8(actor);
    system = func_02036230();
    if (actor->effectTimer != 0xa000) {
        t = FX_Div_01ff9c84(actor->effectTimer, 0xa000);
    } else {
        t = FX32_ONE;
    }
    inv = FX32_ONE - t;
    /* Arguments evaluate right to left, so top comes first. */
    query.shape = MakeSweepShape(&actor->cylinder, OffsetPoint(bottom, lowOffset, modelPos, -0x333),
                                 OffsetPoint(top, highOffset, modelPos,
                                             FX_MUL_ROUND(inv, 0x2000) + FX_MUL_ROUND(t, 0x3333)),
                                 FX_MUL_ROUND(inv, 0x800) + FX_MUL_ROUND(t, 0x1800));
    zero = data_02053438;
    query.delta = data_02053438;
    OffsetBoxByDelta_0203ac70(query.shape.bounds, &query.sweptBounds, &query.delta);
    actor->hitQuery = query;
    if (actor->effectTimer != 0xa000) {
        actor->effectTimer += FX32_ONE;
        if (actor->effectTimer > 0xa000) {
            actor->effectTimer = 0xa000;
        }
    }
    actor->quadFlags |= 1;
    QuadTree_ReinsertNodeIfFlagSet_02033f10(system->tree->root, actor->quadNode);
    {
        void *anim = GetGroupMemberData_020a8eec(actor->effectGroup, 0);
        int frame = Anim_GetFrame_0202f4a0(anim, 0);

        if (frame >= func_0202f4b8(anim, 0) - FX32_ONE) {
            InvokeHandlerOnIndexedRecord_020a8e88(actor->effectGroup, 0, 1);
            SetSlotEntryValue_020a8f4c(actor->effectGroup, 0, 4);
        }
    }
    params.offset = zero;
    params.unk_14 = 0;
    params.flag0c = 0;
    params.flag0d = 0;
    params.count = 1;
    params.unk_18 = 0;
    for (target = func_ov001_0208723c(); target != NULL; target = target->next) {
        if (target->cls->kind == 6) {
            if (target->state == 2 || IsObjectInRange(target)) {
                if (target->cls->collide(target, &actor->hitQuery, 0)) {
                    hit = TRUE;
                    if (target->state != 2) {
                        func_ov001_020863e0(target, &params);
                        RefreshObjectWidget(target);
                    } else if (!TestFlagBit10_020a380c(target)) {
                        PushTarget(target, modelPos, &velocity, &push, &up);
                        SetFlagBit10_020a37f8(target);
                    } else {
                        hit = FALSE;
                    }
                    if (hit) {
                        func_ov021_020a8ab4(&spark);
                        spark.id = 0;
                        spark.position = target->position;
                        spark.flag25 = 0;
                        spark.flag24 = 0;
                        spark.prevIndex = 0xcd;
                        spark.index = 1;
                        func_ov021_020a8ca0(&spark, actor->trackGroup);
                    }
                }
            }
        }
    }
    for (eventId = func_ov001_02087928(); eventId != 0; eventId = func_ov001_02087944(eventId)) {
        u16 hitId = func_ov001_020878b8(eventId, &actor->hitQuery, 0, NULL);

        if (hitId != 0) {
            ZeroBytes0x28_020ac0f8(&path);
            path.speed = 0xc00;
            path.enabled = 1;
            InitPathSegment_020ac104(&segment, eventId, -1, 0, Actor_GetModelPosition_020cd0d8(actor), NULL);
            path.mode = 4;
            func_ov021_020ac33c(&path, &segment);
            if (StageRecord_IsDefeated_02087cc4(eventId)) {
                RefreshEventWidget(hitId);
            }
            GetStageEventTargetInfo_02087960(hitId, &info);
            func_ov021_020a8ab4(&eventSpark);
            eventSpark.id = 0;
            eventSpark.position = info.position;
            eventSpark.flag25 = 0;
            eventSpark.flag24 = 0;
            func_ov021_020a8ca0(&eventSpark, actor->trackGroup);
            PlaySoundChecked_0204d8d0(0xcd, 1);
        }
    }
    Actor_ExtendCountdown_020c89fc(actor, 0x6000);
}
