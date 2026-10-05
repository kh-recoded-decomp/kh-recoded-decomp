typedef unsigned int u32;

asm u32 OS_GetProtectionRegion3_02003c58(void)
{
    mrc p15, 0, r0, c6, c3, 0
    bx lr
}
