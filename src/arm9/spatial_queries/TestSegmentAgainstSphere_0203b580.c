#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct SegmentShapeRef SegmentShapeRef;

extern BOOL TestSphereAgainstSegment_0203f2e8(SphereShapeRef *sphereRef, SegmentShapeRef *segmentRef, void *hit, u32 flags);

BOOL TestSegmentAgainstSphere_0203b580(SegmentShapeRef *segmentRef, SphereShapeRef *sphereRef, void *hit, u32 flags)
{
    return TestSphereAgainstSegment_0203f2e8(sphereRef, segmentRef, hit, flags ^ 1);
}
