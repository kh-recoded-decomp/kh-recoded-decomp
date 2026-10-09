#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 *position;
    Box bounds;
    s32 kind;
    VecFx32 delta;
    Box sweptBounds;
} CollisionShape;

typedef struct {
    u8 _0[0xc];
    u8 flags;
    u8 _d[0x17];
    CollisionShape shape;
    u8 _68[0x20];
} CameraCollider;

typedef struct {
    u8 _0[0x14];
    VecFx32 eye;
    VecFx32 target;
    u8 _2c[0xc];
    u32 flags;
    u8 _3c[4];
    int mode;
    u8 _44[4];
    int locked;
    u8 _4c[0xc];
    fx32 rangeX;
    fx32 rangeY;
    u8 _60[4];
    VecFx32 baseTarget;
    VecFx32 baseEye;
    VecFx32 shake;
    VecFx32 lookAt;
    VecFx32 focus;
    VecFx32 anchor;
    VecFx32 recenterGoal;
    int recenterTimer;
    fx32 minY;
    fx32 maxY;
    fx32 minX;
    fx32 maxX;
    fx32 slideEnd;
    fx32 slideStart;
    int slideTimer;
    u8 _d8[0x44];
    VecFx32 railPoint;
    VecFx32 colliderOffset;
    VecFx32 lastPlayerPos;
    u32 followFlags;
    u8 _144[4];
    int particle;
    u8 _14c[0xc];
    VecFx32 particleShake;
    u8 _164[0x2a8];
    CameraCollider colliders[3];
} CameraState;

typedef struct {
    u8 _0[0x21c];
    u32 (*getInputFlags)(void *entry);
} InputEntry;

typedef struct {
    u8 _0[4];
    int **tree;
} CollisionWorld;

extern CameraState *data_ov042_020be5e0;
extern VecFx32 data_0205344c;
extern int func_ov001_02063a4c(void);
extern VecFx32 *func_ov001_0206dc4c(int index);
extern InputEntry *GetBoundedEntryField(int index);
extern VecFx32 *func_ov030_020bb374(void);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern int FX_Mul(int left, int right);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern fx32 EaseProgress(fx32 elapsed, fx32 duration, int mode);
extern void LerpVecFx32Q27InPlace(VecFx32 *current, const VecFx32 *target, s32 t);
extern void SetShapePosition(CollisionShape *shape, const VecFx32 *position);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern CollisionWorld *GetActorRegistry(void);
extern void QuadTree_ReinsertNodeIfFlagSet(int *tree, int node);
extern void QuadTree_RemoveObject(int *tree, int node);
extern int UpdateDriftParticle(int *particle);
extern void TranslateCameraTarget(const VecFx32 *offset);
extern void TranslateCameraGoal(const VecFx32 *offset);
extern BOOL StepCameraGoalTowardTarget(void);

static inline VecFx32 SubtractVec(const VecFx32 *a, const VecFx32 *b) {
    VecFx32 out;
    VEC_Subtract(a, b, &out);
    return out;
}

static inline VecFx32 AddVec(const VecFx32 *a, const VecFx32 *b) {
    VecFx32 out;
    VEC_Add(a, b, &out);
    return out;
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z) {
    VecFx32 out;
    out.x = x;
    out.y = y;
    out.z = z;
    return out;
}

static inline VecFx32 RejectFromAxis(const VecFx32 *point, const VecFx32 *axis) {
    VecFx32 projected;
    VecFx32 scaled;
    VecFx32 out;
    fx32 dot = VEC_DotProduct(point, axis);
    scaled = *axis;
    ScaleVecFx32InPlace(&scaled, dot);
    projected = scaled;
    VEC_Subtract(point, &projected, &out);
    return out;
}

static inline VecFx32 LerpVec(const VecFx32 *from, const VecFx32 *to, s32 t) {
    VecFx32 out = *from;
    LerpVecFx32Q27InPlace(&out, to, t);
    return out;
}

