#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor {
    u8 pad_000[0x9bc];
    void *pendingEffect;
    s32 pendingEffectKind;
    u8 pad_9c4[0x1730 - 0x9c4];
    s32 effectCooldown;
    void *effectHandle;
} Actor;

extern u32 random_next_scaled_0202aa04(u32 upperBound);
extern VecFx32 *Actor_GetModelPosition_020cd0d8(Actor *actor);
extern void *func_0204da8c(int effectId, BOOL mirrored, VecFx32 *position, int flags);

void Actor_TrySpawnIdleEffect_020c7a70(Actor *actor)
{
    if (actor->effectCooldown == 0 && actor->pendingEffect == NULL) {
        u32 roll = random_next_scaled_0202aa04(2);
        actor->effectHandle = func_0204da8c(0x30, roll == 0, Actor_GetModelPosition_020cd0d8(actor), 0);
        actor->pendingEffect = &actor->effectHandle;
        actor->pendingEffectKind = 0x30;
        actor->effectCooldown = 0x1e000;
    }
}
