#include "nitro/types.h"

typedef struct CollisionBody CollisionBody;
typedef struct CollisionHit CollisionHit;

extern BOOL TestCapsuleAgainstCapsule_020405b4(CollisionBody *bodyA, CollisionBody *bodyB, CollisionHit *hit, u32 flags);

BOOL TestCapsuleAgainstCapsuleSwapped_0203b60c(CollisionBody *bodyA, CollisionBody *bodyB, CollisionHit *hit, u32 flags)
{
    return TestCapsuleAgainstCapsule_020405b4(bodyB, bodyA, hit, flags ^ 1);
}
