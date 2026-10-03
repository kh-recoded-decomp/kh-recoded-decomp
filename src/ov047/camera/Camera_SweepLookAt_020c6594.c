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

typedef struct SweepHit {
    u8 pad_00[0x24];
    int blocking;
} SweepHit;

typedef struct CameraProbe {
    BOOL hit;
    BOOL decelerate;
    Sphere sphere;
    CollisionShape shape;
} CameraProbe;

extern CameraManager *g_cameraManager_020c34e0;
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern CollisionShape func_0203ad14(Sphere *storage, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const CameraBox *src, CameraBox *dst, const VecFx32 *delta);
extern u32 GetBoundedEntryField_0206db5c(int index);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern void func_020350d4(CollisionQuery *query, CameraBox *bounds);
extern SweepHit *SweepWorldCollision_020364a0(CollisionQuery *query);
extern BOOL Camera_CanTrackTarget_020c1ba8(void *contact, void *context);
extern BOOL CameraProbe_TestContact_020c64b0(void *ref, void *query, CameraProbe *probe, void *source);

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

void Camera_SweepLookAt_020c6594(CameraTracking *tracking, fx32 radius)
{
    SweptShape shapeCopy;
    QueryWorkspace workspace;
    CollisionQuery sweep;
    SweptShape shape;
    CollisionQuery query;
    SweptShape stepShape;
    Sphere sphere;
    CameraProbe probe;
    VecFx32 deltaCopy;
    VecFx32 stepDeltaCopy;
    VecFx32 delta;
    CollisionShape probeShape;
    VecFx32 stepDelta;
    QueryFilter filter;
    QueryFilter *filterArg;
    CameraManager *camera = g_cameraManager_020c34e0;
    SweepHit *hit;

    VEC_Subtract_01ff9e3c(&tracking->lookAt, &tracking->target, &delta);
    deltaCopy = delta;
    shape.shape = func_0203ad14(&sphere, &tracking->target, radius);
    shape.delta = deltaCopy;
    OffsetBoxByDelta_0203ac70((CameraBox *)&shape.shape.max, &shape.sweptBounds, &shape.delta);
    shapeCopy = shape;
    filter = MakeFilter(0, 0xe);
    filterArg = &filter;
    CollisionQuery_Init_02034c74(&query, 0,
                                 (GetBoundedEntryField_0206db5c(0) && camera->unk_F4 == 0) ? (void *)(GetBoundedEntryField_0206db5c(0) + 0x14) : NULL,
                                 0xf, 1, 1, &shapeCopy, &workspace, filterArg);
    sweep = query;
    func_020350d4(&sweep, &camera->bounds);
    probe.hit = FALSE;
    probe.decelerate = FALSE;
    probeShape = func_0203ad14(&probe.sphere, &tracking->lookAt, radius - 0x10);
    probe.shape = probeShape;
    sweep.filter = MakeCallback(Camera_CanTrackTarget_020c1ba8, camera);
    sweep.contact = MakeCallback(CameraProbe_TestContact_020c64b0, &probe);
    if (SweepWorldCollision_020364a0(&sweep)) {
        tracking->unk_128 = -1;
        camera->flags &= ~0x4000000;
        probe.decelerate = TRUE;
        do {
            VEC_Subtract_01ff9e3c(&sphere.center, &tracking->target, &stepDelta);
            stepDeltaCopy = stepDelta;
            stepShape.shape = func_0203ad14(&sphere, &tracking->target, radius);
            stepShape.delta = stepDeltaCopy;
            OffsetBoxByDelta_0203ac70((CameraBox *)&stepShape.shape.max, &stepShape.sweptBounds, &stepShape.delta);
            shapeCopy = stepShape;
            probe.hit = FALSE;
            hit = SweepWorldCollision_020364a0(&sweep);
        } while (hit && probe.hit && hit->blocking != 0);
    }
    tracking->lookAt = sphere.center;
}

