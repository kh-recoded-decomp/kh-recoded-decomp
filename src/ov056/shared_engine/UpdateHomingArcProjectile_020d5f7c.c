#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct {
    Sphere *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct {
    void (*func)(void);
    void *arg;
} QueryCallback;

typedef struct {
    u32 words[0x12];
    QueryCallback filter;
    QueryCallback callback;
    u32 tail[2];
} CollisionQuery;

typedef struct {
    u8 pad_000[0x14];
    u8 *info;
    u8 pad_018[0x6c - 0x18];
    s32 kind;
} ContactTarget;

typedef struct {
    u32 flags;
    s32 wall;
    s32 floor;
    u8 pad_0c[4];
    ContactTarget *target;
    u8 pad_14[0xb8 - 0x14];
} Contact;

typedef struct {
    u32 flags;
    s32 side;
    s32 strength;
    VecFx32 center;
    u8 pad_18[4];
    Contact contact;
} HitResult;

typedef struct {
    HitResult result;
    u32 active;
    u32 pad_d8;
} HitScan;

typedef struct {
    fx32 w;
    fx32 x;
    fx32 y;
    fx32 z;
} HalfQuat;

typedef struct {
    u32 flags;
    u8 pad_04[4];
    s16 turnRate;
    u8 pad_0a[2];
    fx32 radius;
    u8 pad_10[4];
    fx32 speed;
    fx32 maxDistance;
    s32 lifetime;
    u8 pad_20[8];
    s32 homingDelay;
} ArcDef;

typedef struct {
    fx32 timers[8];
} ArcParams;

typedef struct {
    u8 pad_000[2];
    s8 status;
    u8 pad_003;
    fx32 age;
    u8 pad_008[0x18 - 0x8];
    VecFx32 start;
    VecFx32 velocity;
    u8 pad_030[0xd4 - 0x30];
    VecFx32 position;
    u8 pad_0e0[0x138 - 0xe0];
    ArcDef *def;
    u8 pad_13c[2];
    s16 hitIds[8];
    u8 pad_14e[2];
    ArcParams *params;
} ArcUnit;

typedef struct ArcOwner ArcOwner;
typedef void (*ArcHitCallback)(ArcOwner *owner, ArcUnit *unit, HitScan *scan);

struct ArcOwner {
    u32 entryIndex;
    u8 pad_04[0x30];
    ArcHitCallback onHit;
    ArcHitCallback onScan;
    u8 pad_3c[0x190 - 0x3c];
    fx32 hitCooldown;
};

typedef struct ArcEntry ArcEntry;
struct ArcEntry {
    u8 pad_000[0x228];
    BOOL (*getTarget)(ArcEntry *entry, VecFx32 *out);
};

extern s16 data_0205356c[];
extern const VecFx32 data_ov056_020d7f64;

