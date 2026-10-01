#include "nitro/types.h"

typedef void (*MenuCallback)(void *work);

extern void func_ov077_020c77f0(void *work, MenuCallback onUpdate, MenuCallback onEnter, MenuCallback onExit);
extern void func_ov077_020c772c(void *work);
extern void func_ov077_020c7408(void *work);
extern void func_ov077_020c73bc(void *work);

int func_ov077_020c7910(void *work)
{
    func_ov077_020c77f0(work, func_ov077_020c772c, func_ov077_020c7408, func_ov077_020c73bc);
    return 1;
}
