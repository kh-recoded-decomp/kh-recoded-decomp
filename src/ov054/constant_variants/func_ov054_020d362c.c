#include "nitro/types.h"

typedef struct Actor Actor;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_ov059_020d21f4(Actor *actor, void *param);
extern void func_ov059_020ccae8(Actor *actor);

#define g_actorInstance (*(Actor **)34420480)

Actor *func_ov054_020d362c(void *param)
{
    Actor *actor = NNSi_FndAllocFromDefaultHeap_0202a178(4744);
    g_actorInstance = actor;
    func_ov059_020d21f4(actor, param);
    func_ov059_020ccae8(actor);
    return actor;
}