static inline fx32 ClampFx(fx32 low, fx32 high, fx32 value) {
    if (value < low) {
        value = low;
    }
    if (value > high) {
        value = high;
    }
    return value;
}

static inline fx32 MulFx(fx32 a, fx32 b) {
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

static inline BOOL VecEquals(const VecFx32 *a, const VecFx32 *b) {
    return a->x == b->x && a->y == b->y && a->z == b->z;
}

static inline void MoveShape(CollisionShape *shape) {
    VecFx32 position;
    VecFx32 sum;
    VEC_Add(shape->position, &data_ov042_020be5e0->colliderOffset, &sum);
    position = sum;
    SetShapePosition(shape, &position);
    OffsetBoxByDelta(&shape->bounds, &shape->sweptBounds, &shape->delta);
}

static inline void ApplyCameraShake(void) {
    CameraState *cam = data_ov042_020be5e0;
    VecFx32 targetSum;
    VecFx32 eyeSum;
    VEC_Add(&cam->baseTarget, &cam->shake, &targetSum);
    cam->target = targetSum;
    VEC_Add(&data_ov042_020be5e0->baseEye, &data_ov042_020be5e0->shake, &eyeSum);
    cam->eye = eyeSum;
}

BOOL UpdateCameraScene(void) {
    CameraState *cam = data_ov042_020be5e0;
    VecFx32 move;
    VecFx32 delta;
    VecFx32 goal;
    VecFx32 offset;
    VecFx32 start;
    VecFx32 end;

    if (func_ov001_02063a4c() != 4 && func_ov001_02063a4c() != 7 && func_ov001_02063a4c() != 8) {
        return FALSE;
    }
    if (cam->locked == 0) {
        switch (cam->mode) {
        case 0:
            move = SubtractVec(func_ov001_0206dc4c(0), &cam->focus);
            move.y = 0;
            TranslateCameraTarget(&move);
            break;
        case 1: {
            VecFx32 *dir = func_ov030_020bb374();
            CollisionWorld *world;
            if (cam->slideTimer != -1) {
                fx32 base = cam->baseEye.x;
                fx32 x;
                cam->slideTimer += 0x1000;
                if (cam->slideTimer >= 0x14000) {
                    cam->slideTimer = -1;
                    x = cam->slideEnd;
                } else {
                    fx32 t = EaseProgress(cam->slideTimer, 0x14000, 1);
                    x = MulFx(cam->slideStart, 0x1000 - t) + MulFx(cam->slideEnd, t);
                }
                delta.x = x - base;
                delta.y = 0;
                delta.z = 0;
                TranslateCameraTarget(&delta);
                TranslateCameraGoal(&delta);
            } else {
                u32 input;
                InputEntry *entry;
                VecFx32 *player;
                delta = RejectFromAxis(&cam->railPoint, dir);
                TranslateCameraTarget(&delta);
                TranslateCameraGoal(&delta);
                input = 0;
                entry = GetBoundedEntryField(0);
                if (entry->getInputFlags != NULL) {
                    input = entry->getInputFlags(entry);
                }
                if (!(input & 0x10)) {
                    player = func_ov001_0206dc4c(0);
                    if (!VecEquals(&data_ov042_020be5e0->lastPlayerPos, player) && (cam->followFlags & 3)) {
                        u32 follow;
                        fx32 maxY;
                        fx32 minY;
                        fx32 z;
                        player = func_ov001_0206dc4c(0);
                        maxY = cam->maxY;
                        minY = cam->minY;
                        z = player->z;
                        goal = MakeVec(player->x, ClampFx(minY, maxY, player->y - 0x1800), z);
                        goal.x = goal.x > cam->maxX ? cam->maxX : (goal.x < cam->minX ? cam->minX : goal.x);
                        offset = SubtractVec(&goal, &cam->focus);
                        follow = cam->followFlags;
                        if (follow & 4) {
                            if (cam->recenterTimer == -1) {
                                if (follow & 1) {
                                    fx32 dist = offset.x;
                                    if (dist < 0) {
                                        dist = -dist;
                                    }
                                    if (dist > FX_Mul(cam->rangeX, 0x99a)) {
                                        int sign = 0;
                                        int step;
                                        cam->recenterTimer = 0;
                                        if (offset.x != 0) {
                                            if (offset.x > 0) {
                                                sign = 1;
                                            } else {
                                                sign = -1;
                                            }
                                        }
                                        step = FX_Mul(cam->rangeX << 1, 0x8cd);
                                        cam->recenterGoal.x += step * sign;
                                    }
                                }
                                if (cam->followFlags & 2) {
                                    fx32 dist = offset.y;
                                    if (dist < 0) {
                                        dist = -dist;
                                    }
                                    if (dist > FX_Mul(cam->rangeY, 0x99a)) {
                                        int sign = 0;
                                        int step;
                                        cam->recenterTimer = 0;
                                        if (offset.y != 0) {
                                            if (offset.y > 0) {
                                                sign = 1;
                                            } else {
                                                sign = -1;
                                            }
                                        }
                                        step = FX_Mul(cam->rangeY << 1, 0x8cd);
                                        cam->recenterGoal.y += step * sign;
                                    }
                                }
                                if (cam->recenterTimer == 0) {
                                    cam->anchor = cam->focus;
                                } else {
                                    offset = data_0205344c;
                                }
                            }
                            if (cam->recenterTimer != -1) {
                                start = cam->focus;
                                cam->recenterTimer += 0x1000;
                                if (cam->recenterTimer >= 0xf000) {
                                    end = cam->recenterGoal;
                                    cam->recenterTimer = -1;
                                } else {
                                    fx32 t = EaseProgress(cam->recenterTimer, 0xf000, 0);
                                    end = LerpVec(&cam->anchor, &cam->recenterGoal, t << 15);
                                }
                                offset = SubtractVec(&end, &start);
                            }
                        } else if (!(follow & 1)) {
                            offset.x = 0;
                        } else if (!(follow & 2)) {
                            offset.y = 0;
                        }
                        TranslateCameraTarget(&offset);
                        VEC_Add(&delta, &offset, &delta);
                    }
                }
            }
            MoveShape(&data_ov042_020be5e0->colliders[0].shape);
            MoveShape(&data_ov042_020be5e0->colliders[1].shape);
            MoveShape(&data_ov042_020be5e0->colliders[2].shape);
            data_ov042_020be5e0->colliderOffset = delta;
            world = GetActorRegistry();
            if (!(cam->followFlags & 1) || data_ov042_020be5e0->maxX != 0x7fffffff) {
                cam->colliders[0].flags |= 1;
                cam->colliders[1].flags |= 1;
                QuadTree_ReinsertNodeIfFlagSet(*world->tree, (int)&cam->colliders[0]);
                QuadTree_ReinsertNodeIfFlagSet(*world->tree, (int)&cam->colliders[1]);
            }
            if (!(cam->followFlags & 2)) {
                cam->colliders[2].flags |= 1;
                QuadTree_ReinsertNodeIfFlagSet(*world->tree, (int)&cam->colliders[2]);
            } else {
                QuadTree_RemoveObject(*world->tree, (int)&cam->colliders[2]);
            }
            break;
        }
        default:
            goto finish;
        }
        StepCameraGoalTowardTarget();
    }
finish:
    if (data_ov042_020be5e0->particle != 0) {
        if (UpdateDriftParticle(&data_ov042_020be5e0->particle)) {
            data_ov042_020be5e0->flags &= ~0x18000;
        }
        data_ov042_020be5e0->shake = data_ov042_020be5e0->particleShake;
    }
    ApplyCameraShake();
    data_ov042_020be5e0->lastPlayerPos = *func_ov001_0206dc4c(0);
    return FALSE;
}
