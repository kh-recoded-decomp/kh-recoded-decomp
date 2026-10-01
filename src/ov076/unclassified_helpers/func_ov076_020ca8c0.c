#include "nitro/types.h"

typedef void (*MenuCallback)(void *work);

extern void func_ov077_020ca7bc(void *work, MenuCallback onUpdate, MenuCallback onEnter, MenuCallback onExit);
extern void func_ov077_020ca398(void *work);
extern void func_ov077_020ca250(void *work);
extern void func_ov077_020ca388(void *work);

int func_ov076_020ca8c0(void *work)
{
    func_ov077_020ca7bc(work, func_ov077_020ca398, func_ov077_020ca250, func_ov077_020ca388);
    return 1;
}
