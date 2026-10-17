#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionCapsule {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCapsule;

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct SweepContact {
    fx32 depth;
    VecFx32 normal;
    fx32 time;
    u8 feature;
} SweepContact;

typedef char CollisionCapsuleSizeCheck[sizeof(CollisionCapsule) == 0x2c ? 1 : -1];
typedef char CollisionShapeSizeCheck[sizeof(CollisionShape) == 0x20 ? 1 : -1];
#define COLLISION_OFFSET_OF(type, member) ((u32)&((type *)0)->member)
typedef char CapsuleRadiusOffsetCheck[COLLISION_OFFSET_OF(CollisionCapsule, radius) == 0x28 ? 1 : -1];
typedef char ShapeKindOffsetCheck[COLLISION_OFFSET_OF(CollisionShape, kind) == 0x1c ? 1 : -1];
typedef char ContactFeatureOffsetCheck[COLLISION_OFFSET_OF(SweepContact, feature) == 0x14 ? 1 : -1];
#undef COLLISION_OFFSET_OF

extern BOOL SweepSegmentAgainstCylinder(const CollisionShape *segmentShape, const CollisionShape *cylinderShape,
                                       SweepContact *contact, u32 flags, const VecFx32 *velocity);

BOOL SweepCapsuleAgainstCapsule(const CollisionShape *first, const CollisionShape *second,
                              SweepContact *contact, u32 flags, const VecFx32 *velocity)
{
    const CollisionCapsule *firstCapsule = first->data;
    CollisionCapsule expanded = *(CollisionCapsule *)second->data;
    CollisionShape expandedRef;

    /* Sweep the first capsule's axis against the second with both radii combined. */
    expandedRef.data = &expanded;
    expandedRef.kind = 3;
    expanded.radius += firstCapsule->radius;
    if (SweepSegmentAgainstCylinder(first, &expandedRef, contact, flags, velocity)) {
        if (contact->feature & 2) {
            contact->feature = 3;
        }
        return TRUE;
    }
    return FALSE;
}
