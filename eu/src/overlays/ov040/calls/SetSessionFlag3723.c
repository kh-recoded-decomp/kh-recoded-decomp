asm void SetSessionFlag3723(void)
{
    ldr r0, [pc, #4]
    ldr r3, [pc, #8]
    bx r3
    nop
    DCD 0x3723
    DCD 0x020645dd
}
