#include "nitro/types.h"

typedef struct StageActor StageActor;

typedef struct ActorLink {
    u8 pad_00[0x10];
    s16 actorId;
} ActorLink;

extern StageActor *GetStageActor_0209c040(int id);
extern void func_ov001_02091ac0(StageActor *actor, int first, int second, int flags);

void ResetLinkedActorMotion_02097a64(ActorLink *link)
{
    StageActor *actor = GetStageActor_0209c040(link->actorId);

    if (actor != NULL) {
        func_ov001_02091ac0(actor, 0xffff, 0xffff, 0);
    }
}
