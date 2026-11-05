#include "nitro/types.h"

extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

void SetWidgetBasePosition(void *unused, void *dst, const void *src) {
    MI_CpuCopy8(src, (u8 *)dst + 0x34, 8);
}
