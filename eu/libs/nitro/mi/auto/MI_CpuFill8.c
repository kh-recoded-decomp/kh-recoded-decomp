#include "nitro/types.h"

/* The fill value argument stays bound to r1. */
register u32 sFill __asm("r1");
register u32 sScratch __asm("r12");

void MI_CpuFill8(void *destination, u32 value, u32 size)
{
    u32 address = (u32)destination;
    u32 minimum = 2;
    u32 wordBytes;

    if (size == 0)
        return;
    if (address & 1)
    {
        sScratch = *(vu16 *)(address - 1) & 0xff;
        *(u16 *)(address - 1) = sScratch | (sFill << 8);
        address++;
        if (--size == 0)
            return;
    }
    if (size >= minimum)
    {
        sFill |= sFill << 8;
        if (address & 2)
        {
            *(u16 *)address = sFill;
            address += 2;
            size -= 2;
            if (size == 0)
                return;
        }
        sFill |= sFill << 16;
        wordBytes = size & ~3;
        if (wordBytes != 0)
        {
            size -= wordBytes;
            sScratch = address + wordBytes;
            do
            {
                *(u32 *)address = sFill;
                address += 4;
            } while (address < sScratch);
        }
        if (size & 2)
        {
            *(u16 *)address = sFill;
            address += 2;
        }
    }
    if (size & 1)
    {
        __atomic_signal_fence(__ATOMIC_SEQ_CST);
        register u32 kept __asm("r3");
        kept = *(vu16 *)address & 0xff00;
        sFill &= 0xff;
        sFill = kept | sFill;
        *(u16 *)address = sFill;
    }
}
