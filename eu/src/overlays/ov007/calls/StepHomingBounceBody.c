#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 unk_00;
    s16 blend;
    VecFx32 position;
    VecFx32 velocity;
    int blendCopy;
} BounceBody;

typedef struct {
    u8 pad_00[0x58];
    VecFx32 position;
} BounceOwner;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_MultAdd(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern BOOL func_ov007_020a09ac(BounceOwner *owner, const VecFx32 *position, const VecFx32 *velocity, VecFx32 *hit);
extern BOOL DampBounceVelocity(BounceOwner *owner, BounceBody *body);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 result;
    result.x = x;
    result.y = y;
    result.z = z;
    return result;
}

BOOL StepHomingBounceBody(BounceOwner *owner, BounceBody *body)
{
    VecFx32 hit;
    VecFx32 target;
    VecFx32 diff;
    VecFx32 blended;
    VecFx32 fall;
    fx32 y;
    fx32 fallSpeed;

    body->blend += 0xaa;
    if (body->blend > 0x1000) {
        body->blend = 0x1000;
    }
    body->blendCopy = body->blend;
    target = MakeVec(body->velocity.x, 0, body->velocity.z);
    VEC_Subtract(&owner->position, &target, &diff);
    VEC_MultAdd(body->blend, &diff, &target, &blended);
    body->position.x = blended.x;
    body->position.z = blended.z;
    fallSpeed = body->velocity.y;
    if (fallSpeed != 0) {
        fall = MakeVec(0, fallSpeed, 0);
        if (fallSpeed < 0 && func_ov007_020a09ac(owner, &body->position, &fall, &hit)) {
            if (DampBounceVelocity(owner, body)) {
                body->velocity.y += 0x7b;
            }
            y = hit.y;
        } else {
            y = body->position.y + body->velocity.y;
        }
        body->position.y = y;
    }
    return body->blend == 0x1000 && body->velocity.y == 0;
}
