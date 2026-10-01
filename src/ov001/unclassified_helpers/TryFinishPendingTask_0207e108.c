#include "nitro/types.h"

extern int data_ov001_020a04d0;
extern BOOL func_ov001_0207e094(void);
extern void func_ov001_0207d6f4(void);

BOOL TryFinishPendingTask_0207e108(void)
{
    BOOL finished = FALSE;

    if (data_ov001_020a04d0 == 0) {
        return finished;
    }
    if (func_ov001_0207e094()) {
        func_ov001_0207d6f4();
        finished = TRUE;
    }
    return finished;
}
