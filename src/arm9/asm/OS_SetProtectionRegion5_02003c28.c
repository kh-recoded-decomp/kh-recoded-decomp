typedef unsigned int u32;

asm void OS_SetProtectionRegion5_02003c28(u32 parameter)
{
    mcr p15, 0, r0, c6, c5, 0
    bx lr
}
