#include "nitro/types.h"

typedef struct CylinderShapeRef CylinderShapeRef;
typedef struct CollisionPolygon CollisionPolygon;

extern BOOL TestCylinderAgainstPolygon_0203c6bc(CylinderShapeRef *cylinderRef, CollisionPolygon **polygonRef, void *contact, u32 flags);

BOOL TestPolygonAgainstCylinder_0203b698(CollisionPolygon **polygonRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags)
{
    return TestCylinderAgainstPolygon_0203c6bc(cylinderRef, polygonRef, contact, flags ^ 1);
}
