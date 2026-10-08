#include "nitro/types.h"
#include "nitro/fx_types.h"

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

typedef struct HitRequest {
    HitQuery query;
    u32 unk_44;
    VecFx32 velocity;
    fx32 scale;
    u8 pad_58[0x60 - 0x58];
} HitRequest;

typedef struct HitScan {
    u32 unk_00;
    int hitKind;
    int hitType;
    u8 pad_0c[0xdc - 0xc];
} HitScan;

typedef struct AnimInfo {
    u16 unk_00;
    u16 frameCount;
    u16 duration;
} AnimInfo;

typedef struct AnimBlendSet {
    u8 selector[0xd8];
    u8 blendTable[0x104 - 0xd8];
} AnimBlendSet;

typedef struct AnimBank {
    AnimBlendSet sets[3];
} AnimBank;

typedef struct ActorEvent {
    int type;
    u8 pad_04[0x1c - 0x4];
    fx32 frame;
    void *actor;
    u8 pad_24[0x38 - 0x24];
} ActorEvent;

typedef struct StageProgress {
    fx32 timer;
    int step;
    u8 flags;
    fx32 frameRemainder;
} StageProgress;

typedef struct Actor Actor;
typedef int (*ActorGetMode)(Actor *actor);
typedef void (*ActorFinishFunc)(Actor *actor, int arg);
typedef void (*ActorEventFunc)(Actor *actor, ActorEvent *event);
typedef void (*ActorAngleFunc)(Actor *actor, u16 angle);
typedef void (*ActorStateFunc)(Actor *actor, int state);

struct Actor {
    u8 pad_0000[0x1d4];
    AnimInfo *anim;
    u8 pad_01d8[0x1dc - 0x1d8];
    int mode;
    u8 pad_01e0[0x200 - 0x1e0];
    ActorFinishFunc onFinish;
    u8 pad_0204[0x208 - 0x204];
    ActorEventFunc onEvent;
    u8 pad_020c[0x210 - 0x20c];
    ActorAngleFunc onAngle;
    u8 pad_0214[0x22c - 0x214];
    ActorGetMode getMode;
    u8 pad_0230[0x234 - 0x230];
    u32 flags;
    u8 pad_0238[0x930 - 0x238];
    u8 playerIndex;
    u8 pad_0931[0x944 - 0x931];
    int state;
    u8 pad_0948[0x964 - 0x948];
    VecFx32 position;
    u8 pad_0970[0x1700 - 0x970];
    AnimBank *animBank;
    u8 pad_1704[0x1808 - 0x1704];
    ActorStateFunc setState;
};

extern s16 data_02053580[];

