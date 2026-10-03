#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef int (*StateQueryFunc)(Actor *actor);

typedef struct {
    u32 flags;
    VecFx32 hitPos;
    VecFx32 pos;
    u8 pad_1c[8];
    u32 state;
} HitSource;

struct Actor {
    u8 pad_0000[0x1dc];
    int guardState;
    u8 pad_01e0[0x22c - 0x1e0];
    StateQueryFunc getGuardState;
    u8 pad_0230[0x9ac - 0x230];
    u64 stateFlags;
    u8 player;
    u8 pad_09b5[0x9c0 - 0x9b5];
    int stageType;
    u8 pad_09c4[0x9e0 - 0x9c4];
    VecFx32 drift;
    u8 pad_09ec[0x9f8 - 0x9ec];
    int airTime;
    u8 pad_09fc[0x1104 - 0x9fc];
    int lockTarget;
};

extern BOOL AnySubObjectBit0Set_020cfb58(Actor *actor);
extern BOOL func_ov001_020645c8(u32 value);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);
extern VecFx32 *func_ov052_020ceb54(Actor *actor);
extern u16 GetLinkedAngleOffset_020ceb7c(Actor *actor);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(VecFx32 *src, VecFx32 *dst);
extern int FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern void AddSessionCounter_02063a80(int counter, int amount);
extern void DispatchAttackHitEvent_020c9e18(Actor *actor, HitSource *source);

BOOL TryCounterHit_020c9a1c(Actor *actor, HitSource *source)
{
    BOOL guarding = FALSE;
    int guardState;
    VecFx32 dir;

    if (source->flags & 2) {
        return FALSE;
    }
    if ((source->flags & 8) || (source->flags & 0x20)) {
        return FALSE;
    }
    if (actor->stateFlags & 0x10) {
        return FALSE;
    }
    if (actor->getGuardState != NULL) {
        guardState = actor->getGuardState(actor);
    } else {
        guardState = actor->guardState;
    }
    if (guardState == 3) {
        return FALSE;
    }
    if (!AnySubObjectBit0Set_020cfb58(actor) || func_ov001_020645c8(0x3520)
        || !IsPlayerEntryFlagSet_02050014(actor->player, 0xb)) {
        return FALSE;
    }
    if (IsPlayerEntryFlagSet_02050014(actor->player, 0x3d) && actor->stageType == 1) {
        guarding = TRUE;
    }
    if (!guarding && actor->stageType != 9) {
        return FALSE;
    }
    VEC_Subtract_01ff9e3c(&source->pos, func_ov052_020ceb54(actor), &dir);
    dir.y = 0;
    if ((dir.x != 0 || dir.y != 0 || dir.z != 0) && !IsPlayerEntryFlagSet_02050014(actor->player, 0x16)) {
        int angle;
        int diff;
        func_01ff9f88(&dir, &dir);
        angle = (u16)FixedPointAtan2_020062bc(-dir.x, -dir.z);
        diff = (u16)(GetLinkedAngleOffset_020ceb7c(actor) - angle);
        if (diff > 0x5000 && diff < 0xb000) {
            return FALSE;
        }
    } else {
        GetLinkedAngleOffset_020ceb7c(actor);
    }
    if (guarding) {
        actor->stateFlags |= 0x400000;
    }
    if (actor->airTime == 0 || actor->lockTarget < 0) {
        actor->stateFlags |= 8;
    }
    source->state |= 1;
    AddSessionCounter_02063a80(0x10, 1);
    actor->drift = source->hitPos;
    actor->airTime = 0x6000;
    DispatchAttackHitEvent_020c9e18(actor, source);
    return TRUE;
}
