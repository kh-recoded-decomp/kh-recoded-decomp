/* MobiClip colour converter: hand-written ARM that turns one decoded YCoCg frame into 15-bit
 * pixels, two destination rows at a time. View block: {pLuma, pChroma, pDest, nDestStrideBytes,
 * nWidthPixels, nHeightRows, pTable}; the stride is in bytes and the width in pixels. Luma rows are
 * 256 bytes; each 256-byte chroma row holds Co at +0 and Cg at +0x80, one pair per 2x2 luma quad.
 *
 * One saturating ramp, indexed signed around pTable + 0x100, does the conversion and the clamp in
 * a single byte load per channel, through three windows displaced by the chroma pair:
 *
 *     green = pTable + Cg            G = ramp[Y + Cg]
 *     red   = pTable + Co - Cg       R = ramp[Y + Co - Cg]
 *     blue  = red - 2 * Co           B = ramp[Y - Co - Cg]
 *
 * The first window built is green, not red. The two anti-diagonal pixels of every quad, (row,
 * col + 1) and (row + 1, col), read the ramp four levels lower (checkerboard dither). Each pixel is
 * 0x8000 | R | G << 5 | B << 10; each quad stores one word of two pixels to each destination row.
 * The inner loop covers sixteen columns as eight unrolled quads, the outer one two rows; both close
 * with `subs` + `bgt`, and the prologue pads its ten-register push with ip.
 *
 * tools/mobiclip/mobiclip_colour.py holds the portable model and runs these instructions against
 * it (random planes, decoded movie frames and a hardware capture). */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global MobiClip_BlitRows
    .type MobiClip_BlitRows, %function
MobiClip_BlitRows:
    /* MobiClip_BlitRows */
