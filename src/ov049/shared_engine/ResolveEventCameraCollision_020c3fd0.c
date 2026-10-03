#include "nitro/types.h"
#include "nitro/fx_types.h"

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

typedef struct EventCameraWork {
    VecFx32 position;
    u8 pad00c[0x190];
    fx32 distance;
} EventCameraWork;

extern void func_ov046_020c2cb8(VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_0203ad14(SweepShape *shape, ShapeExtent *extent, VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(s32 *src, s32 *dst, VecFx32 *delta);
extern u32 GetBoundedEntryField_0206db5c(int index);
extern void CollisionQuery_Init_02034c74(SweepQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, SweepShape *shape, QueryWorkspace *workspace, QueryMask *mask);
extern void func_01ff9f88(const VecFx32 *in, VecFx32 *out);
extern void VEC_MultAdd_01ffa09c(int scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void *SweepWorldCollision_020364a0(SweepQuery *query);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern BOOL CameraCollision_ShouldBlock_020c320c();
extern BOOL CameraCollision_CheckContact_020c3254();

void ResolveEventCameraCollision_020c3fd0(EventCameraWork *work)
{
    SweepShape shape;
    QueryWorkspace workspace;
    SweepQuery query;
    SweepShape initShape;
    SweepQuery initQuery;
    VecFx32 focus;
    ShapeExtent extent;
    VecFx32 sweepDir;
    VecFx32 dirArg;
    VecFx32 focusTmp;
    VecFx32 delta;
    VecFx32 deltaTmp;
    VecFx32 normTmp;
    QueryMask mask;
    QueryMask maskTmp;
    QueryCallback filterCb;
    QueryCallback contactCb;
    QueryMask *maskRef;
    void *actor;

    func_ov046_020c2cb8(&focusTmp);
    focus = focusTmp;
    VEC_Subtract_01ff9e3c(&work->position, &focus, &deltaTmp);
    delta = deltaTmp;
    func_0203ad14(&initShape, &extent, &focus, 0x4cd);
    initShape.delta = delta;
    OffsetBoxByDelta_0203ac70(initShape.bounds, initShape.sweptBounds, &initShape.delta);
    shape = initShape;
    sweepDir = shape.delta;
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
    if (SweepWorldCollision_020364a0(&query) != NULL) {
        work->distance = func_01ffa0f4(&focus, &extent.center);
        if (work->distance < 0xc00) {
            func_01ff9f88(&sweepDir, &normTmp);
            dirArg = normTmp;
            VEC_MultAdd_01ffa09c(0xc00, &dirArg, &focus, &extent.center);
            work->distance = 0xc00;
        }
        work->position = extent.center;
    }
}
