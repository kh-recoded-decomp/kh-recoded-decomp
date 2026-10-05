extern void OSi_ArrangeTimer_0200443c(void);

asm void OSi_AlarmHandler_0200442c(void)
{
    stmdb sp!, {r0, lr}
    bl OSi_ArrangeTimer_0200443c
    ldmia sp!, {r0, lr}
    bx lr
}
