#include "nitro/types.h"

extern u8 *func_ov032_020bbbd4(void *param0, s32 param1);

s32 func_ov032_020bbbfc(void *param0, s32 param1) {
    u8 *entry = func_ov032_020bbbd4(param0, param1);
    return (s32)(s16)*(u32 *)(entry + 0xc);
}
