#pragma opt_loop_invariants off
#pragma opt_common_subs off
#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollBox {
    VecFx32 max;
    VecFx32 min;
} CollBox;

typedef struct CollSphere {
    VecFx32 center;
    fx32 radius;
} CollSphere;

typedef struct CollShape {
    CollSphere *geometry;
    CollBox box;
    s32 kind;
} CollShape;

typedef struct SweepShape {
    CollSphere *geometry;
    CollBox bounds;
    s32 kind;
    VecFx32 delta;
    CollBox sweptBounds;
} SweepShape;

typedef struct ContactNormal {
    fx16 x;
    fx16 y;
    fx16 z;
} ContactNormal;

typedef struct ContactOwner {
    u8 pad_00[0x14];
    ContactNormal normal;
} ContactOwner;

typedef struct ContactEntry {
    ContactOwner *owner;
    s32 category;
    s32 unk08;
} ContactEntry;

typedef struct QueryWorkspace {
    ContactEntry entries[32];
    u8 count;
    u8 pad_181[0x1a4 - 0x181];
} QueryWorkspace;

typedef struct QueryCallback {
    BOOL (*func)();
    void *arg;
} QueryCallback;

typedef struct SweepQuery {
    u8 pad_00[0x28];
    QueryWorkspace *workspace;
    u8 pad_2c[0x48 - 0x2c];
    QueryCallback filter;
    QueryCallback contact;
    u8 pad_58[8];
} SweepQuery;

typedef struct CollisionResult {
    u8 pad_00[0x18];
    VecFx32 normal;
    s32 blocking;
    u8 pad_28[0x44 - 0x28];
    QueryWorkspace *workspace;
} CollisionResult;

typedef struct QueryMask {
    s32 group;
    s32 layers;
} QueryMask;

typedef struct CameraProbe {
    CollSphere sphere;
    CollShape shape;
    s32 hit : 1;
    s32 slowDown : 1;
    VecFx32 normal;
} CameraProbe;

typedef struct FollowControl {
    u8 pad_00[0xc];
    fx32 distance;
    u32 heading;
    u8 pad_14[0x134 - 0x14];
    QueryWorkspace workspace;
} FollowControl;

typedef struct CameraManager {
    u8 pad_00[0x80];
    s32 type;
    u8 pad_84[0xe4 - 0x84];
    s32 followPreset;
    u8 pad_e8[0xf0 - 0xe8];
    u32 stateFlags;
    s32 pathActive;
    u8 buffers[0x128 - 0xf8];
    s32 climbing : 1;
    u8 pad_12c[0x13c - 0x12c];
    FollowControl follow;
} CameraManager;

typedef struct SinCos {
    fx32 cos;
    fx32 sin;
} SinCos;

typedef struct Vec2Fx32 {
    fx32 x;
    fx32 y;
} Vec2Fx32;

extern CameraManager *g_cameraManager_020c34e0;
extern const s16 data_0205356c[];
extern const VecFx32 data_02053438;
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_CrossProduct_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *vec);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_Normalize_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void MakeSphereShape_0203ad14(void *shape, CollSphere *sphere, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const CollBox *src, CollBox *dst, const VecFx32 *delta);
extern u32 GetBoundedEntryField_0206db5c(int index);
extern void CollisionQuery_Init_02034c74(SweepQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, SweepShape *shape, QueryWorkspace *workspace, QueryMask *mask);
extern void func_020350d4(SweepQuery *query, void *buffers);
extern CollisionResult *SweepWorldCollision_020364a0(SweepQuery *query);
extern VecFx32 GetNormalizedCross_0204b9c8(const VecFx32 *vec, const VecFx32 *axis, BOOL verticalOnly);
extern int func_02006450(int left, int right);
extern fx32 Camera_ComputeFollowDistance_020c1a70(int preset);
extern BOOL Camera_CanTrackTarget_020c1ba8();
extern BOOL CameraProbe_CheckContact_020c1cc8();
extern fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern fx32 DotFx32Xy_0204a390(const Vec2Fx32 *a, const Vec2Fx32 *b);

static inline fx32 MulFx(fx32 a, fx32 b)
{
    return (fx32)(((fx64)a * b + 0x800) >> 12);
}

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

