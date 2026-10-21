#include "nitro/types.h"
#include "nitro/fx_types.h"
#pragma scheduling off

typedef struct Box {
    fx32 minX, minY, minZ;
    fx32 maxX, maxY, maxZ;
} Box;

typedef struct ObbShape {
    u8 pad_00[0x18];
    VecFx32 axes[3];
} ObbShape;

typedef struct RoundShape {
    u8 pad_00[0x28];
    fx32 radius;
} RoundShape;

typedef struct StepShape {
    u32 pad_00;
    fx32 surfaceY;
} StepShape;

typedef struct CollObject {
    u8 pad_00[0x18];
    VecFx32 position;
    void *shape;
    u8 pad_28[0x18];
    s32 shapeType;
    u8 pad_44[0x28];
    s32 kind;
} CollObject;

typedef struct ContactEntry {
    CollObject *object;
    s32 type;
    u8 flags;
} ContactEntry;

typedef struct ContactSet {
    ContactEntry entries[16];
    VecFx32 normals[16];
    u8 entryCount;
    u8 order[32];
    u8 orderCount;
} ContactSet;

typedef struct MoverShape {
    u32 pad_00;
    Box box;
    u32 pad_1C;
    VecFx32 delta;
    Box sweptBox;
} MoverShape;

typedef struct Mover {
    u8 pad_00[0x24];
    MoverShape *shape;
    ContactSet *contacts;
} Mover;

typedef struct Hit {
    u8 pad_00[0x2c];
    VecFx32 normal;
    VecFx32 point;
    ContactSet *contacts;
} Hit;

typedef struct ResolveOptions {
    u8 pad_00[0x34];
    s32 stepUp;
} ResolveOptions;

extern s32 func_ov001_02063a38(void);
extern s32 func_ov042_020bd16c(void);
extern void func_02034d64(VecFx32 *vec, ContactSet *set);
extern Hit *func_020351cc(void *world, Mover *mover);
extern void func_02032008(ContactSet *set, CollObject *object, s32 type, s32 flags, const VecFx32 *normal);
extern void func_0203afa0(MoverShape *shape, const VecFx32 *pos);
extern fx32 func_0203d4d0(ObbShape *shape, const VecFx32 *axis);
extern void func_0204a5e4(VecFx32 *vec, fx32 scale);
extern BOOL func_0204a8f4(const VecFx32 *a, const VecFx32 *b);
extern void func_0204aa68(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);
extern void func_0204ad4c(VecFx32 *out, const VecFx32 *v);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void func_01ff8830(void *dst, int value, u32 size);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern const VecFx32 data_02053438;
extern s32 data_02060848;

static inline BOOL IsMode4(void)
{
    return func_ov001_02063a38() == 4;
}

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Subtract_01ff9e3c(a, b, &result);
    return result;
}

static inline VecFx32 VecScale(const VecFx32 *v, fx32 scale)
{
    VecFx32 result = *v;
    func_0204a5e4(&result, scale);
    return result;
}

static inline VecFx32 VecSubScaled(const VecFx32 *v, const VecFx32 *axis, fx32 scale)
{
    VecFx32 offset;
    VecFx32 scaled;
    VecFx32 result;

    scaled = *axis;
    func_0204a5e4(&scaled, scale);
    offset = scaled;
    VEC_Subtract_01ff9e3c(v, &offset, &result);
    return result;
}

static inline VecFx32 VecNormalized(const VecFx32 *v)
{
    VecFx32 result;
    func_01ff9f88(v, &result);
    return result;
}

static inline VecFx32 PerpNormalized(const VecFx32 *v)
{
    VecFx32 perp;
    VecFx32 result;
    func_0204ad4c(&perp, v);
    func_01ff9f88(&perp, &result);
    return result;
}

static inline VecFx32 VecCross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    func_0204aa68(&result, a, b);
    return result;
}

static inline VecFx32 SignedVec(const VecFx32 *v, s8 sign)
{
    VecFx32 result = *v;
    if (sign < 0) {
        NegateVecFx32_0204aa40(&result);
    }
    return result;
}

static inline VecFx32 OffsetPos(const VecFx32 *pos, fx32 offset)
{
    VecFx32 result;
    result.x = pos->x;
    result.y = pos->y + offset;
    result.z = pos->z;
    return result;
}