extern ArcEntry *GetBoundedEntryField_0206db5c(int index);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *axb);
extern void VEC_Normalize_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern int FixedPointMultiply12(int left, int right);
extern u16 Math_AcosIdx_0202ab20(int cosine);
extern void func_0202fba8(VecFx32 *in, HalfQuat *rotation, VecFx32 *out);
extern CollisionShape func_0203ad14(Sphere *storage, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void *func_02036240(u16 actorId);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern Contact *SweepWorldCollision_020364a0(CollisionQuery *query);
extern VecFx32 GetShapeCenter_0203b43c(const CollisionShape *shape);
extern void ZeroAndSetField0xd4_020ac150(HitScan *scan);
extern void func_ov021_020ac148(HitResult *result);
extern HitResult FindStrongestHit_020ab0c8(ArcOwner *owner, ArcUnit *unit, VecFx32 *position, VecFx32 *move);
extern int AdvanceOwnerAnimation_020ab41c(ArcUnit *unit, fx32 step);
extern void AdvanceToSecondPhase_020ab5f0(ArcUnit *unit);
extern void func_ov056_020d5f50(void);
extern void func_ov021_020a9230(void);

BOOL UpdateHomingArcProjectile_020d5f7c(ArcOwner *owner, ArcUnit *unit, fx32 step)
{
    CollisionQuery sweep;
    QueryWorkspace workspace;
    SweptShape sweptCopy;
    HitScan hit;
    HitResult strongest;
    SweptShape landSwept;
    CollisionQuery landQuery;
    SweptShape hitSwept;
    CollisionQuery hitQuery;
    VecFx32 pos;
    VecFx32 dir;
    VecFx32 toTarget;
    VecFx32 axis;
    VecFx32 gravity;
    VecFx32 move;
    HalfQuat turn;
    Sphere sphere;
    VecFx32 landPos;
    VecFx32 landCenter;
    QueryCallback filterCallback;
    QueryCallback contactCallback;
    ArcDef *def = unit->def;
    ArcEntry *entry;
    Contact *contact;
    BOOL found;
    BOOL done;
    int animDone;
    fx32 radius;
    fx32 maxAngle;
    fx32 dot;
    int angle;
    int index;
    fx32 sinHalf;
    int kind;
    int i;

    unit->age += step;
    for (i = 0; i < 8; i++) {
        if (unit->hitIds[i] != -1) {
            ArcParams *params = unit->params;

            params->timers[i] += step;
            if (params->timers[i] >= owner->hitCooldown) {
                unit->hitIds[i] = -1;
                params->timers[i] = 0;
            }
        }
    }
    pos = unit->position;
    entry = GetBoundedEntryField_0206db5c(owner->entryIndex);
    if (entry->getTarget != NULL) {
        found = entry->getTarget(entry, &toTarget);
    } else {
        found = FALSE;
    }
    if (found && unit->age >= def->homingDelay && def->turnRate > 0 && !(def->flags & 0x100)) {
        VEC_Subtract_01ff9e3c(&toTarget, &pos, &toTarget);
        toTarget.y = 0;
        radius = def->radius;
        if (VEC_DotProduct_01ff9e6c(&toTarget, &toTarget) > FixedPointMultiply12(radius, radius)) {
            maxAngle = FixedPointMultiply12(0x8000, def->turnRate);
            VEC_Normalize_01ff9f88(&toTarget, &toTarget);
            VEC_Normalize_01ff9f88(&unit->velocity, &dir);
            VEC_CrossProduct_01ff9ea8(&dir, &toTarget, &axis);
            dot = VEC_DotProduct_01ff9e6c(&dir, &toTarget);
            if (dot < -0x1000) {
                dot = -0x1000;
            } else if (dot >= 0x1000) {
                dot = 0x1000;
            }
            angle = Math_AcosIdx_0202ab20(dot);
            if (angle > maxAngle) {
                angle = maxAngle;
            }
            index = angle >> 5;
            sinHalf = data_0205356c[index];
            turn.x = FixedPointMultiply12(axis.x, sinHalf);
            turn.y = FixedPointMultiply12(axis.y, sinHalf);
            turn.z = FixedPointMultiply12(axis.z, sinHalf);
            turn.w = data_0205356c[(0x400 - index) & 0xfff];
            func_0202fba8(&dir, &turn, &dir);
            ScaleVecFx32_01ffafb4(def->speed, &dir, &dir);
            unit->velocity.x = dir.x;
            unit->velocity.z = dir.z;
        }
    }
    ScaleVecFx32_01ffafb4(FixedPointMultiply12(-0x2d, step), &data_ov056_020d7f64, &gravity);
    VEC_MultAdd_01ffa09c(step, &unit->velocity, &gravity, &move);
    VEC_Add_01ff9e0c(&unit->velocity, &gravity, &unit->velocity);

    landSwept.shape = func_0203ad14(&sphere, &pos, def->radius);
    landSwept.delta = move;
    OffsetBoxByDelta_0203ac70(&landSwept.shape.bounds, &landSwept.sweptBounds, &landSwept.delta);
    sweptCopy = landSwept;
    CollisionQuery_Init_02034c74(&landQuery, 0, func_02036240(owner->entryIndex), 1, 0, 1, &sweptCopy, &workspace, NULL);
    sweep = landQuery;
    if (SweepWorldCollision_020364a0(&sweep) != NULL) {
        landCenter = GetShapeCenter_0203b43c(&sweptCopy.shape);
        landPos = landCenter;
        move.y = 0;
        unit->velocity.y = 0;
        VEC_Subtract_01ff9e3c(&landPos, &pos, &dir);
        if (dir.y > 0) {
            pos.y = landPos.y;
        }
        VEC_Subtract_01ff9e3c(&pos, &gravity, &pos);
    }

    hitSwept.shape = func_0203ad14(&sphere, &pos, def->radius);
    hitSwept.delta = move;
    OffsetBoxByDelta_0203ac70(&hitSwept.shape.bounds, &hitSwept.sweptBounds, &hitSwept.delta);
    sweptCopy = hitSwept;
    CollisionQuery_Init_02034c74(&hitQuery, 0, func_02036240(owner->entryIndex), 0xb, 1, 1, &sweptCopy, &workspace, NULL);
    sweep = hitQuery;
    kind = 0;
    filterCallback.func = func_ov056_020d5f50;
    filterCallback.arg = NULL;
    sweep.filter = filterCallback;
    contactCallback.func = func_ov021_020a9230;
    contactCallback.arg = NULL;
    sweep.callback = contactCallback;
    contact = SweepWorldCollision_020364a0(&sweep);
    if (contact != NULL) {
        ContactTarget *target = contact->target;

        if (target != NULL && target->info[0x194] == 1 && (u32)(target->kind - 0x19) <= 1) {
            kind = 4;
        }
        if (contact->wall != 0) {
            kind = 2;
        }
        if (contact->floor != 0) {
            kind = 1;
        }
        if (kind != 0) {
            ZeroAndSetField0xd4_020ac150(&hit);
            func_ov021_020ac148(&hit.result);
            hit.result.strength = 1;
            hit.result.side = kind;
            hit.result.center = GetShapeCenter_0203b43c(&sweptCopy.shape);
            hit.result.contact = *contact;
            if (owner->onScan != NULL) {
                owner->onScan(owner, unit, &hit);
            }
            if (owner->onHit != NULL) {
                owner->onHit(owner, unit, &hit);
            }
            AdvanceToSecondPhase_020ab5f0(unit);
        }
    }
    strongest = FindStrongestHit_020ab0c8(owner, unit, &pos, &move);
    VEC_Add_01ff9e0c(&pos, &move, &pos);
    unit->position = pos;
    if (unit->status == 1) {
        done = FALSE;
        animDone = AdvanceOwnerAnimation_020ab41c(unit, step);
        if (def->lifetime >= 0) {
            if (unit->age >= def->lifetime) {
                done = TRUE;
            }
        } else if (animDone != 0) {
            done = TRUE;
        }
        if (def->maxDistance >= 0 && func_01ffa0f4(&unit->start, &pos) > def->maxDistance) {
            done = TRUE;
        }
        if (done) {
            AdvanceToSecondPhase_020ab5f0(unit);
        }
    }
    if (unit->status == -1) {
        return TRUE;
    }
    return FALSE;
}
