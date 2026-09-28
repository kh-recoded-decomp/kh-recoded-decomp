#include "nitro/types.h"

extern u8 *func_ov032_020bbbd4(void *param0, s32 param1);
extern void func_ov032_020bbe84(void *dst, s32 count);

void func_ov032_020bbf20(void *param0, s32 param1) {
    u8 *entry = func_ov032_020bbbd4(param0, param1);
    func_ov032_020bbe84(entry + 0x1b, 4);
}