static inline Vec2Fx32 MakeVec2(fx32 x, fx32 y)
{
    Vec2Fx32 vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

static inline SinCos GetSinCos(int index)
{
    SinCos result;
    result.cos = data_0205356c[(0x400 - index) & 0xfff];
    result.sin = data_0205356c[index];
    return result;
}

static inline VecFx32 VecSub(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Subtract_01ff9e3c(a, b, &result);
    return result;
}

static inline VecFx32 VecAdd(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Add_01ff9e0c(a, b, &result);
    return result;
}

static inline VecFx32 VecCross(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_CrossProduct_01ff9ea8(a, b, &result);
    return result;
}

static inline void GetSideNormal(VecFx32 *out, const VecFx32 *delta, const VecFx32 *up)
{
    *out = GetNormalizedCross_0204b9c8(delta, up, TRUE);
}

static inline VecFx32 VecScaled(VecFx32 vec, fx32 scale)
{
    ScaleVecFx32InPlace_0204a5e4(&vec, scale);
    return vec;
}

static inline VecFx32 GetHeadingNormal(SinCos angle)
{
    VecFx32 vec;
    VecFx32 axis;
    VecFx32 dir;
    VecFx32 up;
    VecFx32 result;
    fx64 upY;

    up.x = 0;
    up.y = FX32_ONE;
    up.z = 0;
    axis = up;
    dir.x = -angle.sin;
    dir.y = 0;
    dir.z = -angle.cos;
    vec = dir;
    upY = axis.y;
    result.x = -(fx32)((vec.z * upY + 0x800) >> 12);
    result.y = 0;
    result.z = (fx32)((vec.x * upY + 0x800) >> 12);
    return result;
}

static inline VecFx32 GetSlideDirection(const VecFx32 *normal, const VecFx32 *wall, const VecFx32 *dir, VecFx32 *axis, VecFx32 *projected)
{
    VecFx32 slide;
    VecFx32 scaled;
    VecFx32 edge;
    VecFx32 input;
    VecFx32 cross;
    VecFx32 unit;
    fx32 length;

    VEC_CrossProduct_01ff9ea8(normal, wall, &cross);
    input = cross;
    VEC_NormalizeUnchecked_01ff9f88(&input, &unit);
    edge = unit;
    *axis = unit;
    length = VEC_DotProduct_01ff9e6c(dir, axis);
    scaled = edge;
    ScaleVecFx32InPlace_0204a5e4(&scaled, length);
    *projected = scaled;
    VEC_Normalize_01ffaff4(projected, &slide);
    return slide;
}

static inline VecFx32 RejectFrom(const VecFx32 *offset, const VecFx32 *dir, fx32 dot)
{
    VecFx32 along;
    VecFx32 scaled;
    VecFx32 result;

    scaled = *dir;
    ScaleVecFx32InPlace_0204a5e4(&scaled, dot);
    along = scaled;
    VEC_Subtract_01ff9e3c(offset, &along, &result);
    return result;
}

static inline QueryCallback MakeCallback(BOOL (*func)(), void *arg)
{
    QueryCallback callback;
    callback.func = func;
    callback.arg = arg;
    return callback;
}

static inline VecFx32 GetContactNormal(const ContactNormal *src)
{
    VecFx32 normal;
    normal.x = src->x;
    normal.y = src->y;
    normal.z = src->z;
    return normal;
}

static inline CollShape MakeSphere(CollSphere *sphere, const VecFx32 *center, fx32 radius)
{
    CollShape shape;
    MakeSphereShape_0203ad14(&shape, sphere, center, radius);
    return shape;
}

static inline int SignOf(fx32 value)
{
    if (value == 0) {
        return 0;
    }
    if (value > 0) {
        return 1;
    }
    return -1;
}

static inline fx32 Length2D(const Vec2Fx32 *vec)
{
    fx64 y = vec->y;
    fx64 x = vec->x;

    return FX_Sqrt_01ff9cfc((fx32)((x * x + y * y) >> 12));
}

void Camera_SlideEyeAlongWalls_020c1fa0(VecFx32 *target, VecFx32 *eye)
{
    SweepShape shape;
    QueryWorkspace workspace;
    SweepQuery query;
    SweepShape initShape;
    SweepQuery initQuery;
    SweepShape retryShape;
    CollSphere extent;
    CameraProbe probe;
    VecFx32 dir;
    VecFx32 flatDir;
    VecFx32 wallNormal;
    VecFx32 prevNormal;
    VecFx32 contactNormal;
    VecFx32 axis;
    VecFx32 slide;
    VecFx32 side;
    VecFx32 perp;
    VecFx32 move;
    VecFx32 clampedRef;
    VecFx32 altRef;
    VecFx32 delta;
    VecFx32 up;
    VecFx32 projected;
    VecFx32 offset;
    VecFx32 clamped;
    VecFx32 alt;
    VecFx32 retryDelta;
    Vec2Fx32 offset2d;
    Vec2Fx32 move2d;
    QueryMask mask;
    QueryMask maskTmp;
    SinCos angle;
    QueryMask *maskRef;
    void *actor;
    u32 flags;
    CollisionResult *result;
    QueryWorkspace *contacts;
    fx32 followDist;
    fx32 dot;
    fx32 slideY;
    fx32 eyeY;
    fx32 centerY;
    fx32 maxDown;
    fx32 lenOffset;
    fx32 lenMove;
    int iteration;
    fx32 dist;
    fx32 maxSlope;
    fx32 minRise;
    fx64 radiusSq;
    fx64 followDistSq;
    CameraManager *camera = g_cameraManager_020c34e0;
    FollowControl *follow;
    fx32 radius;

    follow = camera->type == 0 ? &camera->follow : NULL;
    delta = VecSub(eye, target);
    MakeSphereShape_0203ad14(&initShape, &extent, target, 0x666);
    initShape.delta = delta;
    OffsetBoxByDelta_0203ac70(&initShape.bounds, &initShape.sweptBounds, &initShape.delta);
    shape = initShape;
    maskTmp.group = 0;
    maskTmp.layers = 0xe;
    mask = maskTmp;
    maskRef = &mask;
    if (GetBoundedEntryField_0206db5c(0) != 0 && camera->pathActive == 0) {
        actor = (void *)(GetBoundedEntryField_0206db5c(0) + 0x14);
    } else {
        actor = NULL;
    }
    CollisionQuery_Init_02034c74(&initQuery, 0, actor, 0xf, 1, 1, &shape, follow != NULL ? &follow->workspace : &workspace, maskRef);
    query = initQuery;
    if (follow != NULL) {
        func_020350d4(&query, camera->buffers);
    }
    probe.shape = MakeSphere(&probe.sphere, eye, 0x656);
    probe.hit = FALSE;
    probe.slowDown = FALSE;
    if (follow != NULL) {
        angle = GetSinCos((u16)follow->heading >> 4);
        probe.normal = GetHeadingNormal(angle);
    } else {
        up = MakeVec(0, FX32_ONE, 0);
        GetSideNormal(&probe.normal, &shape.delta, &up);
    }
    query.filter = MakeCallback(Camera_CanTrackTarget_020c1ba8, camera);
    query.contact = MakeCallback(CameraProbe_CheckContact_020c1cc8, &probe);
    dir = shape.delta;
    flatDir = MakeVec(shape.delta.x, 0, shape.delta.z);
    wallNormal = probe.normal;
    VecCross(&dir, &wallNormal);
    prevNormal = data_02053438;
    flags = camera->stateFlags;
    if (flags & 0x2000) {
        radius = 3 << 10;
    } else {
        radius = 10 << 10;
    }
    if (flags & 0x80000) {
        radius = func_02006450(radius, 0x2000);
    }
    if (follow != NULL) {
        followDist = follow->distance;
    } else {
        followDist = Camera_ComputeFollowDistance_020c1a70(camera->followPreset);
    }
    maxDown = data_0205356c[0x200];
    iteration = 0;
    maxSlope = data_0205356c[0x155];
    minRise = data_0205356c[0x2e3];
    radiusSq = ((fx64)radius * radius + 0x800) >> 12;
    followDistSq = ((fx64)followDist * followDist + 0x800) >> 12;
    for (;; iteration++) {
        VecAdd(&extent.center, &shape.delta);
        result = SweepWorldCollision_020364a0(&query);
        if (result == NULL) {
            break;
        }
        dist = func_01ffa0f4(&extent.center, target);
        if ((follow == NULL || !camera->climbing) && extent.center.y >= eye->y && dist >= radius) {
            break;
        }
        contacts = result->workspace;
        if (contacts->entries[contacts->count - 1].category != 4) {
            contactNormal = GetContactNormal(&contacts->entries[contacts->count - 1].owner->normal);
        } else {
            contactNormal = result->normal;
        }
        if (AbsDotProduct_0204a96c(&contactNormal, &wallNormal) >= 0xff0) {
            continue;
        }
        slide = GetSlideDirection(&contactNormal, &wallNormal, &dir, &axis, &projected);
        if (slide.x == 0 && slide.y == 0 && slide.z == 0) {
            break;
        }
        if (iteration == 0) {
            BOOL downward = FALSE;
            fx32 y = slide.y;
            if (y < 0 && y > -maxDown) {
                downward = TRUE;
            }
            if (y * (downward ? -1 : 1) < 0) {
                NegateVecFx32_0204aa40(&slide);
            }
        } else if (VEC_DotProduct_01ff9e6c(&slide, &prevNormal) < -0x80) {
            NegateVecFx32_0204aa40(&slide);
        }
        slideY = slide.y;
        if (slideY < -maxSlope) {
            break;
        }
        if (follow == NULL || !camera->climbing) {
            if (slideY > maxSlope) {
                break;
            }
        } else if (slideY > 0) {
            break;
        }
        if (iteration != 0 && VEC_DotProduct_01ff9e6c(&slide, &prevNormal) < 0) {
            break;
        }
        if (VEC_DotProduct_01ff9e6c(&slide, &flatDir) < 0 && slide.y < minRise) {
            break;
        }
        side = VecCross(&slide, &wallNormal);
        if (prevNormal.x != 0 || prevNormal.y != 0 || prevNormal.z != 0) {
            int prevSign = SignOf(VEC_DotProduct_01ff9e6c(&side, &prevNormal));
            int contactSign = SignOf(VEC_DotProduct_01ff9e6c(&side, &contactNormal));

            if (contactSign != prevSign) {
                break;
            }
        }
        offset = VecSub(&extent.center, target);
        dot = VEC_DotProduct_01ff9e6c(&offset, &slide);
        perp = RejectFrom(&offset, &slide, dot);
        if (slide.y > 0) {
            fx32 mag = VEC_Mag_01ff9f28(&perp);
            move = VecScaled(slide, FX_Sqrt_01ff9cfc((fx32)radiusSq - MulFx(mag, mag)) - dot);
            eyeY = eye->y;
            centerY = extent.center.y;
            if (centerY < eyeY) {
                clamped = VecScaled(move, FX_Div_01ff9c84(eyeY - centerY, move.y));
                clampedRef = clamped;
                if (move.y < clampedRef.y) {
                    fx32 mag2 = VEC_Mag_01ff9f28(&perp);
                    alt = VecScaled(slide, FX_Sqrt_01ff9cfc((fx32)followDistSq - MulFx(mag2, mag2)) - dot);
                    altRef = alt;
                    if (VEC_Mag_01ff9f28(&clampedRef) > VEC_Mag_01ff9f28(&altRef)) {
                        move = *(VecFx32 *)&alt;
                    } else {
                        move = *(VecFx32 *)&clamped;
                    }
                }
            }
            if (dist >= 0xc00) {
                offset2d = MakeVec2(extent.center.x - target->x, extent.center.z - target->z);
                move2d = MakeVec2(move.x, move.z);
                if (DotFx32Xy_0204a390(&offset2d, &move2d) <= 0) {
                    lenOffset = Length2D(&offset2d);
                    if (lenOffset > 0x800) {
                        lenMove = Length2D(&move2d);
                        if (lenMove > lenOffset) {
                            ScaleVecFx32InPlace_0204a5e4(&move, FX_Div_01ff9c84(lenOffset, lenMove));
                        }
                    }
                }
            }
        } else {
            fx32 mag = VEC_Mag_01ff9f28(&perp);
            move = VecScaled(slide, FX_Sqrt_01ff9cfc((fx32)followDistSq - MulFx(mag, mag)) - dot);
        }
        shape.delta = move;
        OffsetBoxByDelta_0203ac70(&shape.bounds, &shape.sweptBounds, &shape.delta);
        prevNormal = contactNormal;
    }
    if (query.workspace->count != 0) {
        probe.slowDown = TRUE;
        do {
            retryDelta = VecSub(&extent.center, target);
            MakeSphereShape_0203ad14(&retryShape, &extent, target, 0x666);
            retryShape.delta = retryDelta;
            OffsetBoxByDelta_0203ac70(&retryShape.bounds, &retryShape.sweptBounds, &retryShape.delta);
            shape = retryShape;
            probe.hit = FALSE;
            result = SweepWorldCollision_020364a0(&query);
        } while (result != NULL && probe.hit && result->blocking != 0);
    }
    *eye = extent.center;
    if (func_01ffa0f4(eye, target) < 0x80) {
        *eye = dir;
        VEC_Normalize_01ffaff4(eye, eye);
        ScaleVecFx32InPlace_0204a5e4(eye, 0x80);
        VEC_Add_01ff9e0c(eye, target, eye);
    }
}
