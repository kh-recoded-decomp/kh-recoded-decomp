extern void OSi_SetExContext_02003da8(void);
extern void func_02003e3c_02003e28(void);

asm void OSi_GetAndDisplayContext_02003d94(void)
{
    stmdb sp!, {r0, lr}
    bl OSi_SetExContext_02003da8
    bl func_02003e3c_02003e28
    ldmia sp!, {r0, lr}
    bx lr
}
