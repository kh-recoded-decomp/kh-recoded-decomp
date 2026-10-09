#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ActorChangeStateFunc)(Actor *actor, s32 state);

typedef struct TrackState {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[2];
    s16 angle;
    fx32 scale;
    u8 pad_18[0xc];
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
    u8 pad_00[0x5a];
    u8 kind;
} HitTargetClass;

struct HitTarget {
    HitTarget *next;
    HitTargetClass *cls;
    u8 pad_08[0x38 - 0x8];
    VecFx32 position;
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

typedef struct OrbitSlot {
    fx32 angle;
    fx32 radius;
} OrbitSlot;

struct Actor {
    u8 pad_0000[0x234];
    u32 modelFlags;
    u8 pad_0238[0x75c - 0x238];
    s32 action;
    s32 frame;
    u8 pad_0764[0x768 - 0x764];
    BOOL animationEnded;
    u8 pad_076c[0x928 - 0x76c];
    u64 flags;
    u8 pad_0930[0x944 - 0x930];
    s32 mode;
    u8 pad_0948[0x970 - 0x948];
    VecFx32 velocity;
    VecFx32 rootMotion;
    u8 pad_0988[0x1708 - 0x988];
    fx32 finisherTimer;
    s32 commandTypes[1];
    u8 commandCount;
    s8 commandIndex;
    u8 pad_1712[0x1724 - 0x1712];
    s32 finisherKind;
    u8 pad_1728[0x1738 - 0x1728];
    VecFx32 orbitCenter;
    OrbitSlot *orbitSlots;
    u8 pad_1748[0x1808 - 0x1748];
    ActorChangeStateFunc changeState;
    u8 pad_180c[0x1812 - 0x180c];
    s16 effectGroupId;
    s16 trackGroup;
};

extern const VecFx32 data_02053438;

extern void Actor_UpdateJump_020ca33c(Actor *actor, BOOL tilted, int angle);
extern void func_ov059_020c997c(Actor *actor);
extern void Actor_GetRootMotionDelta_020cce10(Actor *actor, VecFx32 *out);
extern void func_ov021_020a8ab4(TrackState *state);
extern void func_ov021_020a8ca0(TrackState *state, s32 group);
extern VecFx32 *Actor_GetModelPosition_020cd0d8(Actor *actor);
extern int func_ov021_020af5b4(void);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern void Actor_InitOrbitSlots_020cab6c(Actor *actor, VecFx32 *center, TrackState *effectResource);
extern void Actor_TrySpawnIdleEffect_020c7a70(Actor *actor);
extern HitTarget *func_ov001_0208723c(void);
extern BOOL IsTargetInVerticalRange_020cf100(TargetRef *ref);
extern void func_ov001_020863e0(HitTarget *target, PushParams *params);
extern int UpdateWidgetLayerDefault_020cd3b8(TargetRef *ref, int arg);
extern s32 func_ov001_02087928(void);
extern s32 func_ov001_02087944(s32 eventId);
extern void ZeroBytes0x28_020ac0f8(PathRequest *request);
extern void InitPathSegment_020ac104(PathSegment *segment, s32 id, s32 count, s32 param, const VecFx32 *start,
                                     const VecFx32 *end);
extern void func_ov021_020ac33c(PathRequest *request, PathSegment *segment);
extern BOOL StageRecord_IsDefeated_02087cc4(u32 id);
extern BOOL GetStageEventTargetInfo_02087960(u32 id, EventTargetInfo *out);
extern void ResetStageEntries_02087f00(u32 mask);
extern void Actor_ConsumeCommand_020c9a30(Actor *actor);
extern void Actor_UpdateOrbitEffects_020cabc0(Actor *actor, VecFx32 *center);
extern unsigned int GetGroupMemberCount_020a8e64(int groupId);
extern void EffectGroup_RewindEntry_020cb9ec(s32 groupId, s32 entryIndex);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern s32 func_ov001_0206e750(s32 callerId);
extern void func_ov001_0206e7c0(void);

static inline VecFx32 Vec_Difference(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;

    VEC_Subtract_01ff9e3c(a, b, &result);
    return result;
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

void Actor_UpdateFinisher_020ca794(Actor *actor)
{
    VecFx32 delta;
    TrackState burst;
    VecFx32 toCamera;
    PushParams params;
    TrackState spark;
    PathRequest path;
    PathSegment segment;
    TrackState eventSpark;
    EventTargetInfo info;
    HitTarget *target;
    s32 eventId;
    BOOL ended;
    BOOL finished;
    fx32 numer;
    fx32 denom;
    s32 i;

    if (actor->mode == 7) {
        if (actor->action != 10 && !(actor->modelFlags & 4)) {
            Actor_UpdateJump_020ca33c(actor, 0, 0);
        } else {
            actor->velocity = data_02053438;
        }
        func_ov059_020c997c(actor);
    }
    Actor_GetRootMotionDelta_020cce10(actor, &delta);
    actor->rootMotion = delta;
    if (actor->finisherKind == 2) {
        if (actor->finisherTimer != -1) {
            actor->finisherTimer += 0x1000;
        }
        if (actor->mode == 7 && !(actor->flags & 0x4000) && actor->frame >= 0x9000) {
            func_ov021_020a8ab4(&burst);
            burst.id = 0;
            burst.position = *Actor_GetModelPosition_020cd0d8(actor);
            burst.position.y = 0;
            burst.scale = 0xb33;
            burst.flag25 = 0;
            toCamera = Vec_Difference((VecFx32 *)func_ov021_020af5b4(), &burst.position);
            burst.angle = FixedPointAtan2_020062bc(toCamera.x, toCamera.z);
            switch (actor->finisherKind) {
            case 0:
                break;
            case 1:
                break;
            case 2:
                Actor_InitOrbitSlots_020cab6c(actor, &actor->orbitCenter, &burst);
                break;
            }
            actor->finisherTimer = 0;
            actor->flags |= 0x4000;
            Actor_TrySpawnIdleEffect_020c7a70(actor);
            params.offset = data_02053438;
            params.unk_14 = 0;
            params.flag0c = 0;
            params.flag0d = 0;
            params.count = 2;
            params.unk_18 = 0;
            for (target = func_ov001_0208723c(); target != NULL; target = target->next) {
                if (target->cls->kind == 6 && IsObjectInRange(target)) {
                    func_ov001_020863e0(target, &params);
                    RefreshObjectWidget(target);
                    func_ov021_020a8ab4(&spark);
                    spark.id = 0;
                    spark.position = target->position;
                    spark.flag25 = 0;
                    spark.flag24 = 0;
                    func_ov021_020a8ca0(&spark, actor->trackGroup);
                }
            }
            for (eventId = func_ov001_02087928(); eventId != 0; eventId = func_ov001_02087944(eventId)) {
                ZeroBytes0x28_020ac0f8(&path);
                path.speed = 0x2000;
                path.enabled = 1;
                InitPathSegment_020ac104(&segment, eventId, -1, 0, Actor_GetModelPosition_020cd0d8(actor), NULL);
                switch (actor->finisherKind) {
                case 0:
                    path.mode = 1;
                    break;
                case 1:
                    path.mode = 2;
                    break;
                case 2:
                    path.mode = 3;
                    break;
                }
                func_ov021_020ac33c(&path, &segment);
                if (StageRecord_IsDefeated_02087cc4(eventId)) {
                    RefreshEventWidget(eventId);
                }
                GetStageEventTargetInfo_02087960(eventId, &info);
                func_ov021_020a8ab4(&eventSpark);
                eventSpark.id = 0;
                eventSpark.position = info.position;
                eventSpark.flag25 = 0;
                eventSpark.flag24 = 0;
                func_ov021_020a8ca0(&eventSpark, actor->trackGroup);
            }
            ResetStageEntries_02087f00(3);
            if (actor->commandTypes[actor->commandIndex] == 2) {
                Actor_ConsumeCommand_020c9a30(actor);
            }
        }
    }
    if (actor->finisherTimer != -1) {
        finished = FALSE;
        ended = actor->animationEnded;
        if (actor->finisherKind == 2) {
            if (actor->finisherTimer <= 0x1b000) {
                Actor_UpdateOrbitEffects_020cabc0(actor, &actor->orbitCenter);
            }
            if (actor->finisherTimer >= 0xa000) {
                if (actor->finisherTimer <= 0x1b000) {
                    numer = actor->finisherTimer - 0xa000;
                    denom = 0x11000;
                } else {
                    if (GetGroupMemberCount_020a8e64(actor->effectGroupId)) {
                        for (i = 0; i < 7; i++) {
                            EffectGroup_RewindEntry_020cb9ec(actor->effectGroupId, i);
                        }
                        ended = TRUE;
                    }
                    numer = 0xa000 - (actor->finisherTimer - 0x1b000);
                    denom = 0xa000;
                }
                func_ov001_0206e750((s8)((FX_Div_01ff9c84(numer, denom) * 16) >> 12));
            }
            if (actor->finisherTimer >= 0x25000) {
                finished = TRUE;
            }
        }
        if (ended && actor->mode == 7) {
            actor->flags &= ~(u64)0x4000;
            actor->changeState(actor, 1);
            actor->velocity.y = -0x333;
        }
        if (finished) {
            actor->finisherTimer = -1;
            func_ov001_0206e7c0();
        }
    }
}
