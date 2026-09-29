#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct BoxShapeRef BoxShapeRef;

extern BOOL func_0203f09c(SphereShapeRef *sphereRef, BoxShapeRef *boxRef, void *contact, u32 flags);

BOOL TestBoxAgainstSphere_0203b548(BoxShapeRef *boxRef, SphereShapeRef *sphereRef, void *contact, u32 flags)
{
    return func_0203f09c(sphereRef, boxRef, contact, flags ^ 1);
}
