extern int data_0205fdbc;

/* Runtime double square root with errno on domain error. */
asm double sqrt_0202426c(double x)
{
    stmfd sp!, {r4-r6, lr}
    ldr r2, =0x7ff00000
    cmp r1, r2
    bhs @special
    movs r12, r1, lsr #20
    beq @denormal
    bic r1, r1, r2
    orr r1, r1, #0x100000
@normal:
    movs r12, r12, asr #1
    bhs @even
    sub r12, r12, #1
    movs r0, r0, lsl #1
    adc r1, r1, r1
@even:
    movs r3, r0, lsl #1
    adc r1, r1, r1
    mov r2, #0
    mov r4, #0
    mov lr, #0x200000
@high_loop:
    add r6, r4, lr
    cmp r6, r1
    addle r4, r6, lr
    suble r1, r1, r6
    addle r2, r2, lr
    movs r3, r3, lsl #1
    adc r1, r1, r1
    movs lr, lr, lsr #1
    bne @high_loop
    mov r0, #0
    mov r5, #0
    cmp r1, r4
    cmpeq r3, #0x80000000
    blo @low_start
    subs r3, r3, #0x80000000
    sbc r1, r1, r4
    add r4, r4, #1
    mov r0, #0x80000000
@low_start:
    movs r3, r3, lsl #1
    adc r1, r1, r1
    mov lr, #0x40000000
@low_loop:
    add r6, r5, lr
    cmp r4, r1
    cmpeq r6, r3
    bhi @low_skip
    add r5, r6, lr
    subs r3, r3, r6
    sbc r1, r1, r4
    add r0, r0, lr
@low_skip:
    movs r3, r3, lsl #1
    adc r1, r1, r1
    movs lr, lr, lsr #1
    bne @low_loop
    orrs r1, r1, r3
    biceq r0, r0, #1
    movs r1, r2, lsr #1
    movs r0, r0, rrx
    adcs r0, r0, #0
    adc r1, r1, #0
    add r1, r1, #0x20000000
    sub r1, r1, #0x100000
    add r1, r1, r12, lsl #20
    ldmfd sp!, {r4-r6, lr}
    bx lr
@denormal:
    cmp r1, #0
    bne @denormal_high
    cmp r0, #0
    ldmeqfd sp!, {r4-r6, lr}
    bxeq lr
    mvn r12, #0x13
    clz r5, r0
    movs r0, r0, lsl r5
    sub r12, r12, r5
    mov r1, r0, lsr #11
    mov r0, r0, lsl #21
    b @normal
@denormal_high:
    clz r2, r1
    movs r1, r1, lsl r2
    rsb r2, r2, #0x2b
    mov r1, r1, lsr #11
    orr r1, r1, r0, lsr r2
    rsb r2, r2, #0x20
    mov r0, r0, lsl r2
    rsb r12, r2, #1
    b @normal
@special:
    tst r1, #0x80000000
    beq @positive_special
    bics r3, r1, #0x80000000
    cmpeq r0, #0
    ldmeqfd sp!, {r4-r6, lr}
    bxeq lr
    b @domain_error
@positive_special:
    orrs r2, r0, r1, lsl #12
    ldmeqfd sp!, {r4-r6, lr}
    bxeq lr
@domain_error:
    ldr r2, =0x7ff80000
    orr r1, r1, r2
    ldr r3, =data_0205fdbc
    mov r4, #0x21
    str r4, [r3]
    ldmfd sp!, {r4-r6, lr}
    bx lr
}
