#include "nitro/types.h"

typedef struct BoxShapeRef BoxShapeRef;
typedef struct CapsuleShapeRef CapsuleShapeRef;

extern BOOL TestBoxAgainstCapsule_0203fde0(BoxShapeRef *boxRef, CapsuleShapeRef *capsuleRef, void *contact, u32 flags);

BOOL TestCapsuleAgainstBox_0203b59c(CapsuleShapeRef *capsuleRef, BoxShapeRef *boxRef, void *contact, u32 flags)
{
    return TestBoxAgainstCapsule_0203fde0(boxRef, capsuleRef, contact, flags ^ 1);
}
