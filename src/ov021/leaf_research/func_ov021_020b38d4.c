#include "nitro/types.h"

extern u32 func_ov001_0209cb64();
extern u32 func_ov021_020b0374();

/* Leaf script command triggers a sound effect. */
u32 func_ov021_020b38d4(u32 context, s32 operands)
{
    s32 idOperand;

    idOperand = func_ov021_020b0374();
    func_ov021_020b0374(context, operands + 8);
    func_ov001_0209cb64(1, *(u32 *)(idOperand + 4));
    return 0;
}
