asm void OS_SpinWaitCpuCycles_020049a8(register unsigned int cycles)
{
loop:
    subs r0, r0, #4
    bhs loop
    bx lr
}
