#include "nitro/types.h"

typedef struct SphereShapeRef SphereShapeRef;
typedef struct CapsuleShapeRef CapsuleShapeRef;

extern BOOL func_0203f610(SphereShapeRef *sphereRef, CapsuleShapeRef *capsuleRef, void *hit, u32 flags);

BOOL TestCapsuleAgainstSphere_0203b5b8(CapsuleShapeRef *capsuleRef, SphereShapeRef *sphereRef, void *hit, u32 flags)
{
    return func_0203f610(sphereRef, capsuleRef, hit, flags ^ 1);
}
