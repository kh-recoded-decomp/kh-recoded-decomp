/* MobiClip deblocking post-filter: hand-written ARM the frame blitter calls in place when a stream
 * asks for a smoothed picture (display modes 1 and 2). It copies the decoded planes into a second
 * pair of 256-byte-stride planes, filtering the 8-pixel block edges on the way: vertical edges row
 * by row during the copy, horizontal edges in place afterwards. An edge is filtered when
 * |p0 - q0| < alpha and both |p1 - p0| and |q1 - q0| < beta, the thresholds picked by the frame's
 * quantiser. Request block: {src luma, src chroma, dst luma, dst chroma, width, height, quantiser,
 * clip table, vertical-only}; chroma rows hold Co at +0 and Cg at +0x80. The chroma
 * horizontal-edge routine and the four constant words after it sit at the start of .rodata. */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global MobiClip_DeblockFrame
    .type MobiClip_DeblockFrame, %function
MobiClip_DeblockFrame:
    /* MobiClip_DeblockFrame */
MobiClip_Code_020B715C:
    push {r4, r5, r6, r7, r8, sb, lr}
MobiClip_Code_020B7160:
    sub sp, sp, #0x18
MobiClip_Code_020B7164:
    mov r4, r0
MobiClip_Code_020B7168:
    ldr r5, [r4, #0x18]
MobiClip_Code_020B716C:
    add r6, pc, #0xc0
MobiClip_Code_020B7170:
    ldrb r6, [r6, r5]
MobiClip_Code_020B7174:
    add r7, pc, #0xdd
MobiClip_Code_020B7178:
    ldrb r7, [r7, r5]
MobiClip_Code_020B717C:
    orr r6, r6, r7, lsl #8
MobiClip_Code_020B7180:
    str r6, [sp, #0x10]
MobiClip_Code_020B7184:
    ldr r5, [r4]
MobiClip_Code_020B7188:
    ldr r6, [r4, #8]
MobiClip_Code_020B718C:
    ldr r7, [r4, #0x10]
MobiClip_Code_020B7190:
    ldr r8, [r4, #0x14]
MobiClip_Code_020B7194:
    ldr sb, [r4, #0x1c]
MobiClip_Code_020B7198:
    str r5, [sp]
MobiClip_Code_020B719C:
    str r6, [sp, #4]
MobiClip_Code_020B71A0:
    str r7, [sp, #8]
MobiClip_Code_020B71A4:
    str r8, [sp, #0xc]
MobiClip_Code_020B71A8:
    add sb, sb, #0x40
MobiClip_Code_020B71AC:
    str sb, [sp, #0x14]
MobiClip_Code_020B71B0:
    mov r0, sp
MobiClip_Code_020B71B4:
    bl MobiClip_Code_020B728C
MobiClip_Code_020B71B8:
    ldr r0, [r4, #0x20]
MobiClip_Code_020B71BC:
    cmp r0, #1
MobiClip_Code_020B71C0:
    movne r0, sp
MobiClip_Code_020B71C4:
    blne MobiClip_Code_020B73C4
MobiClip_Code_020B71C8:
    ldr r5, [r4, #4]
MobiClip_Code_020B71CC:
    ldr r6, [r4, #0xc]
MobiClip_Code_020B71D0:
    ldr r7, [r4, #0x10]
MobiClip_Code_020B71D4:
    ldr r8, [r4, #0x14]
MobiClip_Code_020B71D8:
    str r5, [sp]
MobiClip_Code_020B71DC:
    str r6, [sp, #4]
MobiClip_Code_020B71E0:
    asr r7, r7, #1
MobiClip_Code_020B71E4:
    asr r8, r8, #1
MobiClip_Code_020B71E8:
    str r7, [sp, #8]
MobiClip_Code_020B71EC:
    str r8, [sp, #0xc]
MobiClip_Code_020B71F0:
    mov r0, sp
MobiClip_Code_020B71F4:
    bl MobiClip_Code_020B74B8
MobiClip_Code_020B71F8:
    ldr r0, [r4, #0x20]
MobiClip_Code_020B71FC:
    cmp r0, #1
MobiClip_Code_020B7200:
    movne r0, sp
MobiClip_Code_020B7204:
    blne MobiClip_Code_020B75C0
MobiClip_Code_020B7208:
    ldr r5, [r4, #4]
MobiClip_Code_020B720C:
    ldr r6, [r4, #0xc]
MobiClip_Code_020B7210:
    add r5, r5, #0x80
MobiClip_Code_020B7214:
    add r6, r6, #0x80
MobiClip_Code_020B7218:
    str r5, [sp]
MobiClip_Code_020B721C:
    str r6, [sp, #4]
MobiClip_Code_020B7220:
    mov r0, sp
MobiClip_Code_020B7224:
    bl MobiClip_Code_020B74B8
MobiClip_Code_020B7228:
    ldr r0, [r4, #0x20]
MobiClip_Code_020B722C:
    cmp r0, #1
MobiClip_Code_020B7230:
    movne r0, sp
MobiClip_Code_020B7234:
    blne MobiClip_Code_020B75C0
MobiClip_Code_020B7238:
    add sp, sp, #0x18
MobiClip_Code_020B723C:
    pop {r4, r5, r6, r7, r8, sb, pc}
    .global gMobiClipDeblockAlpha
    .type gMobiClipDeblockAlpha, %object
gMobiClipDeblockAlpha:
    .byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x05, 0x05, 0x06, 0x07, 0x08, 0x0a, 0x0b, 0x0d, 0x0f, 0x11
    .byte 0x13, 0x16, 0x19, 0x1d, 0x21, 0x26, 0x2c, 0x32, 0x39, 0x42, 0x4b, 0x56, 0x62, 0x70, 0x80, 0x93
    .byte 0xa8, 0xc0, 0xdb, 0xfb, 0xff
    .global gMobiClipDeblockBeta
    .type gMobiClipDeblockBeta, %object
gMobiClipDeblockBeta:
    .byte 0x00, 0x00, 0x00, 0x01, 0x01, 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x05, 0x05, 0x06, 0x06, 0x07
    .byte 0x07, 0x08, 0x08, 0x09, 0x09, 0x0a, 0x0b, 0x0b, 0x0c, 0x0c, 0x0d, 0x0d, 0x0e, 0x0e, 0x0f, 0x0f
    .byte 0x10, 0x10, 0x11, 0x11, 0x12
    .global gMobiClipDeblockPad
    .type gMobiClipDeblockPad, %object
gMobiClipDeblockPad:
    .byte 0x00, 0x00
    /* MobiClip_DeblockLumaVerticalEdges */
MobiClip_Code_020B728C:
    push {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_020B7290:
    ldr lr, [r0, #0x10]
MobiClip_Code_020B7294:
    ldr ip, [r0, #0x14]
MobiClip_Code_020B7298:
    ldr r1, [r0, #4]
MobiClip_Code_020B729C:
    ldr fp, [r0]
MobiClip_Code_020B72A0:
    ldr r3, [r0, #0xc]
MobiClip_Code_020B72A4:
    ldr r2, [fp], #4
MobiClip_Code_020B72A8:
    ldr sl, [r0, #8]
MobiClip_Code_020B72AC:
    str r3, [sp, #-4]!
MobiClip_Code_020B72B0:
    str r2, [r1], #4
MobiClip_Code_020B72B4:
    sub sl, sl, #8
MobiClip_Code_020B72B8:
    str sl, [sp, #-4]!
MobiClip_Code_020B72BC:
    ldrb r2, [fp], #1
MobiClip_Code_020B72C0:
    ldrb r3, [fp], #1
MobiClip_Code_020B72C4:
    ldrb r4, [fp], #1
MobiClip_Code_020B72C8:
    ldrb r5, [fp], #1
MobiClip_Code_020B72CC:
    ldrb r6, [fp], #1
MobiClip_Code_020B72D0:
    ldrb r7, [fp], #1
MobiClip_Code_020B72D4:
    ldrb r8, [fp], #1
MobiClip_Code_020B72D8:
    and sb, lr, #0xff
MobiClip_Code_020B72DC:
    subs sl, r5, r6
MobiClip_Code_020B72E0:
    rsblt sl, sl, #0
MobiClip_Code_020B72E4:
    cmp sl, sb
MobiClip_Code_020B72E8:
    bge MobiClip_Code_020B7360
MobiClip_Code_020B72EC:
    subs sl, r4, r5
MobiClip_Code_020B72F0:
    rsblt sl, sl, #0
MobiClip_Code_020B72F4:
    cmp sl, lr, lsr #8
MobiClip_Code_020B72F8:
    bge MobiClip_Code_020B7360
MobiClip_Code_020B72FC:
    subs sl, r7, r6
MobiClip_Code_020B7300:
    rsblt sl, sl, #0
MobiClip_Code_020B7304:
    cmp sl, lr, lsr #8
MobiClip_Code_020B7308:
    bge MobiClip_Code_020B7360
MobiClip_Code_020B730C:
    add sl, r5, r6
MobiClip_Code_020B7310:
    add sl, sl, #1
MobiClip_Code_020B7314:
    subs sb, r3, r5
MobiClip_Code_020B7318:
    sub r5, r4, r7
MobiClip_Code_020B731C:
    add r5, r5, #4
MobiClip_Code_020B7320:
    asr r5, r5, #3
MobiClip_Code_020B7324:
    rsblt sb, sb, #0
MobiClip_Code_020B7328:
    cmp sb, lr, lsr #8
MobiClip_Code_020B732C:
    addlt r4, r3, sl, asr #1
MobiClip_Code_020B7330:
    addlt r4, r4, #1
MobiClip_Code_020B7334:
    asrlt r4, r4, #1
MobiClip_Code_020B7338:
    subs sb, r8, r6
MobiClip_Code_020B733C:
    rsblt sb, sb, #0
MobiClip_Code_020B7340:
    cmp sb, lr, lsr #8
MobiClip_Code_020B7344:
    addlt r7, r8, sl, asr #1
MobiClip_Code_020B7348:
    addlt r7, r7, #1
MobiClip_Code_020B734C:
    asrlt r7, r7, #1
MobiClip_Code_020B7350:
    rsb r6, r5, sl, asr #1
MobiClip_Code_020B7354:
    ldrb r6, [ip, r6]
MobiClip_Code_020B7358:
    add r5, r5, sl, asr #1
MobiClip_Code_020B735C:
    ldrb r5, [ip, r5]
MobiClip_Code_020B7360:
    ldrb sb, [fp], #1
MobiClip_Code_020B7364:
    orr r2, r2, r3, lsl #8
MobiClip_Code_020B7368:
    orr r2, r2, r4, lsl #16
MobiClip_Code_020B736C:
    orr r2, r2, r5, lsl #24
MobiClip_Code_020B7370:
    orr r6, r6, r7, lsl #8
MobiClip_Code_020B7374:
    orr r6, r6, r8, lsl #16
MobiClip_Code_020B7378:
    orr r6, r6, sb, lsl #24
MobiClip_Code_020B737C:
    stm r1!, {r2, r6}
MobiClip_Code_020B7380:
    pop {sl}
MobiClip_Code_020B7384:
    subs sl, sl, #8
MobiClip_Code_020B7388:
    bne MobiClip_Code_020B72B8
MobiClip_Code_020B738C:
    pop {r3}
MobiClip_Code_020B7390:
    ldr r2, [fp], #4
MobiClip_Code_020B7394:
    ldr sl, [r0, #8]
MobiClip_Code_020B7398:
    add fp, fp, #0x100
MobiClip_Code_020B739C:
    str r2, [r1], #0x104
MobiClip_Code_020B73A0:
    sub fp, fp, sl
MobiClip_Code_020B73A4:
    sub r1, r1, sl
MobiClip_Code_020B73A8:
    subs r3, r3, #1
MobiClip_Code_020B73AC:
    ldrne r2, [fp], #4
MobiClip_Code_020B73B0:
    strne r3, [sp, #-4]!
MobiClip_Code_020B73B4:
    subne sl, sl, #8
MobiClip_Code_020B73B8:
    strne r2, [r1], #4
MobiClip_Code_020B73BC:
    bne MobiClip_Code_020B72B8
MobiClip_Code_020B73C0:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}
    /* MobiClip_DeblockLumaHorizontalEdges */
MobiClip_Code_020B73C4:
    push {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_020B73C8:
    ldr r1, [r0, #8]
MobiClip_Code_020B73CC:
    ldr r2, [r0, #0xc]
MobiClip_Code_020B73D0:
    ldr r3, [r0, #0x10]
MobiClip_Code_020B73D4:
    ldr r4, [r0, #0x14]
MobiClip_Code_020B73D8:
    ldr r0, [r0, #4]
MobiClip_Code_020B73DC:
    mov r5, r1
MobiClip_Code_020B73E0:
    add r0, r0, #0x800
MobiClip_Code_020B73E4:
    subs r2, r2, #8
MobiClip_Code_020B73E8:
    ldrb r7, [r0, #-0x100]
MobiClip_Code_020B73EC:
    ldrb r8, [r0]
MobiClip_Code_020B73F0:
    ldrb r6, [r0, #-0x200]
MobiClip_Code_020B73F4:
    ldrb sb, [r0, #0x100]
MobiClip_Code_020B73F8:
    and lr, r3, #0xff
MobiClip_Code_020B73FC:
    subs sl, r7, r8
MobiClip_Code_020B7400:
    rsblt sl, sl, #0
MobiClip_Code_020B7404:
    cmp sl, lr
MobiClip_Code_020B7408:
    bge MobiClip_Code_020B7494
MobiClip_Code_020B740C:
    subs sl, r6, r7
MobiClip_Code_020B7410:
    rsblt sl, sl, #0
MobiClip_Code_020B7414:
    cmp sl, r3, lsr #8
MobiClip_Code_020B7418:
    bge MobiClip_Code_020B7494
MobiClip_Code_020B741C:
    subs sl, r8, sb
MobiClip_Code_020B7420:
    rsblt sl, sl, #0
MobiClip_Code_020B7424:
    cmp sl, r3, lsr #8
MobiClip_Code_020B7428:
    bge MobiClip_Code_020B7494
MobiClip_Code_020B742C:
    ldrb ip, [r0, #-0x300]
MobiClip_Code_020B7430:
    ldrb lr, [r0, #0x200]
MobiClip_Code_020B7434:
    sub r6, r6, sb
MobiClip_Code_020B7438:
    add sb, r7, r8
MobiClip_Code_020B743C:
    add r6, r6, #4
MobiClip_Code_020B7440:
    add sb, sb, #1
MobiClip_Code_020B7444:
    asr sb, sb, #1
MobiClip_Code_020B7448:
    adds sl, sb, r6, asr #3
MobiClip_Code_020B744C:
    subs fp, sb, r6, asr #3
MobiClip_Code_020B7450:
    ldrb sl, [r4, sl]
MobiClip_Code_020B7454:
    ldrb fp, [r4, fp]
MobiClip_Code_020B7458:
    add sb, sb, #1
MobiClip_Code_020B745C:
    subs r7, ip, r7
MobiClip_Code_020B7460:
    rsblt r7, r7, #0
MobiClip_Code_020B7464:
    cmp r7, r3, lsr #8
MobiClip_Code_020B7468:
    addlt ip, ip, sb
MobiClip_Code_020B746C:
    asrlt ip, ip, #1
MobiClip_Code_020B7470:
    strblt ip, [r0, #-0x200]
MobiClip_Code_020B7474:
    subs r8, lr, r8
MobiClip_Code_020B7478:
    rsblt r8, r8, #0
MobiClip_Code_020B747C:
    cmp r8, r3, lsr #8
MobiClip_Code_020B7480:
    addlt lr, lr, sb
MobiClip_Code_020B7484:
    asrlt lr, lr, #1
MobiClip_Code_020B7488:
    strblt lr, [r0, #0x100]
MobiClip_Code_020B748C:
    strb sl, [r0, #-0x100]
MobiClip_Code_020B7490:
    strb fp, [r0]
MobiClip_Code_020B7494:
    add r0, r0, #1
MobiClip_Code_020B7498:
    subs r5, r5, #1
MobiClip_Code_020B749C:
    bne MobiClip_Code_020B73E8
MobiClip_Code_020B74A0:
    add r0, r0, #0x800
MobiClip_Code_020B74A4:
    sub r0, r0, r1
MobiClip_Code_020B74A8:
    mov r5, r1
MobiClip_Code_020B74AC:
    subs r2, r2, #8
MobiClip_Code_020B74B0:
    bne MobiClip_Code_020B73E8
MobiClip_Code_020B74B4:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}
    /* MobiClip_DeblockChromaVerticalEdges */
MobiClip_Code_020B74B8:
    push {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_020B74BC:
    ldr lr, [r0, #0x10]
MobiClip_Code_020B74C0:
    ldr ip, [r0, #0x14]
MobiClip_Code_020B74C4:
    ldr r1, [r0, #4]
MobiClip_Code_020B74C8:
    ldr fp, [r0]
MobiClip_Code_020B74CC:
    ldr r3, [r0, #0xc]
MobiClip_Code_020B74D0:
    ldr r2, [fp], #4
MobiClip_Code_020B74D4:
    ldr sl, [r0, #8]
MobiClip_Code_020B74D8:
    str r3, [sp, #-4]!
MobiClip_Code_020B74DC:
    str r2, [r1], #4
MobiClip_Code_020B74E0:
    sub sl, sl, #8
MobiClip_Code_020B74E4:
    str sl, [sp, #-4]!
MobiClip_Code_020B74E8:
    ldrb r2, [fp], #1
MobiClip_Code_020B74EC:
    ldrb r3, [fp], #1
MobiClip_Code_020B74F0:
    ldrb r4, [fp], #1
MobiClip_Code_020B74F4:
    ldrb r5, [fp], #1
MobiClip_Code_020B74F8:
    ldrb r6, [fp], #1
MobiClip_Code_020B74FC:
    ldrb r7, [fp], #1
MobiClip_Code_020B7500:
    ldrb r8, [fp], #1
MobiClip_Code_020B7504:
    and sb, lr, #0xff
MobiClip_Code_020B7508:
    subs sl, r5, r6
MobiClip_Code_020B750C:
    rsblt sl, sl, #0
MobiClip_Code_020B7510:
    cmp sl, sb
MobiClip_Code_020B7514:
    bge MobiClip_Code_020B755C
MobiClip_Code_020B7518:
    subs sl, r4, r5
MobiClip_Code_020B751C:
    rsblt sl, sl, #0
MobiClip_Code_020B7520:
    cmp sl, lr, lsr #8
MobiClip_Code_020B7524:
    bge MobiClip_Code_020B755C
MobiClip_Code_020B7528:
    subs sl, r7, r6
MobiClip_Code_020B752C:
    rsblt sl, sl, #0
MobiClip_Code_020B7530:
    cmp sl, lr, lsr #8
MobiClip_Code_020B7534:
    bge MobiClip_Code_020B755C
MobiClip_Code_020B7538:
    add sl, r5, r6
MobiClip_Code_020B753C:
    add sl, sl, #1
MobiClip_Code_020B7540:
    sub sb, r4, r7
MobiClip_Code_020B7544:
    add sb, sb, #4
MobiClip_Code_020B7548:
    asr sb, sb, #3
MobiClip_Code_020B754C:
    add r5, sb, sl, asr #1
MobiClip_Code_020B7550:
    ldrb r5, [ip, r5]
MobiClip_Code_020B7554:
    rsb r6, sb, sl, asr #1
MobiClip_Code_020B7558:
    ldrb r6, [ip, r6]
MobiClip_Code_020B755C:
    ldrb sb, [fp], #1
MobiClip_Code_020B7560:
    orr r2, r2, r3, lsl #8
MobiClip_Code_020B7564:
    orr r2, r2, r4, lsl #16
MobiClip_Code_020B7568:
    orr r2, r2, r5, lsl #24
MobiClip_Code_020B756C:
    orr r6, r6, r7, lsl #8
MobiClip_Code_020B7570:
    orr r6, r6, r8, lsl #16
MobiClip_Code_020B7574:
    orr r6, r6, sb, lsl #24
MobiClip_Code_020B7578:
    stm r1!, {r2, r6}
MobiClip_Code_020B757C:
    pop {sl}
MobiClip_Code_020B7580:
    subs sl, sl, #8
MobiClip_Code_020B7584:
    bne MobiClip_Code_020B74E4
MobiClip_Code_020B7588:
    pop {r3}
MobiClip_Code_020B758C:
    ldr r2, [fp], #4
MobiClip_Code_020B7590:
    ldr sl, [r0, #8]
MobiClip_Code_020B7594:
    add fp, fp, #0x100
MobiClip_Code_020B7598:
    str r2, [r1], #0x104
MobiClip_Code_020B759C:
    sub fp, fp, sl
MobiClip_Code_020B75A0:
    sub r1, r1, sl
MobiClip_Code_020B75A4:
    subs r3, r3, #1
MobiClip_Code_020B75A8:
    ldrne r2, [fp], #4
MobiClip_Code_020B75AC:
    strne r3, [sp, #-4]!
MobiClip_Code_020B75B0:
    subne sl, sl, #8
MobiClip_Code_020B75B4:
    strne r2, [r1], #4
MobiClip_Code_020B75B8:
    bne MobiClip_Code_020B74E4
MobiClip_Code_020B75BC:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}
    .size MobiClip_DeblockFrame, 0x464
    .section .rodata,"a",%progbits
    .arm
    .align 2
    .global MobiClip_DeblockChromaHorizontalEdges
    .type MobiClip_DeblockChromaHorizontalEdges, %object
MobiClip_DeblockChromaHorizontalEdges:
    /* MobiClip_DeblockChromaHorizontalEdges */
MobiClip_Code_020B75C0:
    push {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_020B75C4:
    ldr r1, [r0, #8]
MobiClip_Code_020B75C8:
    ldr r2, [r0, #0xc]
MobiClip_Code_020B75CC:
    ldr r3, [r0, #0x10]
MobiClip_Code_020B75D0:
    ldr r4, [r0, #0x14]
MobiClip_Code_020B75D4:
    ldr r0, [r0, #4]
MobiClip_Code_020B75D8:
    mov r5, r1
MobiClip_Code_020B75DC:
    add r0, r0, #0x800
MobiClip_Code_020B75E0:
    subs r2, r2, #8
MobiClip_Code_020B75E4:
    ldrb r7, [r0, #-0x100]
MobiClip_Code_020B75E8:
    ldrb r8, [r0]
MobiClip_Code_020B75EC:
    ldrb r6, [r0, #-0x200]
MobiClip_Code_020B75F0:
    ldrb sb, [r0, #0x100]
MobiClip_Code_020B75F4:
    and lr, r3, #0xff
MobiClip_Code_020B75F8:
    subs sl, r7, r8
MobiClip_Code_020B75FC:
    rsblt sl, sl, #0
MobiClip_Code_020B7600:
    cmp sl, lr
MobiClip_Code_020B7604:
    bge MobiClip_Code_020B7674
MobiClip_Code_020B7608:
    subs sl, r6, r7
MobiClip_Code_020B760C:
    rsblt sl, sl, #0
MobiClip_Code_020B7610:
    cmp sl, r3, lsr #8
MobiClip_Code_020B7614:
    bge MobiClip_Code_020B7674
MobiClip_Code_020B7618:
    subs sl, r8, sb
MobiClip_Code_020B761C:
    rsblt sl, sl, #0
MobiClip_Code_020B7620:
    cmp sl, r3, lsr #8
MobiClip_Code_020B7624:
    bge MobiClip_Code_020B7674
MobiClip_Code_020B7628:
    sub r6, r6, sb
MobiClip_Code_020B762C:
    add sb, r7, r8
MobiClip_Code_020B7630:
    add r6, r6, #4
MobiClip_Code_020B7634:
    add sb, sb, #1
MobiClip_Code_020B7638:
    asr sb, sb, #1
MobiClip_Code_020B763C:
    adds sl, sb, r6, asr #3
MobiClip_Code_020B7640:
    ldrb sl, [r4, sl]
MobiClip_Code_020B7644:
    subs fp, sb, r6, asr #3
MobiClip_Code_020B7648:
    ldrb fp, [r4, fp]
MobiClip_Code_020B764C:
    subs r5, r5, #1
MobiClip_Code_020B7650:
    strb sl, [r0, #-0x100]
MobiClip_Code_020B7654:
    strb fp, [r0], #1
MobiClip_Code_020B7658:
    bne MobiClip_Code_020B75E4
MobiClip_Code_020B765C:
    add r0, r0, #0x800
MobiClip_Code_020B7660:
    sub r0, r0, r1
MobiClip_Code_020B7664:
    mov r5, r1
MobiClip_Code_020B7668:
    subs r2, r2, #8
MobiClip_Code_020B766C:
    bne MobiClip_Code_020B75E4
MobiClip_Code_020B7670:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}
MobiClip_Code_020B7674:
    add r0, r0, #1
MobiClip_Code_020B7678:
    subs r5, r5, #1
MobiClip_Code_020B767C:
    bne MobiClip_Code_020B75E4
MobiClip_Code_020B7680:
    add r0, r0, #0x800
MobiClip_Code_020B7684:
    sub r0, r0, r1
MobiClip_Code_020B7688:
    mov r5, r1
MobiClip_Code_020B768C:
    subs r2, r2, #8
MobiClip_Code_020B7690:
    bne MobiClip_Code_020B75E4
MobiClip_Code_020B7694:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}
    .global gMobiClipDeblockTailWords
    .type gMobiClipDeblockTailWords, %object
gMobiClipDeblockTailWords:
    .byte 0x14, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x0a, 0x00, 0x00, 0x00
    .size MobiClip_DeblockChromaHorizontalEdges, . - MobiClip_DeblockChromaHorizontalEdges
