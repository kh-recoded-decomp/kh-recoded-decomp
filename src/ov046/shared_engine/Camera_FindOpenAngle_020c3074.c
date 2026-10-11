#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct QueryCallback {
    BOOL (*func)();
    void *arg;
} QueryCallback;

typedef struct SweepQuery {
    u8 pad_00[0x48];
    QueryCallback filter;
    QueryCallback contact;
    u8 pad_58[8];
} SweepQuery;

typedef struct QueryWorkspace {
    u8 data[0x1a4];
} QueryWorkspace;

typedef struct SweepShape {
    void *data;
    s32 bounds[6];
    s32 kind;
    VecFx32 delta;
    s32 sweptBounds[6];
} SweepShape;

typedef struct ShapeExtent {
    VecFx32 center;
    fx32 radius;
} ShapeExtent;

typedef struct QueryMask {
    s32 group;
    s32 layers;
} QueryMask;

typedef struct SweepHit {
    u8 pad_00[0x24];
    fx32 depth;
} SweepHit;

typedef struct CameraManager {
    u8 pad_00[0x38];
    VecFx32 eye;
} CameraManager;

extern CameraManager *g_cameraManager_020c34e0;
extern const s16 data_0205356c[];
extern void func_ov046_020c2cb8(VecFx32 *out);
extern fx32 FX_Sqrt_01ff9cfc(fx32 value);
extern int FixedPointMultiply12(int left, int right);
extern void func_0203ad14(SweepShape *shape, ShapeExtent *extent, VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(s32 *src, s32 *dst, VecFx32 *delta);
extern u32 GetBoundedEntryField_0206db5c(int index);
extern void CollisionQuery_Init_02034c74(SweepQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, SweepShape *shape, QueryWorkspace *workspace, QueryMask *mask);
extern SweepHit *SweepWorldCollision_020364a0(SweepQuery *query);
extern BOOL CameraCollision_ShouldBlock_020c320c();
extern BOOL CameraCollision_CheckContact_020c3254();

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

static inline VecFx32 GetCameraFocus(void)
{
    VecFx32 result;
    func_ov046_020c2cb8(&result);
    return result;
}

static inline fx32 LengthSquared(fx32 x, fx32 z)
{
    return (fx32)(((s64)x * x + (s64)z * z) >> FX32_SHIFT);
}

u16 Camera_FindOpenAngle_020c3074(void)
{
    CameraManager *camera;
    int i;
    fx32 dx;
    fx32 dz;
    SweepShape shape;
    QueryWorkspace workspace;
    SweepQuery query;
    SweepShape initShape;
    SweepQuery initQuery;
    VecFx32 focus;
    ShapeExtent extent;
    VecFx32 delta;
    QueryMask mask;
    QueryMask maskTmp;
    QueryCallback filterCb;
    QueryCallback contactCb;
    QueryMask *maskRef;
    void *actor;
    fx32 radius;
    u16 bestAngle;
    fx32 bestDepth;
    u16 angle;
    fx32 dy;
    SweepHit *hit;

    camera = g_cameraManager_020c34e0;
    focus = GetCameraFocus();
    dx = camera->eye.x - focus.x;
    dz = camera->eye.z - focus.z;
    radius = FX_Sqrt_01ff9cfc(LengthSquared(dx, dz));
    bestAngle = 0;
    bestDepth = (fx32)0x80000000;
    i = 0;
    dy = camera->eye.y - focus.y;
    for (; i < 4; i++) {
        angle = i * 0xffff / 4 + 0xffff / 4;
        delta = MakeVec(FixedPointMultiply12(data_0205356c[angle >> 4], radius), dy, FixedPointMultiply12(data_0205356c[(0x400 - (angle >> 4)) & 0xfff], radius));
        func_0203ad14(&initShape, &extent, &focus, 0x666);
        initShape.delta = delta;
        OffsetBoxByDelta_0203ac70(initShape.bounds, initShape.sweptBounds, &initShape.delta);
        shape = initShape;
        maskTmp.group = 0;
        maskTmp.layers = 0xe;
        mask = maskTmp;
        maskRef = &mask;
        actor = NULL;
        if (GetBoundedEntryField_0206db5c(0) != 0) {
            actor = (void *)(GetBoundedEntryField_0206db5c(0) + 0x14);
        }
        CollisionQuery_Init_02034c74(&initQuery, 0, actor, 0xf, 1, 1, &shape, &workspace, maskRef);
        query = initQuery;
        filterCb.func = CameraCollision_ShouldBlock_020c320c;
        filterCb.arg = NULL;
        query.filter = filterCb;
        contactCb.func = CameraCollision_CheckContact_020c3254;
        contactCb.arg = NULL;
        query.contact = contactCb;
        hit = SweepWorldCollision_020364a0(&query);
        if (hit != NULL) {
            if (bestDepth < hit->depth) {
                bestDepth = hit->depth;
                bestAngle = angle;
            }
        } else {
            bestAngle = angle;
            break;
        }
    }
    return bestAngle + 0x7fff;
}
