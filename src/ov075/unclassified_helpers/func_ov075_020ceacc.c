#include "nitro/types.h"

typedef void (*MenuCallback)(void *work);

extern void func_ov077_020ce9ac(void *work, MenuCallback onUpdate, MenuCallback onEnter, MenuCallback onExit);
extern void func_ov077_020ce8e8(void *work);
extern void func_ov077_020ce5c4(void *work);
extern void func_ov077_020ce578(void *work);

int func_ov075_020ceacc(void *work)
{
    func_ov077_020ce9ac(work, func_ov077_020ce8e8, func_ov077_020ce5c4, func_ov077_020ce578);
    return 1;
}
