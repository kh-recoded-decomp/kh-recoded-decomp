#include "nitro/types.h"

extern u32 func_ov001_02063838(void);
extern BOOL func_ov001_0208883c(void);
extern s32 func_ov001_02063a38(void);
extern BOOL func_ov036_020bc648(void);

BOOL func_020284e8(void)
{
    if (func_ov001_02063838() != 0 && func_ov001_0208883c() != 0) {
        return TRUE;
    }
    if (func_ov001_02063a38() == 8 && func_ov036_020bc648() != 0) {
        return TRUE;
    }
    return FALSE;
}
