#include "nitro/types.h"

/* Bound start and halfword keep the original registers. */
register u16 *sCopyStart __asm("r12");
register u32 sHalfword __asm("r2");

__attribute__((optimize("Os", "no-move-loop-invariants", "no-expensive-optimizations")))
void MIi_CpuCopy16Backward(const void *source, void *destination, u32 size)
{
    const u16 *from = (const u16 *)((const u8 *)source + size);
    u32 to;

    sCopyStart = destination;
    to = (u32)destination + size;
    while (__atomic_signal_fence(__ATOMIC_SEQ_CST), (s32)sCopyStart < (s32)to) {
        sHalfword = *--from;
        to -= sizeof(u16);
        *(u16 *)to = sHalfword;
    }
    __atomic_signal_fence(__ATOMIC_SEQ_CST);
}
