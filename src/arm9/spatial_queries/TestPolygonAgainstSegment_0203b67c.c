#include "nitro/types.h"

typedef struct CollisionSegment CollisionSegment;
typedef struct CollisionPolygon CollisionPolygon;
typedef struct CollisionContact CollisionContact;

extern BOOL TestSegmentAgainstPolygon_0203c258(CollisionSegment **segmentRef, CollisionPolygon **polygonRef, CollisionContact *contact, u32 flags);

BOOL TestPolygonAgainstSegment_0203b67c(CollisionPolygon **polygonRef, CollisionSegment **segmentRef, CollisionContact *contact, u32 flags)
{
    return TestSegmentAgainstPolygon_0203c258(segmentRef, polygonRef, contact, flags ^ 1);
}
