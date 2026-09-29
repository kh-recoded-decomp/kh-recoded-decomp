#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct PolygonShapeRef PolygonShapeRef;

extern BOOL TestSphereAgainstPolygon_0203fa38(SphereShapeRef *sphereRef, PolygonShapeRef *polygonRef, void *contact, u32 flags);

BOOL TestPolygonAgainstSphere_0203b644(PolygonShapeRef *polygonRef, SphereShapeRef *sphereRef, void *contact, u32 flags)
{
    return TestSphereAgainstPolygon_0203fa38(sphereRef, polygonRef, contact, flags ^ 1);
}
