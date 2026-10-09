#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CameraView {
    u8 pad_00[0x14];
    VecFx32 position;
    VecFx32 lookAt;
    VecFx32 up;
} CameraView;

typedef struct CameraTrackingFlags {
    int unk_0 : 1;
    int turning : 1;
} CameraTrackingFlags;

typedef struct CameraTracking {
    BOOL active;
    int state;
    int heading;
    fx32 distance;
    int angle;
    fx32 height;
    fx32 unk_18;
    u32 unk_1C;
    u32 unk_20;
    VecFx32 lookAt;
    VecFx32 target;
    VecFx32 prevLookAt;
    VecFx32 prevTarget;
    VecFx32 direction;
    VecFx32 prevDirection;
    VecFx32 unk_6C;
    fx32 prevHeight;
    VecFx32 savedLookAt;
    VecFx32 savedTarget;
    fx32 savedDistance;
    u32 savedAngle;
    fx32 savedHeight;
    fx32 savedUnk18;
    VecFx32 unk_A4;
    int unk_B0;
    int unk_B4;
    u16 unk_B8;
    u16 unk_BA;
    fx32 unk_BC;
    fx32 unk_C0;
    fx32 unk_C4;
    fx32 unk_C8;
    fx32 unk_CC;
    int unk_D0;
    int unk_D4;
    int unk_D8;
    int unk_DC;
    u8 pad_E0[0xc];
    int unk_EC;
    int unk_F0;
    int unk_F4;
    int turnTimer;
    fx32 turnSpeed;
    u8 pad_100[0x4];
    int unk_104;
    int unk_108;
    int unk_10C;
    int unk_110;
    u8 pad_114[0x6];
    u16 unk_11A;
    u8 pad_11C[0xc];
    int unk_128;
    CameraTrackingFlags trackFlags;
    int unk_130;
} CameraTracking;

typedef struct CameraBox {
    VecFx32 max;
    VecFx32 min;
} CameraBox;

typedef struct CameraManagerFlags {
    u32 unk_0 : 1;
} CameraManagerFlags;

typedef struct CameraManager {
    CameraView view;
    VecFx32 eye;
    VecFx32 unk_44;
    u8 pad_50[0x94];
    int mode;
    int prevMode;
    u8 pad_EC[0x4];
    u32 flags;
    int unk_F4;
    CameraBox bounds;
    u8 pad_110[0x18];
    CameraManagerFlags extraFlags;
    u8 pad_12C[0x10];
    CameraTracking tracking;
} CameraManager;

