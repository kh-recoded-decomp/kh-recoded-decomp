#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct CollisionCylinder {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
    fx32 radius;
} CollisionCylinder;

typedef struct CylinderShapeRef {
    CollisionCylinder *cylinder;
    u8 pad_04[0x18];
    s32 kind;
} CylinderShapeRef;

typedef struct SphereShapeRef {
    CollisionSphere *sphere;
    u8 pad_04[0x18];
    s32 kind;
} SphereShapeRef;

extern BOOL AreVecsWithinRange16_0204a8f4(const VecFx32 *a, const VecFx32 *b);
extern BOOL TestSegmentAgainstCylinder_02040ca4(CylinderShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags);
extern void GetSegmentDelta_0203ffcc(VecFx32 *out, const CollisionCylinder *segment);
extern BOOL SweepSphereAgainstCylinder_02042678(SphereShapeRef *sphereRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags, const VecFx32 *velocity);

void TestCapsuleAgainstCylinder_02040548(CylinderShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags)
{
    CollisionCylinder *segment = segmentRef->cylinder;
    CollisionCylinder *cylinder = cylinderRef->cylinder;
    VecFx32 velocity;
    SphereShapeRef sphereRef;
    CollisionSphere sphere;

    if ((flags & 2) || (flags & 1) || AreVecsWithinRange16_0204a8f4(&segment->start, &segment->end)) {
        TestSegmentAgainstCylinder_02040ca4(segmentRef, cylinderRef, contact, flags);
        return;
    }
    sphereRef.sphere = &sphere;
    sphere.center = segment->start;
    sphere.radius = cylinder->radius;
    GetSegmentDelta_0203ffcc(&velocity, segment);
    SweepSphereAgainstCylinder_02042678(&sphereRef, cylinderRef, contact, flags, &velocity);
}
