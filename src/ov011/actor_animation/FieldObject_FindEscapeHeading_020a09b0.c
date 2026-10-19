#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "ov011/SpawnCollisionOwner.h"

typedef struct { VecFx32 max, min; } CollisionBounds;
typedef struct { void *geometry; CollisionBounds bounds; s32 kind; } CollisionShape;
typedef struct { VecFx32 center; fx32 radius; } CollisionSphere;
typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    CollisionBounds sweptBounds;
} SweptShape;

/* These objects are initialized by the collision subsystem. The query is
 * copied by value; its individual fields are not inspected here. */
typedef struct { u8 reserved[0x1a4]; } QueryWorkspace;
typedef struct { u32 reserved[0x60 / 4]; } CollisionQuery;
typedef struct { u8 reserved[0x24]; fx32 nearestTime; } CollisionResult;
typedef struct { s32 category; s32 mask; } QueryFilter;

extern void VEC_Add(const VecFx32 *, const VecFx32 *, VecFx32 *);
extern fx32 FX_Mul(fx32, fx32);
extern u16 FX_Atan2Idx(fx32, fx32);
extern const s16 gSinFx12Table[];
extern void MakeSphereShape(CollisionShape *, CollisionSphere *, const VecFx32 *, fx32);
extern void OffsetBoxByDelta(const CollisionBounds *, CollisionBounds *, const VecFx32 *);
extern void CollisionQuery_Init(CollisionQuery *, u16, void *, u8, u8, u8,
    SweptShape *, QueryWorkspace *, const QueryFilter *);
extern CollisionResult *SweepWorldCollision(CollisionQuery *);

static inline VecFx32 MakeVector(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

static inline VecFx32 AddVectors(const VecFx32 *base, const VecFx32 *offset)
{
    VecFx32 result;
    VEC_Add(base, offset, &result);
    return result;
}

static inline QueryFilter MakeFilter(s32 category, s32 mask)
{
    QueryFilter result = {category, mask};
    return result;
}

u16 FieldObject_FindEscapeHeading_020a09b0(const SpawnOwner *owner)
{
    QueryWorkspace workspace;
    SweptShape shapeCopy;
    CollisionQuery queryCopy;
    SweptShape shape;
    CollisionQuery query;
    VecFx32 center;
    CollisionSphere sphere;
    VecFx32 originOffset;
    VecFx32 delta;
    QueryFilter filter;
    s32 bestAngle = 0;
    fx32 bestTime;
    int direction;

    originOffset = MakeVector(0, 0x1010, 0);
    center = AddVectors(&owner->body->center, &originOffset);
    bestTime = (s32)0x80000000;
    for (direction = 0; direction < 4; direction++) {
        u16 angle = (0xffff * direction) / 4 + 0xffff / 4;
        int index = angle >> 4;
        fx32 z = FX_Mul(gSinFx12Table[index], 0x5000);
        fx32 x = FX_Mul(gSinFx12Table[(0x400 - index) & 0xfff], 0x5000);
        CollisionResult *hit;

        delta = MakeVector(x, 0, z);
        MakeSphereShape(&shape.shape, &sphere, &center, 0x1000);
        shape.delta = delta;
        OffsetBoxByDelta(&shape.shape.bounds, &shape.sweptBounds, &shape.delta);
        shapeCopy = shape;
        filter = MakeFilter(0, 0x15);
        CollisionQuery_Init(&query, 0, owner->body->collisionBody, 2, 1, 1,
            &shapeCopy, &workspace, &filter);
        queryCopy = query;
        hit = SweepWorldCollision(&queryCopy);
        if (hit != 0) {
            if (bestTime < hit->nearestTime) {
                bestTime = hit->nearestTime;
                bestAngle = angle;
            }
        } else {
            bestAngle = angle;
            break;
        }
    }
    return FX_Atan2Idx(gSinFx12Table[(0x400 - (bestAngle >> 4)) & 0xfff],
        gSinFx12Table[bestAngle >> 4]);
}
