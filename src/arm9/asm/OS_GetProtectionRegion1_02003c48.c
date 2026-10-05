typedef unsigned int u32;

asm u32 OS_GetProtectionRegion1_02003c48(void)
{
    mrc p15, 0, r0, c6, c1, 0
    bx lr
}
