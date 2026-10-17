#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollisionSegment;

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

typedef char CollisionSphereSizeCheck[sizeof(CollisionSphere) == 0x10 ? 1 : -1];
typedef char CollisionSegmentSizeCheck[sizeof(CollisionSegment) == 0x28 ? 1 : -1];
typedef char CollisionShapeSizeCheck[sizeof(CollisionShape) == 0x20 ? 1 : -1];
#define COLLISION_OFFSET_OF(type, member) ((u32)&((type *)0)->member)
typedef char SphereRadiusOffsetCheck[COLLISION_OFFSET_OF(CollisionSphere, radius) == 0x0c ? 1 : -1];
typedef char SegmentLengthOffsetCheck[COLLISION_OFFSET_OF(CollisionSegment, length) == 0x24 ? 1 : -1];
typedef char ContactFeatureOffsetCheck[COLLISION_OFFSET_OF(SweepContact, feature) == 0x14 ? 1 : -1];
#undef COLLISION_OFFSET_OF

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_NormalizeLength(const VecFx32 *src, VecFx32 *out);
extern BOOL TestSegmentAgainstSphere(const CollisionShape *segmentRef, const CollisionShape *sphereRef,
                                    SweepContact *contact, u32 flags);

BOOL SweepSphereAgainstSphere(const CollisionShape *first, const CollisionShape *second,
                            SweepContact *contact, u32 flags, const VecFx32 *velocity)
{
    CollisionShape segmentRef;
    CollisionShape sphereRef;
    CollisionSegment segment;
    CollisionSphere expanded;
    VecFx32 end;
    VecFx32 direction;
    const CollisionSphere *firstSphere = first->data;
    const CollisionSphere *secondSphere = second->data;

    /* Reduce the swept sphere to its center's path against the combined radius. */
    segment.start = firstSphere->center;
    VEC_Add(&segment.start, velocity, &end);
    segment.end = end;
    VEC_Subtract(&segment.end, &segment.start, &direction);
    segment.direction = direction;
    segment.length = VEC_NormalizeLength(&segment.direction, &segment.direction);
    expanded = *secondSphere;
    expanded.radius += firstSphere->radius;
    segmentRef.data = &segment;
    sphereRef.data = &expanded;
    if (TestSegmentAgainstSphere(&segmentRef, &sphereRef, contact, flags | 0x10)) {
        if (contact != NULL) {
            contact->feature = 3;
        }
        return TRUE;
    }
    return FALSE;
}