static inline void SetMoverShapeDelta(MoverShape *shape, const VecFx32 *delta)
{
    shape->delta = *delta;
    OffsetBoxByDelta_0203ac70(&shape->box, &shape->sweptBox, &shape->delta);
}

static inline int Sign(fx32 value)
{
    if (value == 0) {
        return 0;
    }
    return value > 0 ? 1 : -1;
}

void ResolveContactPushOut_020382b0(void *world, s32 unused, Mover *mover, Hit *hit, VecFx32 *pos, VecFx32 *out,
                   volatile fx32 heightOffset, u32 flags, ResolveOptions *options)
{
    ContactSet localSet;
    VecFx32 rel;
    VecFx32 planar;
    VecFx32 dir;
    VecFx32 push;
    VecFx32 result;
    VecFx32 axisVec;
    VecFx32 bestAxisVec;
    VecFx32 otherNormal;
    u8 history[4];
    u8 count;
    u8 j;
    CollObject *object;
    const VecFx32 *normal;
    fx32 dist;
    BOOL checkGround;
    ObbShape *shape;
    fx32 bestScore;
    s8 bestSign;
    u8 bestAxis;
    u8 otherIdx;
    ContactEntry *entry;
    ContactSet *set;
    u8 otherCount;
    u8 iter;
    Hit *other;
    ContactEntry *candidate;
    u8 i;
    u8 n;
    u8 idx;
    int contactIdx;
    u8 *order;

    set = hit->contacts;
    count = set->orderCount;
    if (IsMode4() && func_ov042_020bd16c() == 1) {
        for (i = 0; i < count; i++) {
            candidate = &set->entries[set->order[i]];
            if (candidate->type == 4 && (u32)(candidate->object->kind - 3) <= 1) {
                out->x = 0;
                out->z = 0;
                return;
            }
        }
        for (i = 0; i < count; i++) {
            candidate = &set->entries[set->order[i]];
            if (set->normals[set->order[i]].y <= 0 && candidate->type == 4 &&
                (candidate->object->kind == 8 || (u32)(candidate->object->kind - 0x1b) <= 1)) {
                func_02034d64(out, set);
                if (options->stepUp == 0) {
                    return;
                }
                out->y = ((StepShape *)candidate->object->shape)->surfaceY + 0x1800 - pos->y;
                return;
            }
        }
    }

    if (count >= 4) {
        *out = data_02053438;
        return;
    }

    for (i = 0; i < 2; i++) {
        for (n = 0; n < count; n++) {
            idx = set->order[n];
            if (idx < set->entryCount && set->entries[idx].type == 4 &&
                (i == 1 || (set->entries[idx].flags & 3))) {
                goto found;
            }
        }
    }
found:
    if (n == count) {
        if (data_02060848 == 0) {
            return;
        }
        func_02034d64(out, set);
        return;
    }

    order = set->order;
    order += n;
    idx = *order;
    object = set->entries[idx].object;
    rel = VecSub(pos, &object->position);
    normal = &set->normals[idx];
    planar = VecSubScaled(&rel, normal, VEC_DotProduct_01ff9e6c(&rel, normal));
    dir = func_0204a8f4(&planar, &data_02053438) ? PerpNormalized(normal) : VecNormalized(&planar);

    contactIdx = idx;
    checkGround = FALSE;
    mover->contacts = &localSet;
    func_02034d64(out, set);
    if (object->shapeType != 1) {
        checkGround = TRUE;
    } else {
        VEC_Add_01ff9e0c(pos, out, pos);
        if (object->shapeType == 1) {
            func_01ff8830(history, 0, 4);
        }
        iter = 0;
        entry = &set->entries[contactIdx];
        for (; iter < 6; iter++) {
            localSet.entryCount = 0;
            localSet.orderCount = 0;
            switch (object->shapeType) {
            case 1: {
                u8 axis;

                shape = object->shape;
                bestScore = 0x80000000;
                if (entry->flags & 3) {
                    checkGround = TRUE;
                    goto groundCheck;
                }
                for (axis = 0; axis < 3; axis++) {
                    axisVec = VecSubScaled(&shape->axes[axis], (const VecFx32 *)&entry[16],
                        VEC_DotProduct_01ff9e6c(&shape->axes[axis], &set->normals[contactIdx]));
                    if (func_01ffaff4(&axisVec, &axisVec) != 0) {
                        fx32 facing = VEC_DotProduct_01ff9e6c(&axisVec, &planar);
                        u8 k;
                        s8 sign;
                        u8 repeats = 0;

                        sign = Sign(facing);
                        facing = facing * sign;
                        for (k = 0; k < iter; k++) {
                            u8 entryBits = history[k];
                            if (axis == (entryBits & 3) &&
                                (sign == -1) == ((entryBits & 4) ? 1 : 0)) {
                                repeats++;
                                if (repeats == 2) {
                                    break;
                                }
                                facing = -facing;
                                sign = -sign;
                            }
                        }
                        if (repeats != 2) {
                            fx32 extent = func_0203d4d0(shape, &axisVec);
                            fx32 score = facing - extent;
                            if (bestScore < score) {
                                bestSign = sign;
                                bestAxis = axis;
                                bestScore = score;
                                bestAxisVec = axisVec;
                                dist = extent;
                            }
                        }
                    }
                }
                dir = SignedVec(&bestAxisVec, bestSign);
                dist -= VEC_DotProduct_01ff9e6c(&dir, &rel);
                history[iter] = bestAxis;
                history[iter] |= (u8)((bestSign == -1) << 2);
                func_02032008(&localSet, object, 4, 0, &dir);
                break;
            }
            case 0:
            case 3:
            case 4:
                if (entry->flags & 3) {
                    dist = 0x80;
                } else {
                    dist = ((RoundShape *)object->shape)->radius - VEC_Mag_01ff9f28(&planar);
                }
                break;
            case 5:
                dist = 0x80;
                break;
            }

            push = VecScale(&dir, dist);
            {
                VecFx32 shapePos = OffsetPos(pos, heightOffset);
                func_0203afa0(mover->shape, &shapePos);
            }
            SetMoverShapeDelta(mover->shape, &push);
            other = func_020351cc(world, mover);
            if (other == NULL) {
                result = push;
                break;
            }
            otherCount = other->contacts->orderCount;
            if (otherCount != 0) {
                if (otherCount >= 4) {
                    continue;
                }
                for (j = 0; j < otherCount; j++) {
                    u8 k;
                    otherIdx = other->contacts->order[j];
                    for (k = 0; k < count; k++) {
                        if (func_0204a8f4(&other->contacts->normals[otherIdx], &set->normals[set->order[k]])) {
                            break;
                        }
                    }
                    if (k == count) {
                        fx32 along = VEC_DotProduct_01ff9e6c(&other->contacts->normals[otherIdx], &dir);
                        if (along < 0) {
                            along = -along;
                        }
                        if (along >= 0x10 || along <= -0x10) {
                            dir = VecCross(normal, &dir);
                            break;
                        }
                    }
                }
                if (j < count) {
                    continue;
                }
            }
            otherNormal = other->normal;
            if (VEC_DotProduct_01ff9e6c(&otherNormal, &dir) > (dist -= 0x10)) {
                result = VecSubScaled(&otherNormal, normal, VEC_DotProduct_01ff9e6c(&otherNormal, normal));
                break;
            }
            if (func_0204a8f4(&otherNormal, &data_02053438)) {
                dir = VecCross(normal, &dir);
            } else {
                dir = otherNormal;
            }
            dist = func_01ffaff4(&dir, &dir);
        }

        if (iter < 6) {
            localSet.entryCount = 0;
            localSet.orderCount = 0;
            {
                VecFx32 shapePos = OffsetPos(pos, heightOffset);
                func_0203afa0(mover->shape, &shapePos);
            }
            SetMoverShapeDelta(mover->shape, &result);
            other = func_020351cc(world, mover);
            if (other != NULL) {
                result = VecSub(&other->point, pos);
                result.y -= heightOffset;
                func_02034d64(&result, other->contacts);
            }
            *out = result;
            if ((flags & 4) && out->y < 0) {
                out->y = 0;
            }
            if (out->x == 0 && out->y == 0 && out->z == 0) {
                checkGround = TRUE;
            }
        } else {
            *out = data_02053438;
            checkGround = TRUE;
        }
    }

groundCheck:
    if (checkGround) {
        for (i = 0; i < count; i++) {
            candidate = &set->entries[set->order[i]];
            if (set->normals[set->order[i]].y <= 0 && candidate->type == 4 && candidate->object->kind == 0xc) {
                pos->y += ((StepShape *)candidate->object->shape)->surfaceY + 0x1800 - pos->y;
                return;
            }
        }
    }
}
