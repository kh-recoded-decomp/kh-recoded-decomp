/* NitroSDK original assembly (libraries/os/src/os_terminate_proc.c). */

typedef int BOOL;
typedef unsigned int u32;

asm void OS_Halt_02004d30(void)
{
    mov r0, #0
    mcr p15, 0, r0, c7, c0, 4
    bx lr
}
