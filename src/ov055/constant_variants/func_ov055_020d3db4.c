#include "nitro/types.h"

typedef struct Actor Actor;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_ov059_020d3734(Actor *actor, void *param);
extern void func_ov059_020ccae8(Actor *actor);

#define g_actorInstance (*(Actor **)34422528)

Actor *func_ov055_020d3db4(void *param)
{
    Actor *actor = NNSi_FndAllocFromDefaultHeap_0202a178(4756);
    g_actorInstance = actor;
    func_ov059_020d3734(actor, param);
    func_ov059_020ccae8(actor);
    return actor;
}
