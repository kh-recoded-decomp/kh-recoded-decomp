#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TrackState {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    s16 scale;
    u16 angle;
    s32 rate;
    void *target;
    u8 pad_1c[8];
    u8 mode;
    u8 loop;
    s16 priority;
    s16 soundId;
    s16 volume;
} TrackState;

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

typedef struct ProbeBody {
    CollisionShape shape;
    VecFx32 delta;
    s32 sweptBounds[6];
} ProbeBody;

typedef struct ProbeQuery {
    ProbeBody body;
    u8 pad_44[4];
    VecFx32 velocity;
    u8 pad_54[0xc];
} ProbeQuery;

typedef struct ProbeFilter {
    s32 mask;
    u8 pad_04[8];
    fx32 range;
    u8 pad_10[2];
    u8 kind;
    u8 pad_13[0xd];
    s32 owner;
    u16 ignoreStatic : 1;
    u16 ignoreActors : 1;
    u16 ignoreHidden : 1;
    u16 unused3 : 1;
    u16 hitTargets : 1;
    u16 unused5 : 2;
    u16 nearestOnly : 1;
    u16 unused8 : 8;
} ProbeFilter;

typedef struct ProbeResult {
    u8 pad_00[8];
    s32 hitType;
    u8 pad_0c[0xc];
    u16 hitId;
    u8 pad_1a[0xc2];
} ProbeResult;

typedef struct EventEffect {
    int state;
    int timer;
    int active;
    int hasTarget;
    u8 pad_10[8];
    int targetId;
    u8 pad_1c[0xc];
    BOOL releaseReady;
    u8 pad_2c[0xa];
    s16 hitGroup;
} EventEffect;

typedef struct Entity Entity;

typedef VecFx32 *(*EntityPositionFunc)(Entity *entity);

struct Entity {
    u8 pad_000[0xbc];
    VecFx32 position;
    u8 pad_0c8[0x224 - 0xc8];
    EntityPositionFunc getPosition;
    u8 pad_228[0x760 - 0x228];
    int chargeTime;
    u8 pad_764[0x9b4 - 0x764];
    u8 slot;
};

extern EventEffect *data_ov010_020a1dc0;

extern void func_ov021_020ac0b8(ProbeQuery *query);
extern s16 func_ov052_020ceb7c(Entity *entity);
extern void func_ov021_020a9160(VecFx32 *out, const VecFx32 *center, u16 angle, const VecFx32 *offset);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void InitCylinderShape_0203aeac(CollisionShape *shape, CollisionCylinder *cylinder, const VecFx32 *start, const VecFx32 *end, const VecFx32 *direction, fx32 length, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const s32 *src, s32 *dst, const VecFx32 *delta);
extern void ZeroBytes0x28_020ac0f8(ProbeFilter *filter);
extern void ZeroAndSetField0xd4_020ac150(ProbeResult *result);
extern void func_ov001_020645dc(u32 eventId);
extern void func_ov001_020645e8(u32 eventId);
extern BOOL func_ov021_020ac164(int mode, ProbeQuery *query, ProbeFilter *filter, ProbeResult *result);
extern BOOL GetStageEventTargetInfo_02087960(u16 id, EventTargetInfo *info);
extern void func_ov021_020a8ab4(TrackState *state);
extern int func_ov021_020a8ca0(TrackState *request, int groupId);
extern u32 SpawnSoundSlot_0204da8c(u32 owner, u32 kind, VecFx32 *position, u32 flags);

void Entity_ProbeReleaseTarget_020a10b8(Entity *entity)
{
    EventEffect *effect = data_ov010_020a1dc0;
    BOOL found = FALSE;
    int hitId = -1;

    if (!effect->releaseReady && entity->chargeTime >= 0x12000 && entity->chargeTime < 0x19000) {
        ProbeQuery query;
        ProbeResult result;
        ProbeBody body;
        TrackState request;
        ProbeFilter filter;
        CollisionCylinder cylinder;
        VecFx32 start;
        VecFx32 end;
        EventTargetInfo info;
        VecFx32 direction;
        VecFx32 delta;
        CollisionShape shape;
        u16 angle;
        fx32 length;
        ProbeResult *hit;
        ProbeFilter *probe;

        func_ov021_020ac0b8(&query);
        start = *(entity->getPosition != NULL ? entity->getPosition(entity) : &entity->position);
        angle = func_ov052_020ceb7c(entity) + 0x8000;
        end.x = 0;
        end.y = 0;
        end.z = 0x1e000;
        func_ov021_020a9160(&end, &start, angle, &end);
        VEC_Subtract_01ff9e3c(&end, &start, &delta);
        direction = delta;
        length = func_01ffaff4(&direction, &direction);
        InitCylinderShape_0203aeac(&shape, &cylinder, &start, &end, &direction, length, 0x1000);
        body.shape = shape;
        body.delta = query.velocity;
        OffsetBoxByDelta_0203ac70(body.shape.bounds, body.sweptBounds, &body.delta);
        query.body = body;
        probe = &filter;
        ZeroBytes0x28_020ac0f8(probe);
        probe->mask = 0;
        probe->kind = 9;
        probe->range = 0x64000;
        probe->owner = 0;
        probe->ignoreStatic = 0;
        probe->ignoreHidden = 0;
        probe->hitTargets = 1;
        probe->ignoreActors = 0;
        probe->nearestOnly = 1;
        hit = &result;
        ZeroAndSetField0xd4_020ac150(hit);
        func_ov001_020645dc(0x3716);
        while (func_ov021_020ac164(0, &query, probe, hit)) {
            if (hit->hitType == 4) {
                hitId = hit->hitId;
                found = TRUE;
            }
        }
        func_ov001_020645e8(0x3716);
        if (found && GetStageEventTargetInfo_02087960(hitId, &info)) {
            func_ov021_020a8ab4(&request);
            request.id = entity->slot;
            request.loop = 0;
            request.mode = 0;
            request.position = info.position;
            func_ov021_020a8ca0(&request, effect->hitGroup);
            SpawnSoundSlot_0204da8c(0xf4, 0x1a, &info.position, 0);
            effect->targetId = hitId;
            effect->hasTarget = 1;
            effect->releaseReady = 1;
        }
    }
}
