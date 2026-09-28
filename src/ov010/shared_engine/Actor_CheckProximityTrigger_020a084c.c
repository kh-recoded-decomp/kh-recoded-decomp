#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x40];
    VecFx32 pos;
} Actor;

extern VecFx32 *func_ov001_0206dc4c(int arg);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern void func_ov001_0207f9c8(Actor *actor, int flag);

BOOL Actor_CheckProximityTrigger_020a084c(Actor *actor)
{
    VecFx32 *target = func_ov001_0206dc4c(0);

    if (actor->pos.y <= target->y) {
        target = func_ov001_0206dc4c(0);
        if (func_01ffa0f4(&actor->pos, target) < 0x3000) {
            func_ov001_0207f9c8(actor, 1);
        }
    }
    return FALSE;
}
