#include "nitro/types.h"

typedef struct Actor Actor;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_ov059_020c7474(Actor *actor, void *param);
extern void func_ov059_020cba3c(Actor *actor);

#define g_actorInstance (*(Actor **)0x020cffa0)

Actor *CreateActorInstance_020c7a48(void *param)
{
    Actor *actor = NNSi_FndAllocFromDefaultHeap_0202a178(0x1830);
    g_actorInstance = actor;
    func_ov059_020c7474(actor, param);
    func_ov059_020cba3c(actor);
    return actor;
}
