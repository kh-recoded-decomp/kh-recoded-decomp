#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct CylinderShapeRef CylinderShapeRef;
typedef struct CollisionHit CollisionHit;

extern BOOL TestSphereAgainstCylinder_0203f658(SphereShapeRef *sphereRef, CylinderShapeRef *cylinderRef, CollisionHit *hit, u32 flags);

BOOL TestCylinderAgainstSphere_0203b5f0(CylinderShapeRef *cylinderRef, SphereShapeRef *sphereRef, CollisionHit *hit, u32 flags)
{
    return TestSphereAgainstCylinder_0203f658(sphereRef, cylinderRef, hit, flags ^ 1);
}