typedef struct Sphere {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct CollisionShape {
    void *data;
    VecFx32 max;
    VecFx32 min;
    int kind;
} CollisionShape;

typedef struct SweptShape {
    CollisionShape shape;
    VecFx32 delta;
    CameraBox sweptBounds;
} SweptShape;

typedef struct QueryWorkspace {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct QueryCallback {
    void *func;
    void *context;
} QueryCallback;

typedef struct QueryFilter {
    s32 unk_00;
    s32 mask;
} QueryFilter;

typedef struct CollisionQuery {
    u8 pad_00[0x48];
    QueryCallback filter;
    QueryCallback contact;
    u8 pad_58[0x8];
} CollisionQuery;

extern CameraManager *g_cameraManager_020c34e0;
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern void RotateVectorAroundAxis_0204b34c(VecFx32 *vec, const VecFx32 *axis, s32 angle);
extern s16 AngleBetweenVecs_0204b070(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern CollisionShape MakeSphereShape_0203ad14(Sphere *storage, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const CameraBox *src, CameraBox *dst, const VecFx32 *delta);
extern u32 GetBoundedEntryField_0206db5c(int index);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern void *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void RotateVecTowardVec_0204b0ac(VecFx32 *vec, const VecFx32 *axis, s32 angle);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL CameraTarget_IsTrackable_020c6dec(void *target, void *work, void *query, void *context);
extern BOOL IsQueryFacingContact_020c1e40(void *ref, void *query);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

static inline QueryFilter MakeFilter(s32 value, s32 mask)
{
    QueryFilter filter;
    filter.unk_00 = value;
    filter.mask = mask;
    return filter;
}

static inline QueryCallback MakeCallback(void *func, void *context)
{
    QueryCallback callback;
    callback.func = func;
    callback.context = context;
    return callback;
}

static inline VecFx32 ScaledVec(VecFx32 vec, fx32 scale)
{
    ScaleVecFx32InPlace_0204a5e4(&vec, scale);
    return vec;
}

static inline VecFx32 RotatedVec(VecFx32 vec, const VecFx32 *axis, s32 angle)
{
    RotateVecTowardVec_0204b0ac(&vec, axis, angle);
    return vec;
}

static inline void MultAddPair(VecFx32 *pos, VecFx32 *copy, fx32 scale, const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    VEC_MultAdd_01ffa09c(scale, a, b, &out);
    *pos = out;
    *copy = *(VecFx32 *)&out;
}

static inline VecFx32 SubVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 out;
    VEC_Subtract_01ff9e3c(a, b, &out);
    return out;
}

BOOL Camera_FindClearOrbit_020c6e10(int angle)
{
    QueryWorkspace workspace;
    SweptShape shapeCopy;
    CollisionQuery sweep;
    SweptShape stepShapeCopy;
    CollisionQuery stepSweep;
    SweptShape shape;
    CollisionQuery query;
    SweptShape stepShape;
    CollisionQuery stepQuery;
    Sphere sphere;
    VecFx32 center;
    VecFx32 reference;
    VecFx32 rotated;
    VecFx32 stepDir;
    VecFx32 nextPos;
    VecFx32 start;
    VecFx32 axis;
    VecFx32 offset;
    VecFx32 stepPos;
    VecFx32 stepDelta;
    VecFx32 back;
    QueryFilter filter;
    QueryFilter stepFilter;
    CameraManager *camera = g_cameraManager_020c34e0;
    CameraTracking *tracking = &camera->tracking;
    fx32 distance;
    s64 totalAngle;
    s32 sweepAngle;

    back = tracking->direction;
    NegateVecFx32_0204aa40(&back);
    start = back;
    *(VecFx32 *)&reference = *(VecFx32 *)&back;
    rotated = *(VecFx32 *)&back;
    axis = MakeVec(0, -0x1000, 0);
    RotateVectorAroundAxis_0204b34c(&rotated, &axis, (s64)(s16)(angle - tracking->angle) * 0x6488 / 0x10000);
    totalAngle = (s64)AngleBetweenVecs_0204b070(&reference, &rotated) * 0x6488 / 0x10000;
    distance = tracking->distance;
    if (distance > 0x2800) {
        distance = 0x2800;
    }
    offset = ScaledVec(rotated, distance);
    shape.shape = MakeSphereShape_0203ad14(&sphere, &tracking->target, 0x4cd);
    shape.delta = offset;
    OffsetBoxByDelta_0203ac70((CameraBox *)&shape.shape.max, &shape.sweptBounds, &shape.delta);
    shapeCopy = shape;
    filter = MakeFilter(0, 0xe);
    CollisionQuery_Init_02034c74(&query, 0, (void *)(GetBoundedEntryField_0206db5c(0) + 0x14), 0xf, 1, 1, &shapeCopy, &workspace, &filter);
    sweep = query;
    sweep.filter = MakeCallback(CameraTarget_IsTrackable_020c6dec, camera);
    sweep.contact = MakeCallback(IsQueryFacingContact_020c1e40, NULL);
    if (SweepWorldCollision_020364a0(&sweep)) {
        return TRUE;
    }
    center = sphere.center;
    for (sweepAngle = totalAngle - 0x2ca; sweepAngle >= 0; sweepAngle -= 0x2ca) {
        stepDir = RotatedVec(start, &rotated, sweepAngle);
        MultAddPair(&stepPos, &nextPos, distance, &stepDir, &tracking->target);
        stepDelta = SubVec(&nextPos, &center);
        stepShape.shape = MakeSphereShape_0203ad14(&sphere, &center, 0x4cd);
        stepShape.delta = stepDelta;
        OffsetBoxByDelta_0203ac70((CameraBox *)&stepShape.shape.max, &stepShape.sweptBounds, &stepShape.delta);
        stepShapeCopy = stepShape;
        stepFilter = MakeFilter(0, 0xe);
        CollisionQuery_Init_02034c74(&stepQuery, 0, (void *)(GetBoundedEntryField_0206db5c(0) + 0x14), 0xf, 1, 1, &stepShapeCopy, &workspace, &stepFilter);
        stepSweep = stepQuery;
        stepSweep.filter = MakeCallback(CameraTarget_IsTrackable_020c6dec, camera);
        if (SweepWorldCollision_020364a0(&stepSweep)) {
            return TRUE;
        }
        center = stepPos;
    }
    return FALSE;
}