extern void MI_CpuFill8(void *dst, int value, int size);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void ScaleVecFx32(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_NormalizeLength(const VecFx32 *source, VecFx32 *destination);
extern u16 AdvanceAnimationTracks(void *state, fx32 delta);
extern void selectJointAnimationBlend(void *selector, u16 trackIndex, void *blendTable, s16 blendIndex);
extern void OffsetBoxByDelta(const void *src, Box *dst, const VecFx32 *delta);
extern void InitCylinderShape(CollisionShape *shape, CollisionCylinder *cylinder, const VecFx32 *start,
                                       const VecFx32 *end, const VecFx32 *direction, fx32 length, fx32 radius);
extern void ConfigureChannelSlot(int kind, int value, int index);
extern u32 RemapIndex(u32 value);
extern void InitRecord60(HitRequest *record);
extern void ZeroAndSetField0xd4(HitScan *scan);
extern BOOL StepHitScan(int type, HitRequest *request, void *options, HitScan *scan);
extern u16 GetLinkedAngleOffset_020cd104(Actor *actor);

static inline VecFx32 Vec_Difference(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;

    VEC_Subtract(a, b, &result);
    return result;
}

static inline CollisionShape MakeCylinderShape(CollisionCylinder *cylinder, const VecFx32 *start, const VecFx32 *end,
                                               const VecFx32 *direction, fx32 length)
{
    CollisionShape shape;

    InitCylinderShape(&shape, cylinder, start, end, direction, length, 0xc33);
    return shape;
}

void Actor_UpdateComboStage(Actor *actor, StageProgress *progress, fx32 delta)
{
    HitScan scan;
    HitRequest request;
    HitQuery query;
    ActorEvent event;
    CollisionCylinder cylinder;
    VecFx32 start;
    VecFx32 end;
    VecFx32 offset;
    ActorEvent hitEvent;
    VecFx32 direction;
    int angle;
    HitScan *result;
    int mode;
    BOOL done;
    fx32 threshold;
    int i;

    if (actor->getMode != NULL) {
        mode = actor->getMode(actor);
    } else {
        mode = actor->mode;
    }
    done = FALSE;
    threshold = 0x7fffffff;
    if (mode == 0) {
        return;
    }
    progress->timer += delta;
    switch (mode) {
    case 1: {
        fx32 frame;

        progress->flags |= 1;
        if (progress->timer >= 0x1e000) {
            frame = (actor->anim->duration << 12) / 100 + progress->frameRemainder;
            MI_CpuFill8(&event, 0, sizeof(ActorEvent));
            event.type = 0x3a;
            event.frame = frame;
            event.actor = actor;
            if ((frame >> 12) >= actor->anim->frameCount) {
                event.frame = (actor->anim->frameCount - 1) << 12;
            }
            if (actor->onEvent != NULL) {
                actor->onEvent(actor, &event);
            }
            progress->frameRemainder = frame & 0xfff;
            progress->timer = 0;
            progress->step++;
        }
        AdvanceAnimationTracks(actor->animBank, delta);
        if (actor->anim->frameCount <= 1) {
            goto finish;
        }
        if (progress->step < 0x12) {
            break;
        }
        goto finish;
    }
    case 2:
        progress->flags |= 2;
        if (actor->state != 0x12 && progress->timer >= 0x5000) {
            actor->setState(actor, 0x12);
        }
        AdvanceAnimationTracks(&actor->animBank->sets[1], delta);
        threshold = 0x5a000 - (progress->step << 13);
        break;
    case 3:
        switch (progress->step) {
        case 0: {
            BOOL hit = FALSE;

            progress->flags |= 4;
            AdvanceAnimationTracks(&actor->animBank->sets[2], delta);
            if (progress->flags & 0x20) {
                hit = TRUE;
            }
            if (progress->timer >= 0x1c2000) {
                hit = TRUE;
            }
            if (progress->timer >= 0x1e000) {
                progress->flags |= 0x10;
            }
            if (!hit && (progress->flags & 0x10)) {
                request.velocity.z = 0;
                request.velocity.y = 0;
                request.velocity.x = 0;
                angle = GetLinkedAngleOffset_020cd104(actor) >> 4;
                request.velocity.x = -data_02053580[angle];
                request.velocity.z = -data_02053580[(0x400 - angle) & 0xfff];
                ScaleVecFx32(0x333, &request.velocity, &request.velocity);
                InitRecord60(&request);
                start = actor->position;
                end = start;
                end.y += 0x333;
                offset.x = 0;
                offset.y = 0x8cd;
                offset.z = 0;
                direction = Vec_Difference(&end, &start);
                query.shape = MakeCylinderShape(&cylinder, &start, &end, &direction,
                                                VEC_NormalizeLength(&direction, &direction));
                query.delta = offset;
                OffsetBoxByDelta(query.shape.bounds, &query.sweptBounds, &query.delta);
                request.query = query;
                result = &scan;
                ZeroAndSetField0xd4(result);
                while (StepHitScan(actor->playerIndex, &request, NULL, result)) {
                    if (result->hitType != 0) {
                        if (result->hitType == 1) {
                            if (result->hitKind != 2) {
                                hit = TRUE;
                            }
                        } else {
                            hit = TRUE;
                        }
                    }
                    if (hit) {
                        break;
                    }
                }
            }
            if (hit) {
                MI_CpuFill8(&hitEvent, 0, sizeof(ActorEvent));
                hitEvent.type = 0x62;
                hitEvent.frame = actor->anim->duration << 9;
                hitEvent.actor = actor;
                if ((hitEvent.frame >> 12) >= actor->anim->frameCount) {
                    hitEvent.frame = (actor->anim->frameCount - 1) << 12;
                }
                if (actor->onEvent != NULL) {
                    actor->onEvent(actor, &hitEvent);
                }
                for (i = 0; i < 5; i++) {
                    selectJointAnimationBlend(actor->animBank->sets[2].selector, i,
                                                       (u8 *)&actor->animBank->sets[2] + 0xd8, 1);
                }
                progress->step = 1;
            }
            break;
        }
        case 1:
            if (AdvanceAnimationTracks(&actor->animBank->sets[2], delta) != 0) {
                done = TRUE;
            } else {
                progress->flags |= 4;
            }
            break;
        }
        break;
    case 7:
        threshold = 0x96000;
        break;
    case 6:
        threshold = 0x10e000;
        break;
    case 11:
        threshold = 0x12c000;
        break;
    case 8:
        threshold = 0x258000;
        break;
    case 9:
        threshold = 0x258000;
        break;
    case 10:
        threshold = 0x258000;
        break;
    case 4: {
        u16 angle = GetLinkedAngleOffset_020cd104(actor) + 0x1555;

        if (actor->onAngle != NULL) {
            actor->onAngle(actor, angle);
        }
        threshold = 0xb4000;
        if (progress->timer < 0x3000 || !(actor->flags & 4)) {
            break;
        }
    finish:
        done = TRUE;
        break;
    }
    }
    if (threshold != 0x7fffffff && threshold <= progress->timer) {
        done = TRUE;
    }
    if (done) {
        if (actor->onFinish != NULL) {
            actor->onFinish(actor, 0);
        }
    } else {
        u32 channel = RemapIndex(mode);
        if (channel != 0) {
            ConfigureChannelSlot(1, channel, actor->playerIndex);
        }
    }
}
