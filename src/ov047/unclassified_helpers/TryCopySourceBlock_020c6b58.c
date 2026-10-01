#include "nitro/types.h"

extern u32 func_ov001_0207b3cc(void);
extern int CopySourceBlock_020b9f7c(void *dest);

BOOL TryCopySourceBlock_020c6b58(void *dest)
{
    BOOL canCopy;

    if (func_ov001_0207b3cc() == 1 || func_ov001_0207b3cc() == 0) {
        canCopy = TRUE;
    } else {
        canCopy = FALSE;
    }
    if (!canCopy) {
        return FALSE;
    }
    CopySourceBlock_020b9f7c(dest);
    return TRUE;
}
