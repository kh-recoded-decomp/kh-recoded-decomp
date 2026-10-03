#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 unk_00;
    VecFx32 position;
    VecFx32 velocity;
} BounceBody;

extern const VecFx32 data_02053438;

extern BOOL func_ov007_020a098c(void *owner, const VecFx32 *position, const VecFx32 *velocity, VecFx32 *hit);
extern BOOL DampBounceVelocity_020a0abc(void *owner, BounceBody *body);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

BOOL StepBounceBody_020a0afc(void *owner, BounceBody *body) {
    VecFx32 hit;

    if (func_ov007_020a098c(owner, &body->position, &body->velocity, &hit)) {
        body->position = hit;
        if (!DampBounceVelocity_020a0abc(owner, body)) {
            body->velocity = data_02053438;
            return FALSE;
        }
    } else {
        VEC_Add_01ff9e0c(&body->position, &body->velocity, &body->position);
    }
    return TRUE;
}
