#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    void *geometry;
    VecFx32 boxMax;
    VecFx32 boxMin;
    s32 kind;
} CollShape;

typedef struct {
    VecFx32 center;
    fx32 radius;
} CollSphere;

typedef struct {
    u8 pad_000[0x928];
    u64 flags;
    u8 pad_930[0xea0 - 0x930];
    CollSphere hitSphere;
} Actor;

extern void Actor_GetRotatedJointPosition_020c895c(VecFx32 *out, Actor *actor);
extern CollShape MakeSphereShape_0203ad14(CollSphere *sphere, const VecFx32 *center, fx32 radius);

BOOL Actor_BuildJointHitSphere_020c90c8(Actor *actor, CollShape *out)
{
    if (actor->flags & 0x20) {
        return FALSE;
    } else {
        VecFx32 center;
        VecFx32 joint;
        Actor_GetRotatedJointPosition_020c895c(&joint, actor);
        center = joint;
        *out = MakeSphereShape_0203ad14(&actor->hitSphere, &center, 0x4cd);
        return TRUE;
    }
}
