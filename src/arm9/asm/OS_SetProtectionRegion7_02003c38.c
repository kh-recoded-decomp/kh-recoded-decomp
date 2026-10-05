typedef unsigned int u32;

asm void OS_SetProtectionRegion7_02003c38(u32 parameter)
{
    mcr p15, 0, r0, c6, c7, 0
    bx lr
}
