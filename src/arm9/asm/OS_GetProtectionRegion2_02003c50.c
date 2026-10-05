typedef unsigned int u32;

asm u32 OS_GetProtectionRegion2_02003c50(void)
{
    mrc p15, 0, r0, c6, c2, 0
    bx lr
}
