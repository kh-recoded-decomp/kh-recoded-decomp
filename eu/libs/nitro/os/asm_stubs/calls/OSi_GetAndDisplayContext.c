extern void OSi_SetExContext(void);
extern void OSi_DisplayExContext(void);

asm void OSi_GetAndDisplayContext(void)
{
    stmdb sp!, {r0, lr}
    bl OSi_SetExContext
    bl OSi_DisplayExContext
    ldmia sp!, {r0, lr}
    bx lr
}
