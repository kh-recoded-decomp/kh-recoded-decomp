/* MSL runtime double-precision add (original assembly) */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global _dadd
    .type _dadd, %function
_dadd:
    push {r4, lr}
    eors ip, r1, r3
    eormi r3, r3, #0x80000000
    bmi func_02022e44
    .global func_02022b14
    .type func_02022b14, %function
func_02022b14:
    subs ip, r0, r2
    sbcs lr, r1, r3
    bhs .L_002c
    adds r2, r2, ip
    adc r3, r3, lr
    subs r0, r0, ip
    sbc r1, r1, lr
.L_002c:
    mov lr, #0x80000000
    lsr ip, r1, #0x14
    orr r1, lr, r1, lsl #11
    orr r1, r1, r0, lsr #21
    lsl r0, r0, #0xb
    lsls r4, ip, #0x15
    cmnne r4, #0x200000
    beq .L_0128
    lsr r4, r3, #0x14
    orr r3, lr, r3, lsl #11
    orr r3, r3, r2, lsr #21
    lsl r2, r2, #0xb
    lsls lr, r4, #0x15
    beq .L_0170
.L_0064:
    subs r4, ip, r4
    beq .L_00bc
    cmp r4, #0x20
    ble .L_00a0
    cmp r4, #0x38
    movge r4, #0x3f
    sub r4, r4, #0x20
    rsb lr, r4, #0x20
    orrs lr, r2, r3, lsl lr
    lsr r2, r3, r4
    orrne r2, r2, #1
    adds r0, r0, r2
    adcs r1, r1, #0
    blo .L_00e4
    b .L_00c8
.L_00a0:
    rsb lr, r4, #0x20
    lsls lr, r2, lr
    rsb lr, r4, #0x20
    lsr r2, r2, r4
    orr r2, r2, r3, lsl lr
    lsr r3, r3, r4
    orrne r2, r2, #1
.L_00bc:
    adds r0, r0, r2
    adcs r1, r1, r3
    blo .L_00e4
.L_00c8:
    add ip, ip, #1
    and r4, r0, #1
    rrxs r1, r1
    orr r0, r4, r0, rrx
    lsl lr, ip, #0x15
    cmn lr, #0x200000
    beq .L_02f4
.L_00e4:
    lsls r2, r0, #0x15
    lsr r0, r0, #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    lsr r1, r1, #0xc
    orr r1, r1, ip, lsl #20
    tst r2, #0x80000000
    popeq {r4, lr}
    bxeq lr
    lsls r2, r2, #1
    andseq r2, r0, #1
    popeq {r4, lr}
    bxeq lr
    adds r0, r0, #1
    adc r1, r1, #0
    pop {r4, lr}
    bx lr
.L_0128:
    cmp ip, #0x800
    movge lr, #0x80000000
    movlt lr, #0
    bics ip, ip, #0x800
    beq .L_0194
    orrs r4, r0, r1, lsl #1
    bne .L_02d0
    lsr r4, r3, #0x14
    lsl r3, r3, #0xb
    orr r3, r3, r2, lsr #21
    lsl r2, r2, #0xb
    lsls r4, r4, #0x15
    beq .L_02bc
    cmn r4, #0x200000
    bne .L_02bc
    orrs r4, r2, r3, lsl #1
    beq .L_02bc
    b .L_02d0
.L_0170:
    cmp r4, #0x800
    movge lr, #0x80000000
    movlt lr, #0
    bic ip, ip, #0x800
    bics r4, r4, #0x800
    beq .L_0200
    orrs r4, r2, r3, lsl #1
    bne .L_02d0
    b .L_02bc
.L_0194:
    orrs r4, r0, r1, lsl #1
    beq .L_01d4
    mov ip, #1
    bic r1, r1, #0x80000000
    lsr r4, r3, #0x14
    lsl r3, r3, #0xb
    orr r3, r3, r2, lsr #21
    lsl r2, r2, #0xb
    lsls r4, r4, #0x15
    cmnne r4, #0x200000
    lsr r4, r4, #0x15
    orr r4, r4, lr, lsr #20
    beq .L_0170
    orr r3, r3, #0x80000000
    orr ip, ip, lr, lsr #20
    b .L_0064
.L_01d4:
    lsr ip, r3, #0x14
    lsl r1, r3, #0xb
    orr r1, r1, r2, lsr #21
    lsl r0, r2, #0xb
    lsls r4, ip, #0x15
    beq .L_0288
    cmn r4, #0x200000
    bne .L_0288
    orrs r4, r0, r1, lsl #1
    beq .L_02bc
    b .L_02d4
.L_0200:
    orrs r4, r2, r3, lsl #1
    beq .L_0298
    mov r4, #1
    bic r3, r3, #0x80000000
    cmp r1, #0
    bpl .L_0224
    orr ip, ip, lr, lsr #20
    orr r4, r4, lr, lsr #20
    b .L_0064
.L_0224:
    adds r0, r0, r2
    adcs r1, r1, r3
    blo .L_0244
    add ip, ip, #1
    and r4, r0, #1
    rrxs r1, r1
    rrx r0, r0
    orr r0, r0, r4
.L_0244:
    cmp r1, #0
    subsge ip, ip, #1
    lsls r2, r0, #0x15
    lsr r0, r0, #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    orr r1, lr, r1, lsr #12
    orr r1, r1, ip, lsl #20
    popeq {r4, lr}
    bxeq lr
    tst r2, #0x80000000
    popeq {r4, lr}
    bxeq lr
    lsls r2, r2, #1
    andseq r2, r0, #1
    popeq {r4, lr}
    bxeq lr
.L_0288:
    mov r1, r3
    mov r0, r2
    pop {r4, lr}
    bx lr
.L_0298:
    cmp r1, #0
    subsge ip, ip, #1
    lsr r0, r0, #0xb
    orr r0, r0, r1, lsl #21
    add r1, r1, r1
    orr r1, lr, r1, lsr #12
    orr r1, r1, ip, lsl #20
    pop {r4, lr}
    bx lr
.L_02bc:
    ldr r1, .L_pool_0314
    orr r1, lr, r1
    mov r0, #0
    pop {r4, lr}
    bx lr
.L_02d0:
    mov r1, r3
.L_02d4:
    mvn r0, #0
    bic r1, r0, #0x80000000
    pop {r4, lr}
    bx lr
    mvn r0, #0
    bic r1, r0, #0x80000000
    pop {r4, lr}
    bx lr
.L_02f4:
    cmp ip, #0x800
    movge lr, #0x80000000
    movlt lr, #0
    ldr r1, .L_pool_0314
    orr r1, lr, r1
    mov r0, #0
    pop {r4, lr}
    bx lr
.L_pool_0314:
    .word 0x7ff00000
    .size _dadd, .-_dadd
