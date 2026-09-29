#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EffectSlot {
    u16 groupId;
    u16 effectId;
    u32 handle;
} EffectSlot;

typedef struct EffectEntry {
    u8 flags;
    u8 slotId;
} EffectEntry;

typedef struct ActorBody {
    VecFx32 position;
    u8 pad_0c[0xe8];
    EffectEntry effects[8];
} ActorBody;

typedef struct EffectActor {
    u8 pad_000[0x2c0];
    ActorBody body;
} EffectActor;

extern EffectSlot *GetStageEntrySlot_0209c1fc(u32 id);
extern BOOL Effect_IsAlive_0204dc3c(u32 handle);
extern void Effect_SetPosition_0204db9c(u32 handle, VecFx32 *position);
extern void ReleaseActorEffect_02091ac0(EffectActor *actor, u16 groupId, u16 effectId, int mode);

void UpdateActorAttachedEffects_0208fb7c(EffectActor *actor)
{
    ActorBody *body = &actor->body;
    int i;

    for (i = 0; i < 8; i++) {
        EffectEntry *entry = &actor->body.effects[i];
        EffectSlot *slot;

        if (entry->slotId != 0) {
            slot = GetStageEntrySlot_0209c1fc(entry->slotId);
            if (slot != NULL) {
                if (Effect_IsAlive_0204dc3c(slot->handle)) {
                    if (entry->flags & 4) {
                        Effect_SetPosition_0204db9c(slot->handle, &body->position);
                    }
                } else {
                    ReleaseActorEffect_02091ac0(actor, slot->groupId, slot->effectId, 0);
                }
            }
        }
    }
}
