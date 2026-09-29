#include "nitro/types.h"

typedef struct BoxShapeRef BoxShapeRef;
typedef struct CylinderShapeRef CylinderShapeRef;

extern BOOL TestBoxAgainstCylinder_0203b704(BoxShapeRef *boxRef, CylinderShapeRef *cylinderRef, void *contact, u32 flags);

BOOL TestCylinderAgainstBox_0203b564(CylinderShapeRef *cylinderRef, BoxShapeRef *boxRef, void *contact, u32 flags)
{
    return TestBoxAgainstCylinder_0203b704(boxRef, cylinderRef, contact, flags ^ 1);
}