MobiClip_Code_020AA300:
    push {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_020AA304:
    ldr r8, [r0, #0xc]
MobiClip_Code_020AA308:
    ldr sb, [r0, #0x10]
MobiClip_Code_020AA30C:
    ldr sl, [r0, #0x14]
MobiClip_Code_020AA310:
    ldr r3, [r0, #0x18]
MobiClip_Code_020AA314:
    mov r4, #0x100
MobiClip_Code_020AA318:
    rsb r5, sb, r4, lsl #1
MobiClip_Code_020AA31C:
    sub r6, r4, sb, lsr #1
MobiClip_Code_020AA320:
    sub r7, r8, sb
MobiClip_Code_020AA324:
    lsl r7, r7, #1
MobiClip_Code_020AA328:
    push {r5, r6, r7, r8, sb, sl}
MobiClip_Code_020AA32C:
    ldr r1, [r0, #4]
MobiClip_Code_020AA330:
    ldr r2, [r0, #8]
MobiClip_Code_020AA334:
    ldr r0, [r0]
MobiClip_Code_020AA338:
    add r3, r3, #0x100
MobiClip_Code_020AA33C:
    add lr, r2, r8
    /* outer loop: two destination rows */
MobiClip_Code_020AA340:
    str sl, [sp, #-4]!
MobiClip_Code_020AA344:
    ldr sl, [sp, #0x14]
    /* inner loop: sixteen columns as eight 2x2 quads */
MobiClip_Code_020AA348:
    ldrb r5, [r1], #0x80
MobiClip_Code_020AA34C:
    ldrb r6, [r1], #-0x7f
MobiClip_Code_020AA350:
    ldrb r4, [r0], #1
MobiClip_Code_020AA354:
    sub r5, r5, #0x80
MobiClip_Code_020AA358:
    sub r6, r6, #0x80
MobiClip_Code_020AA35C:
    add r7, r3, r6
MobiClip_Code_020AA360:
    sub r6, r5, r6
MobiClip_Code_020AA364:
    add r6, r6, r3
MobiClip_Code_020AA368:
    sub r5, r6, r5, lsl #1
MobiClip_Code_020AA36C:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA370:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA374:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA378:
    ldrb r4, [r0], #0xff
MobiClip_Code_020AA37C:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA380:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA384:
    orr r8, r8, #0x8000
MobiClip_Code_020AA388:
    sub r4, r4, #4
MobiClip_Code_020AA38C:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA390:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA394:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA398:
    ldrb r4, [r0], #1
MobiClip_Code_020AA39C:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA3A0:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA3A4:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA3A8:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA3AC:
    str r8, [r2], #4
MobiClip_Code_020AA3B0:
    sub r4, r4, #4
MobiClip_Code_020AA3B4:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA3B8:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA3BC:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA3C0:
    ldrb r4, [r0], #-0xff
MobiClip_Code_020AA3C4:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA3C8:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA3CC:
    orr r8, r8, #0x8000
MobiClip_Code_020AA3D0:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA3D4:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA3D8:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA3DC:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA3E0:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA3E4:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA3E8:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA3EC:
    str r8, [lr], #4
MobiClip_Code_020AA3F0:
    ldrb r5, [r1], #0x80
MobiClip_Code_020AA3F4:
    ldrb r6, [r1], #-0x7f
MobiClip_Code_020AA3F8:
    ldrb r4, [r0], #1
MobiClip_Code_020AA3FC:
    sub r5, r5, #0x80
MobiClip_Code_020AA400:
    sub r6, r6, #0x80
MobiClip_Code_020AA404:
    add r7, r3, r6
MobiClip_Code_020AA408:
    sub r6, r5, r6
MobiClip_Code_020AA40C:
    add r6, r6, r3
MobiClip_Code_020AA410:
    sub r5, r6, r5, lsl #1
MobiClip_Code_020AA414:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA418:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA41C:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA420:
    ldrb r4, [r0], #0xff
MobiClip_Code_020AA424:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA428:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA42C:
    orr r8, r8, #0x8000
MobiClip_Code_020AA430:
    sub r4, r4, #4
MobiClip_Code_020AA434:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA438:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA43C:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA440:
    ldrb r4, [r0], #1
MobiClip_Code_020AA444:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA448:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA44C:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA450:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA454:
    str r8, [r2], #4
MobiClip_Code_020AA458:
    sub r4, r4, #4
MobiClip_Code_020AA45C:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA460:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA464:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA468:
    ldrb r4, [r0], #-0xff
MobiClip_Code_020AA46C:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA470:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA474:
    orr r8, r8, #0x8000
MobiClip_Code_020AA478:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA47C:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA480:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA484:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA488:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA48C:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA490:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA494:
    str r8, [lr], #4
MobiClip_Code_020AA498:
    ldrb r5, [r1], #0x80
MobiClip_Code_020AA49C:
    ldrb r6, [r1], #-0x7f
MobiClip_Code_020AA4A0:
    ldrb r4, [r0], #1
MobiClip_Code_020AA4A4:
    sub r5, r5, #0x80
MobiClip_Code_020AA4A8:
    sub r6, r6, #0x80
MobiClip_Code_020AA4AC:
    add r7, r3, r6
MobiClip_Code_020AA4B0:
    sub r6, r5, r6
MobiClip_Code_020AA4B4:
    add r6, r6, r3
MobiClip_Code_020AA4B8:
    sub r5, r6, r5, lsl #1
MobiClip_Code_020AA4BC:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA4C0:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA4C4:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA4C8:
    ldrb r4, [r0], #0xff
MobiClip_Code_020AA4CC:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA4D0:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA4D4:
    orr r8, r8, #0x8000
MobiClip_Code_020AA4D8:
    sub r4, r4, #4
MobiClip_Code_020AA4DC:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA4E0:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA4E4:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA4E8:
    ldrb r4, [r0], #1
MobiClip_Code_020AA4EC:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA4F0:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA4F4:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA4F8:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA4FC:
    str r8, [r2], #4
MobiClip_Code_020AA500:
    sub r4, r4, #4
MobiClip_Code_020AA504:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA508:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA50C:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA510:
    ldrb r4, [r0], #-0xff
MobiClip_Code_020AA514:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA518:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA51C:
    orr r8, r8, #0x8000
MobiClip_Code_020AA520:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA524:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA528:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA52C:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA530:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA534:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA538:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA53C:
    str r8, [lr], #4
MobiClip_Code_020AA540:
    ldrb r5, [r1], #0x80
MobiClip_Code_020AA544:
    ldrb r6, [r1], #-0x7f
MobiClip_Code_020AA548:
    ldrb r4, [r0], #1
MobiClip_Code_020AA54C:
    sub r5, r5, #0x80
MobiClip_Code_020AA550:
    sub r6, r6, #0x80
MobiClip_Code_020AA554:
    add r7, r3, r6
MobiClip_Code_020AA558:
    sub r6, r5, r6
MobiClip_Code_020AA55C:
    add r6, r6, r3
MobiClip_Code_020AA560:
    sub r5, r6, r5, lsl #1
MobiClip_Code_020AA564:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA568:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA56C:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA570:
    ldrb r4, [r0], #0xff
MobiClip_Code_020AA574:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA578:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA57C:
    orr r8, r8, #0x8000
MobiClip_Code_020AA580:
    sub r4, r4, #4
MobiClip_Code_020AA584:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA588:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA58C:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA590:
    ldrb r4, [r0], #1
MobiClip_Code_020AA594:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA598:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA59C:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA5A0:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA5A4:
    str r8, [r2], #4
MobiClip_Code_020AA5A8:
    sub r4, r4, #4
MobiClip_Code_020AA5AC:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA5B0:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA5B4:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA5B8:
    ldrb r4, [r0], #-0xff
MobiClip_Code_020AA5BC:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA5C0:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA5C4:
    orr r8, r8, #0x8000
MobiClip_Code_020AA5C8:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA5CC:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA5D0:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA5D4:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA5D8:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA5DC:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA5E0:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA5E4:
    str r8, [lr], #4
MobiClip_Code_020AA5E8:
    ldrb r5, [r1], #0x80
MobiClip_Code_020AA5EC:
    ldrb r6, [r1], #-0x7f
MobiClip_Code_020AA5F0:
    ldrb r4, [r0], #1
MobiClip_Code_020AA5F4:
    sub r5, r5, #0x80
MobiClip_Code_020AA5F8:
    sub r6, r6, #0x80
MobiClip_Code_020AA5FC:
    add r7, r3, r6
MobiClip_Code_020AA600:
    sub r6, r5, r6
MobiClip_Code_020AA604:
    add r6, r6, r3
MobiClip_Code_020AA608:
    sub r5, r6, r5, lsl #1
MobiClip_Code_020AA60C:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA610:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA614:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA618:
    ldrb r4, [r0], #0xff
MobiClip_Code_020AA61C:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA620:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA624:
    orr r8, r8, #0x8000
MobiClip_Code_020AA628:
    sub r4, r4, #4
MobiClip_Code_020AA62C:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA630:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA634:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA638:
    ldrb r4, [r0], #1
MobiClip_Code_020AA63C:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA640:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA644:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA648:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA64C:
    str r8, [r2], #4
MobiClip_Code_020AA650:
    sub r4, r4, #4
MobiClip_Code_020AA654:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA658:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA65C:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA660:
    ldrb r4, [r0], #-0xff
MobiClip_Code_020AA664:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA668:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA66C:
    orr r8, r8, #0x8000
MobiClip_Code_020AA670:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA674:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA678:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA67C:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA680:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA684:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA688:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA68C:
    str r8, [lr], #4
MobiClip_Code_020AA690:
    ldrb r5, [r1], #0x80
MobiClip_Code_020AA694:
    ldrb r6, [r1], #-0x7f
MobiClip_Code_020AA698:
    ldrb r4, [r0], #1
MobiClip_Code_020AA69C:
    sub r5, r5, #0x80
MobiClip_Code_020AA6A0:
    sub r6, r6, #0x80
MobiClip_Code_020AA6A4:
    add r7, r3, r6
MobiClip_Code_020AA6A8:
    sub r6, r5, r6
MobiClip_Code_020AA6AC:
    add r6, r6, r3
MobiClip_Code_020AA6B0:
    sub r5, r6, r5, lsl #1
MobiClip_Code_020AA6B4:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA6B8:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA6BC:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA6C0:
    ldrb r4, [r0], #0xff
MobiClip_Code_020AA6C4:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA6C8:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA6CC:
    orr r8, r8, #0x8000
MobiClip_Code_020AA6D0:
    sub r4, r4, #4
MobiClip_Code_020AA6D4:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA6D8:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA6DC:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA6E0:
    ldrb r4, [r0], #1
MobiClip_Code_020AA6E4:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA6E8:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA6EC:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA6F0:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA6F4:
    str r8, [r2], #4
MobiClip_Code_020AA6F8:
    sub r4, r4, #4
MobiClip_Code_020AA6FC:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA700:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA704:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA708:
    ldrb r4, [r0], #-0xff
MobiClip_Code_020AA70C:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA710:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA714:
    orr r8, r8, #0x8000
MobiClip_Code_020AA718:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA71C:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA720:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA724:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA728:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA72C:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA730:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA734:
    str r8, [lr], #4
MobiClip_Code_020AA738:
    ldrb r5, [r1], #0x80
MobiClip_Code_020AA73C:
    ldrb r6, [r1], #-0x7f
MobiClip_Code_020AA740:
    ldrb r4, [r0], #1
MobiClip_Code_020AA744:
    sub r5, r5, #0x80
MobiClip_Code_020AA748:
    sub r6, r6, #0x80
MobiClip_Code_020AA74C:
    add r7, r3, r6
MobiClip_Code_020AA750:
    sub r6, r5, r6
MobiClip_Code_020AA754:
    add r6, r6, r3
MobiClip_Code_020AA758:
    sub r5, r6, r5, lsl #1
MobiClip_Code_020AA75C:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA760:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA764:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA768:
    ldrb r4, [r0], #0xff
MobiClip_Code_020AA76C:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA770:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA774:
    orr r8, r8, #0x8000
MobiClip_Code_020AA778:
    sub r4, r4, #4
MobiClip_Code_020AA77C:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA780:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA784:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA788:
    ldrb r4, [r0], #1
MobiClip_Code_020AA78C:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA790:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA794:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA798:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA79C:
    str r8, [r2], #4
MobiClip_Code_020AA7A0:
    sub r4, r4, #4
MobiClip_Code_020AA7A4:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA7A8:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA7AC:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA7B0:
    ldrb r4, [r0], #-0xff
MobiClip_Code_020AA7B4:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA7B8:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA7BC:
    orr r8, r8, #0x8000
MobiClip_Code_020AA7C0:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA7C4:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA7C8:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA7CC:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA7D0:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA7D4:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA7D8:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA7DC:
    str r8, [lr], #4
MobiClip_Code_020AA7E0:
    ldrb r5, [r1], #0x80
MobiClip_Code_020AA7E4:
    ldrb r6, [r1], #-0x7f
MobiClip_Code_020AA7E8:
    ldrb r4, [r0], #1
MobiClip_Code_020AA7EC:
    sub r5, r5, #0x80
MobiClip_Code_020AA7F0:
    sub r6, r6, #0x80
MobiClip_Code_020AA7F4:
    add r7, r3, r6
MobiClip_Code_020AA7F8:
    sub r6, r5, r6
MobiClip_Code_020AA7FC:
    add r6, r6, r3
MobiClip_Code_020AA800:
    sub r5, r6, r5, lsl #1
MobiClip_Code_020AA804:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA808:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA80C:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA810:
    ldrb r4, [r0], #0xff
MobiClip_Code_020AA814:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA818:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA81C:
    orr r8, r8, #0x8000
MobiClip_Code_020AA820:
    sub r4, r4, #4
MobiClip_Code_020AA824:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA828:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA82C:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA830:
    ldrb r4, [r0], #1
MobiClip_Code_020AA834:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA838:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA83C:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA840:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA844:
    str r8, [r2], #4
MobiClip_Code_020AA848:
    sub r4, r4, #4
MobiClip_Code_020AA84C:
    ldrb r8, [r7, r4]
MobiClip_Code_020AA850:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA854:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA858:
    ldrb r4, [r0], #-0xff
MobiClip_Code_020AA85C:
    add r8, fp, r8, lsl #5
MobiClip_Code_020AA860:
    add r8, r8, ip, lsl #10
MobiClip_Code_020AA864:
    orr r8, r8, #0x8000
MobiClip_Code_020AA868:
    ldrb sb, [r7, r4]
MobiClip_Code_020AA86C:
    ldrb fp, [r6, r4]
MobiClip_Code_020AA870:
    ldrb ip, [r5, r4]
MobiClip_Code_020AA874:
    add r8, r8, sb, lsl #21
MobiClip_Code_020AA878:
    add r8, r8, fp, lsl #16
MobiClip_Code_020AA87C:
    add r8, r8, ip, lsl #26
MobiClip_Code_020AA880:
    orr r8, r8, #0x80000000
MobiClip_Code_020AA884:
    str r8, [lr], #4
MobiClip_Code_020AA888:
    subs sl, sl, #0x10
MobiClip_Code_020AA88C:
    bgt MobiClip_Code_020AA348
    /* advance luma, chroma and both destination rows to the next row pair */
MobiClip_Code_020AA890:
    pop {sl}
MobiClip_Code_020AA894:
    ldr r5, [sp]
MobiClip_Code_020AA898:
    ldr r6, [sp, #4]
MobiClip_Code_020AA89C:
    ldr r7, [sp, #8]
MobiClip_Code_020AA8A0:
    add r0, r0, r5
MobiClip_Code_020AA8A4:
    add r1, r1, r6
MobiClip_Code_020AA8A8:
    add r2, r2, r7
MobiClip_Code_020AA8AC:
    add lr, lr, r7
MobiClip_Code_020AA8B0:
    subs sl, sl, #2
MobiClip_Code_020AA8B4:
    bgt MobiClip_Code_020AA340
MobiClip_Code_020AA8B8:
    add sp, sp, #0x18
MobiClip_Code_020AA8BC:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, pc}
    .size MobiClip_BlitRows, . - MobiClip_BlitRows
