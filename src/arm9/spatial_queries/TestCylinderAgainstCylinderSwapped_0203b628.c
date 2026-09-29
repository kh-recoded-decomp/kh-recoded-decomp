#include "nitro/types.h"

typedef struct CylinderShapeRef CylinderShapeRef;

extern BOOL TestCylinderAgainstCylinder_020410a0(CylinderShapeRef *refA, CylinderShapeRef *refB, void *contact, u32 flags);

BOOL TestCylinderAgainstCylinderSwapped_0203b628(CylinderShapeRef *refA, CylinderShapeRef *refB, void *contact, u32 flags)
{
    return TestCylinderAgainstCylinder_020410a0(refB, refA, contact, flags ^ 1);
}
