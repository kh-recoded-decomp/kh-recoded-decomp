#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct Sphere {
    VecFx32 center;
    fx32 radius;
} Sphere;

typedef struct CollisionShape {
    Sphere *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct SweptShape {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct {
    s32 unk_00;
    s32 mask;
} QueryFilter;

typedef struct {
    u32 words[0x18];
} CollisionQuery;

typedef struct Surface {
    u8 pad_00[0x40];
    s32 kind;
} Surface;

typedef struct ActorBody {
    u8 pad_000[0x10c];
    Surface surface;
} ActorBody;

typedef struct {
    u8 kind;
    u8 mode;
    u8 group;
} TouchInfo;

typedef struct {
    u8 pad_000[0x194];
    TouchInfo touch;
} ObjectExtension;

typedef struct {
    u8 pad_00[0x14];
    ObjectExtension *ext;
    u8 pad_18[0x54];
    s32 type;
} HitObject;

typedef struct {
    u8 pad_00[0x10];
    HitObject *object;
    u8 pad_14[0x18];
    void *surface;
} CollisionHit;

typedef struct {
    u8 pad_00[0xa];
    u16 group;
} StageController;

typedef struct {
    u8 pad_000[0x10];
    ActorBody body;
    u8 pad_160[0x72];
    u16 stageId;
    u8 pad_1D4[0x98];
    u32 stateBits : 31;
    u32 stateTop : 1;
    u8 pad_270[0x18];
    u16 drawLow : 13;
    u16 ignoreTouch : 1;
    u16 drawHigh : 2;
    u8 pad_28A[0x2];
    u16 moveLow : 7;
    u16 moveKind : 4;
    u16 moveHigh : 5;
} MoveActor;

extern fx32 Surface_GetKindValue_02034c24(Surface *surface);
extern CollisionShape func_0203ad14(Sphere *storage, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, QueryFilter *filter);
extern CollisionHit *SweepWorldCollision_020364a0(CollisionQuery *query);
extern StageController *GetStageController_0209c120(u16 stageId);
extern void addScaledVector_020301ac(void *surface, const VecFx32 *delta, const VecFx32 *origin, VecFx32 *out);

CollisionHit *SweepActorMove_02097dc8(MoveActor *actor, const VecFx32 *from, const VecFx32 *delta, VecFx32 *out) {
    ActorBody *body = &actor->body;
    QueryWorkspace workspace;
    SweptShape shapeCopy;
    CollisionQuery sweep;
    SweptShape shape;
    CollisionQuery query;
    VecFx32 center;
    Sphere sphere;
    QueryFilter filter;
    CollisionHit *hit;
    HitObject *object;
    fx32 radius;

    if (actor->moveKind == 0) {
        return NULL;
    }
    if (actor->stateBits & 0x40000) {
        return NULL;
    }
    center = *from;
    filter.mask = 0x18;
    radius = Surface_GetKindValue_02034c24(&body->surface);
    center.y += radius;
    shape.shape = func_0203ad14(&sphere, &center, radius);
    shape.delta = *delta;
    OffsetBoxByDelta_0203ac70(&shape.shape.bounds, &shape.sweptBounds, &shape.delta);
    shapeCopy = shape;
    CollisionQuery_Init_02034c74(&query, 0, &actor->body, 0xe, 1, 1, &shapeCopy, &workspace, &filter);
    sweep = query;
    hit = SweepWorldCollision_020364a0(&sweep);
    if (hit == NULL) {
        return NULL;
    }
    object = hit->object;
    if (object != NULL) {
        if (object->type == 2) {
            return NULL;
        }
        if (object->type == 5) {
            return NULL;
        }
    }
    if (object != NULL && object->ext != NULL) {
        TouchInfo *touch = &object->ext->touch;

        if (actor->ignoreTouch) {
            return NULL;
        }
        if (touch != NULL && touch->kind == 0) {
            return NULL;
        }
        if (touch != NULL && touch->kind == 1) {
            u8 group = touch->group;

            if (touch->mode == 1 && group != 0) {
                StageController *controller = GetStageController_0209c120(actor->stageId);

                if (controller != NULL && group == controller->group) {
                    return NULL;
                }
            }
        }
    }
    addScaledVector_020301ac(hit->surface, delta, &center, out);
    return hit;
}
