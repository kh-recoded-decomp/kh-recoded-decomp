typedef unsigned int u32;

asm u32 OS_GetProtectionRegion6_02003c70(void)
{
    mrc p15, 0, r0, c6, c6, 0
    bx lr
}
