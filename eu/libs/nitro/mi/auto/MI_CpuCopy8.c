#include "nitro/types.h"

/* Source and destination stay bound to r0 and r1. */
register u32 sSource __asm("r0");
register u32 sDestination __asm("r1");
register u32 sScratch __asm("r12");

void MI_CpuCopy8(const void *source, void *destination, u32 size)
{
    u32 minimum = 2;
    u32 carry;
    u32 chunk;

    if (size == 0)
        return;
    if (sDestination & 1)
    {
        sScratch = *(vu16 *)(sDestination - 1) & 0xff;
        if (sSource & 1)
            carry = *(vu16 *)(sSource - 1) >> 8;
        else
            carry = *(vu16 *)sSource;
        *(u16 *)(sDestination - 1) = sScratch | (carry << 8);
        sSource++;
        sDestination++;
        if (--size == 0)
            return;
    }
    sScratch = sSource ^ sDestination;
    if (sScratch & 1)
    {
        u32 remaining = size;

        sSource &= ~1;
        sScratch = *(vu16 *)sSource;
        sSource += 2;
        carry = sScratch >> 8;
        while (!__builtin_sub_overflow(remaining, 2, &remaining))
        {
            sScratch = carry | (*(vu16 *)sSource << 8);
            sSource += 2;
            *(u16 *)sDestination = sScratch;
            sDestination += 2;
            carry = sScratch >> 16;
        }
        if (remaining & 1)
        {
            __atomic_signal_fence(__ATOMIC_SEQ_CST);
            sScratch = (*(vu16 *)sDestination & 0xff00) | carry;
            *(u16 *)sDestination = sScratch;
        }
        return;
    }
    if (sScratch & 2)
    {
        chunk = size & ~1;
        if (chunk != 0)
        {
            size -= chunk;
            sScratch = chunk + sDestination;
            do
            {
                *(u16 *)sDestination = *(u16 *)sSource;
                sSource += 2;
                sDestination += 2;
            } while (sDestination < sScratch);
        }
    }
    else if (size >= minimum)
    {
        if (sDestination & 2)
        {
            *(u16 *)sDestination = *(u16 *)sSource;
            sSource += 2;
            sDestination += 2;
            size -= 2;
            if (size == 0)
                return;
        }
        chunk = size & ~3;
        if (chunk != 0)
        {
            size -= chunk;
            sScratch = chunk + sDestination;
            do
            {
                *(u32 *)sDestination = *(u32 *)sSource;
                sSource += 4;
                sDestination += 4;
            } while (sDestination < sScratch);
        }
        if (size & 2)
        {
            *(u16 *)sDestination = *(u16 *)sSource;
            sSource += 2;
            sDestination += 2;
        }
    }
    if (size & 1)
    {
        __atomic_signal_fence(__ATOMIC_SEQ_CST);
        register u32 kept __asm("r2");
        kept = *(vu16 *)sDestination;
        sSource = *(vu16 *)sSource;
        kept &= 0xff00;
        sSource &= 0xff;
        sSource = sSource | kept;
        *(u16 *)sDestination = sSource;
    }
}
