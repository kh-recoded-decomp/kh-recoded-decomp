#include "nitro/types.h"

extern void MI_CpuCopy16_01ff869c(const void *src, void *dest, u32 size);
extern void MIi_CpuCopy16Backward_01ff86b8(const void *src, void *dest, u32 size);

void MI_CpuMove16_01ff86d8(const void *src, void *dest, u32 size) {
    if ((u32)dest <= (u32)src || (u32)src + size <= (u32)dest) {
        MI_CpuCopy16_01ff869c(src, dest, size);
    } else {
        MIi_CpuCopy16Backward_01ff86b8(src, dest, size);
    }
}
