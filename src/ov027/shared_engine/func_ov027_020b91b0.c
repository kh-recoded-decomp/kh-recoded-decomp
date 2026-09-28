#include "nitro/types.h"

extern void MI_CpuCopy8_01ff89a8(const void *src, void *dst, u32 size);

void func_ov027_020b91b0(void *unused, void *dst, const void *src) {
    MI_CpuCopy8_01ff89a8(src, (u8 *)dst + 0x34, 8);
}
