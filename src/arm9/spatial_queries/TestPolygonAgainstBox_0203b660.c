#include "nitro/types.h"

typedef struct BoxShapeRef BoxShapeRef;
typedef struct PolygonShapeRef PolygonShapeRef;

extern BOOL TestBoxAgainstPolygon_02040024(BoxShapeRef *boxRef, PolygonShapeRef *polygonRef, void *contact, u32 flags);

BOOL TestPolygonAgainstBox_0203b660(PolygonShapeRef *polygonRef, BoxShapeRef *boxRef, void *contact, u32 flags)
{
    return TestBoxAgainstPolygon_02040024(boxRef, polygonRef, contact, flags ^ 1);
}
