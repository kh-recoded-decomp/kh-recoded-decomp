#include "nitro/types.h"

typedef void (*MenuCallback)(void *work);

extern void func_ov077_020c77f0(void *work, MenuCallback onUpdate, MenuCallback onEnter, MenuCallback onExit);
extern void func_ov077_020c73cc(void *work);
extern void func_ov077_020c7284(void *work);
extern void func_ov077_020c73bc(void *work);

int func_ov077_020c78f4(void *work)
{
    func_ov077_020c77f0(work, func_ov077_020c73cc, func_ov077_020c7284, func_ov077_020c73bc);
    return 1;
}
