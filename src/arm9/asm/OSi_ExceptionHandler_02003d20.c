extern void OSi_GetAndDisplayContext_02003d94(void);
extern void *data_02056df0;

/* NitroSDK exception vector entry handler. */
asm void OSi_ExceptionHandler_02003d20(void)
{
    ldr r12, =data_02056df0
    ldr r12, [r12]
    cmp r12, #0
    movne lr, pc
    bxne r12
    ldr r12, =0x02000000
    stmfd r12!, {r0-r3, sp, lr}
    and r0, sp, #1
    mov sp, r12
    mrs r1, CPSR
    and r1, r1, #0x1f
    teq r1, #0x17
    bne @10
    bl OSi_GetAndDisplayContext_02003d94
    b @usr_return
@10:
    teq r1, #0x1b
    bne @usr_return
    bl OSi_GetAndDisplayContext_02003d94
@usr_return:
    ldr r12, =data_02056df0
    ldr r12, [r12]
    cmp r12, #0
@1:
    beq @1
@2:
    mov r0, r0
    b @2
    ldmfd sp!, {r0-r3, r12, lr}
    mov sp, r12
    bx lr
}
