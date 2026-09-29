#include "nitro/types.h"

typedef struct SegmentShapeRef SegmentShapeRef;
typedef struct CylinderShapeRef CylinderShapeRef;

extern void TestSegmentAgainstCylinder_02040548(SegmentShapeRef *segmentRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags);

void TestCylinderAgainstSegment_0203b5d4(CylinderShapeRef *cylinderRef, SegmentShapeRef *segmentRef, void *contact, u32 flags)
{
    TestSegmentAgainstCylinder_02040548(segmentRef, cylinderRef, contact, flags ^ 1);
}
