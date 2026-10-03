#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 flags;
    u8 pad_04[0x0c];
    VecFx32 position;
} AttackTarget;

typedef struct {
    u8 pad_000[0x9ac];
    u64 stateFlags;
    u8 player;
    u8 pad_9b5[0x9c0 - 0x9b5];
    int mode;
} AttackActor;

extern s16 data_0205356c[];
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern VecFx32 *func_ov052_020ceb54(AttackActor *actor);
extern u16 GetLinkedAngleOffset_020ceb7c(AttackActor *actor);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *v, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);

BOOL TryFlagTargetBehind_020c9bdc(AttackActor *actor, AttackTarget *target)
{
    VecFx32 dir;
    VecFx32 forward;
    int index;

    if (actor->mode != 1) {
        return FALSE;
    }
    if (!IsPlayerEntryFlagSet_02050014(actor->player, 10)) {
        return FALSE;
    }
    if (!IsPlayerEntryFlagSet_02050014(actor->player, 0x55)) {
        return FALSE;
    }
    if (target->flags & 2) {
        return FALSE;
    }
    VEC_Subtract_01ff9e3c(&target->position, func_ov052_020ceb54(actor), &dir);
    forward.x = forward.y = forward.z = dir.y = 0;
    if (dir.x != 0 || dir.y != 0 || dir.z != 0) {
        func_01ff9f88(&dir, &dir);
        index = GetLinkedAngleOffset_020ceb7c(actor) >> 4;
        forward.x = -data_0205356c[index];
        forward.z = -data_0205356c[(0x400 - index) & 0xfff];
        if (VEC_DotProduct_01ff9e6c(&dir, &forward) > 0) {
            return FALSE;
        }
    }
    actor->stateFlags |= 0x80;
    return TRUE;
}
