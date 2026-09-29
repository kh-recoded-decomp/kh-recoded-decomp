#include "nitro/types.h"

typedef struct Actor Actor;

extern void func_ov059_020cd078(Actor *actor, BOOL enable);
extern void func_ov059_020cccec(Actor *actor, int mode, BOOL flag);

void Actor_ResetMotion_020c7960(Actor *actor, int mode, BOOL flag)
{
    if (mode == 2 && flag != FALSE) {
        func_ov059_020cd078(actor, FALSE);
    }
    func_ov059_020cccec(actor, mode, flag);
}
