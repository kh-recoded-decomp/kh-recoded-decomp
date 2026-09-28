#include "nitro/types.h"

extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL func_ov001_020728c4(void);
extern void func_ov001_02075f5c(void *menu, s32 arg);
extern void func_ov001_02076008(void *menu, s32 arg);

void func_ov001_020761a4(void *menu, s32 arg)
{
    if (!IsModeSetOrFlag370aClear_0207259c() || IsHudFlag7Set_020725bc() || func_ov001_020728c4()) {
        func_ov001_02075f5c(menu, arg);
    } else {
        func_ov001_02076008(menu, arg);
    }
}
