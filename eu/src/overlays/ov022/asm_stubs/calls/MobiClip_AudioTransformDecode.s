/* MobiClip audio, coding 1: a small CELP-style speech codec. One call decodes one 10-20 byte frame
 * of the channel record's stream into 128 samples and returns the bytes it consumed (the player
 * adds them to its stream cursor; the record's stream pointer is not advanced here).
 *
 * Frame: word 0 = lag (bits 15-9), gain index (8-6), codebook index 0 (5-0); word 1 = pulse phase
 * (15-14), pulse mode (13-12), codebook indices 1 (11-6) and 2 (5-0); then the pulse halfwords.
 * Lag 127 restarts the channel from the record's default reflection vector and initial gain; lag
 * 126 starts the excitation from silence; any other lag copies a windowed stretch of the previous
 * two frames' excitation (weights 1/16 .. 7/16 at the ends, 1/2 in between). The gain is scaled by
 * a Q13 multiplier per frame, and pulses of -7g..7g (mode 0, 42 three-bit pulses every third
 * sample) or -3g, -g, g, 3g (modes 1-3, two-bit pulses every 3rd/4th/5th sample) are added. The
 * reflection vector is the last frame's plus one entry of each of three codebooks; a Q15 step-up
 * recursion turns it into eight predictor coefficients, interpolated with the last frame's over
 * four 32-sample subframes of an 8th-order all-pole filter (Q14). The output stage saturates to
 * s16 and stores halfwords at the record's stride (+0x14f4).
 *
 * Hand-written ARM from the MobiClip library: the routines return with `mov pc, lr`, keep r4-r11
 * live across the inner calls, read their tables pc-relative and are aligned to 16 bytes, with
 * zero padding between them. No shipped movie selects coding 1 (all use IMA ADPCM, coding 3).
 * tools/mobiclip/mobiclip_audio.py documents the record layout, holds the portable model and runs
 * these instructions against it. */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global MobiClip_AudioTransformDecode
    .type MobiClip_AudioTransformDecode, %function
MobiClip_AudioTransformDecode:
    /* MobiClip_AudioTransformDecode (entry: branch over the inner routines) */
MobiClip_Code_020AAC54:
    b MobiClip_Code_020AB464
    .global gMobiClipAudioAlign_ClearExcitation
    .type gMobiClipAudioAlign_ClearExcitation, %object
gMobiClipAudioAlign_ClearExcitation:
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    /* MobiClip_AudioClearExcitation: zero the 128 excitation words */
MobiClip_Code_020AAC64:
    mov r6, #0x20
MobiClip_Code_020AAC68:
    add r7, r3, #0x200
MobiClip_Code_020AAC6C:
    mov r8, #0
MobiClip_Code_020AAC70:
    mov sb, #0
MobiClip_Code_020AAC74:
    mov sl, #0
MobiClip_Code_020AAC78:
    mov fp, #0
MobiClip_Code_020AAC7C:
    stm r7!, {r8, sb, sl, fp}
MobiClip_Code_020AAC80:
    subs r6, r6, #1
MobiClip_Code_020AAC84:
    bne MobiClip_Code_020AAC7C
MobiClip_Code_020AAC88:
    mov pc, lr
    .global gMobiClipAudioAlign_LongTermPredict
    .type gMobiClipAudioAlign_LongTermPredict, %object
gMobiClipAudioAlign_LongTermPredict:
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    /* MobiClip_AudioLongTermPredict: windowed copy of the history at the frame's lag */
MobiClip_Code_020AAC94:
    push {r1, r3, r4}
MobiClip_Code_020AAC98:
    add r3, r3, #0x200
MobiClip_Code_020AAC9C:
    rsb ip, r6, #0x7f
MobiClip_Code_020AACA0:
    add r4, r4, ip, lsl #2
MobiClip_Code_020AACA4:
    ldr r2, [r4], #4
MobiClip_Code_020AACA8:
    mov r1, #2
MobiClip_Code_020AACAC:
    asr r2, r2, #4
MobiClip_Code_020AACB0:
    str r2, [r3], #4
MobiClip_Code_020AACB4:
    ldr r2, [r4], #4
MobiClip_Code_020AACB8:
    ldr r7, [r4], #4
MobiClip_Code_020AACBC:
    ldr r8, [r4], #4
MobiClip_Code_020AACC0:
    ldr sb, [r4], #4
MobiClip_Code_020AACC4:
    ldr sl, [r4], #4
MobiClip_Code_020AACC8:
    ldr fp, [r4], #4
MobiClip_Code_020AACCC:
    mul ip, r2, r1
MobiClip_Code_020AACD0:
    add r1, r1, #1
MobiClip_Code_020AACD4:
    asr ip, ip, #4
MobiClip_Code_020AACD8:
    str ip, [r3], #4
MobiClip_Code_020AACDC:
    mul ip, r7, r1
MobiClip_Code_020AACE0:
    add r1, r1, #1
MobiClip_Code_020AACE4:
    asr ip, ip, #4
MobiClip_Code_020AACE8:
    str ip, [r3], #4
MobiClip_Code_020AACEC:
    mul ip, r8, r1
MobiClip_Code_020AACF0:
    add r1, r1, #1
MobiClip_Code_020AACF4:
    asr ip, ip, #4
MobiClip_Code_020AACF8:
    str ip, [r3], #4
MobiClip_Code_020AACFC:
    mul ip, sb, r1
MobiClip_Code_020AAD00:
    add r1, r1, #1
MobiClip_Code_020AAD04:
    asr ip, ip, #4
MobiClip_Code_020AAD08:
    str ip, [r3], #4
MobiClip_Code_020AAD0C:
    mul ip, sl, r1
MobiClip_Code_020AAD10:
    add r1, r1, #1
MobiClip_Code_020AAD14:
    asr ip, ip, #4
MobiClip_Code_020AAD18:
    str ip, [r3], #4
MobiClip_Code_020AAD1C:
    mul ip, fp, r1
MobiClip_Code_020AAD20:
    asr ip, ip, #4
MobiClip_Code_020AAD24:
    str ip, [r3], #4
MobiClip_Code_020AAD28:
    mov ip, #0x72
MobiClip_Code_020AAD2C:
    ldm r4!, {r6, r7, r8, sb, sl, fp}
MobiClip_Code_020AAD30:
    asr r6, r6, #1
MobiClip_Code_020AAD34:
    asr r7, r7, #1
MobiClip_Code_020AAD38:
    asr r8, r8, #1
MobiClip_Code_020AAD3C:
    asr sb, sb, #1
MobiClip_Code_020AAD40:
    asr sl, sl, #1
MobiClip_Code_020AAD44:
    asr fp, fp, #1
MobiClip_Code_020AAD48:
    stm r3!, {r6, r7, r8, sb, sl, fp}
MobiClip_Code_020AAD4C:
    subs ip, ip, #6
MobiClip_Code_020AAD50:
    bne MobiClip_Code_020AAD2C
MobiClip_Code_020AAD54:
    ldr r2, [r4], #4
MobiClip_Code_020AAD58:
    ldr r7, [r4], #4
MobiClip_Code_020AAD5C:
    ldr r8, [r4], #4
MobiClip_Code_020AAD60:
    ldr sb, [r4], #4
MobiClip_Code_020AAD64:
    ldr sl, [r4], #4
MobiClip_Code_020AAD68:
    ldr fp, [r4], #4
MobiClip_Code_020AAD6C:
    mul ip, r2, r1
MobiClip_Code_020AAD70:
    sub r1, r1, #1
MobiClip_Code_020AAD74:
    asr ip, ip, #4
MobiClip_Code_020AAD78:
    str ip, [r3], #4
MobiClip_Code_020AAD7C:
    mul ip, r7, r1
MobiClip_Code_020AAD80:
    sub r1, r1, #1
MobiClip_Code_020AAD84:
    asr ip, ip, #4
MobiClip_Code_020AAD88:
    str ip, [r3], #4
MobiClip_Code_020AAD8C:
    mul ip, r8, r1
MobiClip_Code_020AAD90:
    sub r1, r1, #1
MobiClip_Code_020AAD94:
    asr ip, ip, #4
MobiClip_Code_020AAD98:
    str ip, [r3], #4
MobiClip_Code_020AAD9C:
    mul ip, sb, r1
MobiClip_Code_020AADA0:
    sub r1, r1, #1
MobiClip_Code_020AADA4:
    asr ip, ip, #4
MobiClip_Code_020AADA8:
    str ip, [r3], #4
MobiClip_Code_020AADAC:
    mul ip, sl, r1
MobiClip_Code_020AADB0:
    sub r1, r1, #1
MobiClip_Code_020AADB4:
    asr ip, ip, #4
MobiClip_Code_020AADB8:
    str ip, [r3], #4
MobiClip_Code_020AADBC:
    mul ip, fp, r1
MobiClip_Code_020AADC0:
    ldr r2, [r4], #4
MobiClip_Code_020AADC4:
    asr ip, ip, #4
MobiClip_Code_020AADC8:
    str ip, [r3], #4
MobiClip_Code_020AADCC:
    asr r2, r2, #4
MobiClip_Code_020AADD0:
    str r2, [r3], #4
MobiClip_Code_020AADD4:
    pop {r1, r3, r4}
MobiClip_Code_020AADD8:
    mov pc, lr
    .global gMobiClipAudioAlign_AddPulses2Bit
    .type gMobiClipAudioAlign_AddPulses2Bit, %object
gMobiClipAudioAlign_AddPulses2Bit:
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    /* MobiClip_AudioAddPulses2Bit: pulse modes 1-3, amplitudes -3g, -g, g, 3g */
MobiClip_Code_020AADE4:
    add r1, r3, #0x200
MobiClip_Code_020AADE8:
    add r1, r1, r7, lsl #2
MobiClip_Code_020AADEC:
    rsb r7, r6, #0
MobiClip_Code_020AADF0:
    lsl r6, r6, #1
MobiClip_Code_020AADF4:
    sub r7, r7, r6
MobiClip_Code_020AADF8:
    ldrh r5, [r0], #2
MobiClip_Code_020AADFC:
    mov fp, #0xe
MobiClip_Code_020AAE00:
    ldr sl, [r1]
MobiClip_Code_020AAE04:
    lsr r2, r5, fp
MobiClip_Code_020AAE08:
    and r2, r2, #3
MobiClip_Code_020AAE0C:
    mla r2, r6, r2, r7
MobiClip_Code_020AAE10:
    add sl, sl, r2
MobiClip_Code_020AAE14:
    str sl, [r1], sb
MobiClip_Code_020AAE18:
    subs fp, fp, #2
MobiClip_Code_020AAE1C:
    bge MobiClip_Code_020AAE00
MobiClip_Code_020AAE20:
    subs r8, r8, #1
MobiClip_Code_020AAE24:
    bne MobiClip_Code_020AADF8
MobiClip_Code_020AAE28:
    pop {r1, pc}
    .global gMobiClipAudioAlign_AddPulses3Bit
    .type gMobiClipAudioAlign_AddPulses3Bit, %object
gMobiClipAudioAlign_AddPulses3Bit:
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    /* MobiClip_AudioAddPulses3Bit: pulse mode 0, 42 pulses, amplitudes -7g..7g */
MobiClip_Code_020AAE34:
    add r1, r3, #0x200
MobiClip_Code_020AAE38:
    add r1, r1, r7, lsl #2
MobiClip_Code_020AAE3C:
    rsb r7, r6, #0
MobiClip_Code_020AAE40:
    lsl r6, r6, #1
MobiClip_Code_020AAE44:
    sub r7, r7, r6, lsl #1
MobiClip_Code_020AAE48:
    sub r7, r7, r6
MobiClip_Code_020AAE4C:
    mov sb, #0
MobiClip_Code_020AAE50:
    mov r8, #8
MobiClip_Code_020AAE54:
    ldrh r5, [r0], #2
MobiClip_Code_020AAE58:
    mov fp, #0xd
MobiClip_Code_020AAE5C:
    ldr sl, [r1]
MobiClip_Code_020AAE60:
    lsr r2, r5, fp
MobiClip_Code_020AAE64:
    and r2, r2, #7
MobiClip_Code_020AAE68:
    mla r2, r6, r2, r7
MobiClip_Code_020AAE6C:
    add sl, sl, r2
MobiClip_Code_020AAE70:
    str sl, [r1], #0xc
MobiClip_Code_020AAE74:
    subs fp, fp, #3
MobiClip_Code_020AAE78:
    bge MobiClip_Code_020AAE5C
MobiClip_Code_020AAE7C:
    and r5, r5, #1
MobiClip_Code_020AAE80:
    orr sb, r5, sb, lsl #1
MobiClip_Code_020AAE84:
    subs r8, r8, #1
MobiClip_Code_020AAE88:
    bne MobiClip_Code_020AAE54
MobiClip_Code_020AAE8C:
    ldr sl, [r1]
MobiClip_Code_020AAE90:
    lsr r2, sb, #5
MobiClip_Code_020AAE94:
    and r2, r2, #7
MobiClip_Code_020AAE98:
    mla r2, r6, r2, r7
MobiClip_Code_020AAE9C:
    add sl, sl, r2
MobiClip_Code_020AAEA0:
    str sl, [r1], #0xc
MobiClip_Code_020AAEA4:
    ldr sl, [r1]
MobiClip_Code_020AAEA8:
    lsr r2, sb, #2
MobiClip_Code_020AAEAC:
    and r2, r2, #7
MobiClip_Code_020AAEB0:
    mla r2, r6, r2, r7
MobiClip_Code_020AAEB4:
    add sl, sl, r2
MobiClip_Code_020AAEB8:
    str sl, [r1]
MobiClip_Code_020AAEBC:
    pop {r1, pc}
    .global gMobiClipAudioAlign_DecodeCoefficients
    .type gMobiClipAudioAlign_DecodeCoefficients, %object
gMobiClipAudioAlign_DecodeCoefficients:
    .byte 0x00, 0x00, 0x00, 0x00
    /* MobiClip_AudioDecodeCoefficients: three codebook entries, then the Q15 step-up */
MobiClip_Code_020AAEC4:
    push {r3, r4, lr}
MobiClip_Code_020AAEC8:
    ldm r2, {r5, r6, r7, r8, sb, sl, fp, ip}
MobiClip_Code_020AAECC:
    add r3, r1, #0x70
MobiClip_Code_020AAED0:
    ldrb r4, [r3]
MobiClip_Code_020AAED4:
    add r2, r1, #0x8c0
MobiClip_Code_020AAED8:
    add r4, r2, r4, lsl #4
MobiClip_Code_020AAEDC:
    bl MobiClip_Code_020AB034
MobiClip_Code_020AAEE0:
    add r3, r1, #0x71
MobiClip_Code_020AAEE4:
    ldrb r4, [r3]
MobiClip_Code_020AAEE8:
    add r2, r1, #0xcc0
MobiClip_Code_020AAEEC:
    add r4, r2, r4, lsl #4
MobiClip_Code_020AAEF0:
    bl MobiClip_Code_020AB034
MobiClip_Code_020AAEF4:
    add r3, r1, #0x72
MobiClip_Code_020AAEF8:
    ldrb r4, [r3]
MobiClip_Code_020AAEFC:
    add r2, r1, #0x10c0
MobiClip_Code_020AAF00:
    add r4, r2, r4, lsl #4
MobiClip_Code_020AAF04:
    bl MobiClip_Code_020AB034
MobiClip_Code_020AAF08:
    add r2, r1, #8
MobiClip_Code_020AAF0C:
    stm r2, {r5, r6, r7, r8, sb, sl, fp, ip}
MobiClip_Code_020AAF10:
    mul r3, r5, r6
MobiClip_Code_020AAF14:
    add r5, r5, r3, asr #15
MobiClip_Code_020AAF18:
    mul r3, r6, r7
MobiClip_Code_020AAF1C:
    mul r4, r5, r7
MobiClip_Code_020AAF20:
    add r5, r5, r3, asr #15
MobiClip_Code_020AAF24:
    add r6, r6, r4, asr #15
MobiClip_Code_020AAF28:
    mul r3, r7, r8
MobiClip_Code_020AAF2C:
    mul r4, r5, r8
MobiClip_Code_020AAF30:
    add r5, r5, r3, asr #15
MobiClip_Code_020AAF34:
    mul r3, r6, r8
MobiClip_Code_020AAF38:
    add r7, r7, r4, asr #15
MobiClip_Code_020AAF3C:
    add r6, r6, r3, asr #15
MobiClip_Code_020AAF40:
    mul r3, r8, sb
MobiClip_Code_020AAF44:
    mul r4, r5, sb
MobiClip_Code_020AAF48:
    add r5, r5, r3, asr #15
MobiClip_Code_020AAF4C:
    add r8, r8, r4, asr #15
MobiClip_Code_020AAF50:
    mul r3, r7, sb
MobiClip_Code_020AAF54:
    mul r4, r6, sb
MobiClip_Code_020AAF58:
    add r6, r6, r3, asr #15
MobiClip_Code_020AAF5C:
    add r7, r7, r4, asr #15
MobiClip_Code_020AAF60:
    mul r3, sb, sl
MobiClip_Code_020AAF64:
    mul r4, r5, sl
MobiClip_Code_020AAF68:
    add r5, r5, r3, asr #15
MobiClip_Code_020AAF6C:
    add sb, sb, r4, asr #15
MobiClip_Code_020AAF70:
    mul r3, r8, sl
MobiClip_Code_020AAF74:
    mul r4, r6, sl
MobiClip_Code_020AAF78:
    add r6, r6, r3, asr #15
MobiClip_Code_020AAF7C:
    mul r3, r7, sl
MobiClip_Code_020AAF80:
    add r8, r8, r4, asr #15
MobiClip_Code_020AAF84:
    add r7, r7, r3, asr #15
MobiClip_Code_020AAF88:
    mul r3, sl, fp
MobiClip_Code_020AAF8C:
    mul r4, r5, fp
MobiClip_Code_020AAF90:
    add r5, r5, r3, asr #15
MobiClip_Code_020AAF94:
    add sl, sl, r4, asr #15
MobiClip_Code_020AAF98:
    mul r3, sb, fp
MobiClip_Code_020AAF9C:
    mul r4, r6, fp
MobiClip_Code_020AAFA0:
    add r6, r6, r3, asr #15
MobiClip_Code_020AAFA4:
    add sb, sb, r4, asr #15
MobiClip_Code_020AAFA8:
    mul r3, r8, fp
MobiClip_Code_020AAFAC:
    mul r4, r7, fp
MobiClip_Code_020AAFB0:
    add r7, r7, r3, asr #15
MobiClip_Code_020AAFB4:
    add r8, r8, r4, asr #15
MobiClip_Code_020AAFB8:
    mul r3, fp, ip
MobiClip_Code_020AAFBC:
    mul r4, r5, ip
MobiClip_Code_020AAFC0:
    add r5, r5, r3, asr #15
MobiClip_Code_020AAFC4:
    add fp, fp, r4, asr #15
MobiClip_Code_020AAFC8:
    mul r3, sl, ip
MobiClip_Code_020AAFCC:
    mul r4, r6, ip
MobiClip_Code_020AAFD0:
    add r6, r6, r3, asr #15
MobiClip_Code_020AAFD4:
    add sl, sl, r4, asr #15
MobiClip_Code_020AAFD8:
    mul r3, sb, ip
MobiClip_Code_020AAFDC:
    mul r4, r7, ip
MobiClip_Code_020AAFE0:
    add r7, r7, r3, asr #15
MobiClip_Code_020AAFE4:
    mul r3, r8, ip
MobiClip_Code_020AAFE8:
    add sb, sb, r4, asr #15
MobiClip_Code_020AAFEC:
    add r8, r8, r3, asr #15
MobiClip_Code_020AAFF0:
    asr r5, r5, #1
MobiClip_Code_020AAFF4:
    rsb r5, r5, #0
MobiClip_Code_020AAFF8:
    asr r6, r6, #1
MobiClip_Code_020AAFFC:
    rsb r6, r6, #0
MobiClip_Code_020AB000:
    asr r7, r7, #1
MobiClip_Code_020AB004:
    rsb r7, r7, #0
MobiClip_Code_020AB008:
    asr r8, r8, #1
MobiClip_Code_020AB00C:
    rsb r8, r8, #0
MobiClip_Code_020AB010:
    asr sb, sb, #1
MobiClip_Code_020AB014:
    rsb sb, sb, #0
MobiClip_Code_020AB018:
    asr sl, sl, #1
MobiClip_Code_020AB01C:
    rsb sl, sl, #0
MobiClip_Code_020AB020:
    asr fp, fp, #1
MobiClip_Code_020AB024:
    rsb fp, fp, #0
MobiClip_Code_020AB028:
    asr ip, ip, #1
MobiClip_Code_020AB02C:
    rsb ip, ip, #0
MobiClip_Code_020AB030:
    pop {r3, r4, pc}
    /* MobiClip_AudioAddCodebookEntry: add eight s16 to r5-ip */
MobiClip_Code_020AB034:
    ldrsh r0, [r4], #2
MobiClip_Code_020AB038:
    ldrsh r3, [r4], #2
MobiClip_Code_020AB03C:
    ldrsh r2, [r4], #2
MobiClip_Code_020AB040:
    add r5, r5, r0
MobiClip_Code_020AB044:
    add r6, r6, r3
MobiClip_Code_020AB048:
    add r7, r7, r2
MobiClip_Code_020AB04C:
    ldrsh r0, [r4], #2
MobiClip_Code_020AB050:
    ldrsh r3, [r4], #2
MobiClip_Code_020AB054:
    ldrsh r2, [r4], #2
MobiClip_Code_020AB058:
    add r8, r8, r0
MobiClip_Code_020AB05C:
    add sb, sb, r3
MobiClip_Code_020AB060:
    add sl, sl, r2
MobiClip_Code_020AB064:
    ldrsh r0, [r4], #2
MobiClip_Code_020AB068:
    ldrsh r3, [r4], #2
MobiClip_Code_020AB06C:
    add fp, fp, r0
MobiClip_Code_020AB070:
    add ip, ip, r3
MobiClip_Code_020AB074:
    mov pc, lr
    .global gMobiClipAudioAlign_SynthesisFilter
    .type gMobiClipAudioAlign_SynthesisFilter, %object
gMobiClipAudioAlign_SynthesisFilter:
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    /* MobiClip_AudioSynthesisFilter: 8th-order all-pole filter, Q14 */
MobiClip_Code_020AB084:
    push {r1, r3, r4, lr}
MobiClip_Code_020AB088:
    add lr, r1, #0x78
MobiClip_Code_020AB08C:
    ldr r1, [r1, #0x74]
MobiClip_Code_020AB090:
    str r2, [sp, #-4]!
MobiClip_Code_020AB094:
    ldr r4, [r0], #4
MobiClip_Code_020AB098:
    ldr r3, [lr, #0x1c]
MobiClip_Code_020AB09C:
    lsl r4, r4, #0xe
MobiClip_Code_020AB0A0:
    ldr r2, [lr, #0x18]
MobiClip_Code_020AB0A4:
    mla r4, r5, r3, r4
MobiClip_Code_020AB0A8:
    ldr r3, [lr, #0x14]
MobiClip_Code_020AB0AC:
    mla r4, r6, r2, r4
MobiClip_Code_020AB0B0:
    ldr r2, [lr, #0x10]
MobiClip_Code_020AB0B4:
    mla r4, r7, r3, r4
MobiClip_Code_020AB0B8:
    ldr r3, [lr, #0xc]
MobiClip_Code_020AB0BC:
    mla r4, r8, r2, r4
MobiClip_Code_020AB0C0:
    ldr r2, [lr, #8]
MobiClip_Code_020AB0C4:
    mla r4, sb, r3, r4
MobiClip_Code_020AB0C8:
    ldr r3, [lr, #4]
MobiClip_Code_020AB0CC:
    mla r4, sl, r2, r4
MobiClip_Code_020AB0D0:
    ldr r2, [lr]
MobiClip_Code_020AB0D4:
    mla r4, fp, r3, r4
MobiClip_Code_020AB0D8:
    mla r4, ip, r2, r4
MobiClip_Code_020AB0DC:
    asr r4, r4, #0xe
MobiClip_Code_020AB0E0:
    str r4, [lr]
MobiClip_Code_020AB0E4:
    str r4, [r1], #4
MobiClip_Code_020AB0E8:
    ldr r4, [r0], #4
MobiClip_Code_020AB0EC:
    ldr r3, [lr]
MobiClip_Code_020AB0F0:
    lsl r4, r4, #0xe
MobiClip_Code_020AB0F4:
    ldr r2, [lr, #0x1c]
MobiClip_Code_020AB0F8:
    mla r4, r5, r3, r4
MobiClip_Code_020AB0FC:
    ldr r3, [lr, #0x18]
MobiClip_Code_020AB100:
    mla r4, r6, r2, r4
MobiClip_Code_020AB104:
    ldr r2, [lr, #0x14]
MobiClip_Code_020AB108:
    mla r4, r7, r3, r4
MobiClip_Code_020AB10C:
    ldr r3, [lr, #0x10]
MobiClip_Code_020AB110:
    mla r4, r8, r2, r4
MobiClip_Code_020AB114:
    ldr r2, [lr, #0xc]
MobiClip_Code_020AB118:
    mla r4, sb, r3, r4
MobiClip_Code_020AB11C:
    ldr r3, [lr, #8]
MobiClip_Code_020AB120:
    mla r4, sl, r2, r4
MobiClip_Code_020AB124:
    ldr r2, [lr, #4]
MobiClip_Code_020AB128:
    mla r4, fp, r3, r4
MobiClip_Code_020AB12C:
    mla r4, ip, r2, r4
MobiClip_Code_020AB130:
    asr r4, r4, #0xe
MobiClip_Code_020AB134:
    str r4, [lr, #4]
MobiClip_Code_020AB138:
    str r4, [r1], #4
MobiClip_Code_020AB13C:
    ldr r4, [r0], #4
MobiClip_Code_020AB140:
    ldr r3, [lr, #4]
MobiClip_Code_020AB144:
    lsl r4, r4, #0xe
MobiClip_Code_020AB148:
    ldr r2, [lr]
MobiClip_Code_020AB14C:
    mla r4, r5, r3, r4
MobiClip_Code_020AB150:
    ldr r3, [lr, #0x1c]
MobiClip_Code_020AB154:
    mla r4, r6, r2, r4
MobiClip_Code_020AB158:
    ldr r2, [lr, #0x18]
MobiClip_Code_020AB15C:
    mla r4, r7, r3, r4
MobiClip_Code_020AB160:
    ldr r3, [lr, #0x14]
MobiClip_Code_020AB164:
    mla r4, r8, r2, r4
MobiClip_Code_020AB168:
    ldr r2, [lr, #0x10]
MobiClip_Code_020AB16C:
    mla r4, sb, r3, r4
MobiClip_Code_020AB170:
    ldr r3, [lr, #0xc]
MobiClip_Code_020AB174:
    mla r4, sl, r2, r4
MobiClip_Code_020AB178:
    ldr r2, [lr, #8]
MobiClip_Code_020AB17C:
    mla r4, fp, r3, r4
MobiClip_Code_020AB180:
    mla r4, ip, r2, r4
MobiClip_Code_020AB184:
    asr r4, r4, #0xe
MobiClip_Code_020AB188:
    str r4, [lr, #8]
MobiClip_Code_020AB18C:
    str r4, [r1], #4
MobiClip_Code_020AB190:
    ldr r4, [r0], #4
MobiClip_Code_020AB194:
    ldr r3, [lr, #8]
MobiClip_Code_020AB198:
    lsl r4, r4, #0xe
MobiClip_Code_020AB19C:
    ldr r2, [lr, #4]
MobiClip_Code_020AB1A0:
    mla r4, r5, r3, r4
MobiClip_Code_020AB1A4:
    ldr r3, [lr]
MobiClip_Code_020AB1A8:
    mla r4, r6, r2, r4
MobiClip_Code_020AB1AC:
    ldr r2, [lr, #0x1c]
MobiClip_Code_020AB1B0:
    mla r4, r7, r3, r4
MobiClip_Code_020AB1B4:
    ldr r3, [lr, #0x18]
MobiClip_Code_020AB1B8:
    mla r4, r8, r2, r4
MobiClip_Code_020AB1BC:
    ldr r2, [lr, #0x14]
MobiClip_Code_020AB1C0:
    mla r4, sb, r3, r4
MobiClip_Code_020AB1C4:
    ldr r3, [lr, #0x10]
MobiClip_Code_020AB1C8:
    mla r4, sl, r2, r4
MobiClip_Code_020AB1CC:
    ldr r2, [lr, #0xc]
MobiClip_Code_020AB1D0:
    mla r4, fp, r3, r4
MobiClip_Code_020AB1D4:
    mla r4, ip, r2, r4
MobiClip_Code_020AB1D8:
    asr r4, r4, #0xe
MobiClip_Code_020AB1DC:
    str r4, [lr, #0xc]
MobiClip_Code_020AB1E0:
    str r4, [r1], #4
MobiClip_Code_020AB1E4:
    ldr r4, [r0], #4
MobiClip_Code_020AB1E8:
    ldr r3, [lr, #0xc]
MobiClip_Code_020AB1EC:
    lsl r4, r4, #0xe
MobiClip_Code_020AB1F0:
    ldr r2, [lr, #8]
MobiClip_Code_020AB1F4:
    mla r4, r5, r3, r4
MobiClip_Code_020AB1F8:
    ldr r3, [lr, #4]
MobiClip_Code_020AB1FC:
    mla r4, r6, r2, r4
MobiClip_Code_020AB200:
    ldr r2, [lr]
MobiClip_Code_020AB204:
    mla r4, r7, r3, r4
MobiClip_Code_020AB208:
    ldr r3, [lr, #0x1c]
MobiClip_Code_020AB20C:
    mla r4, r8, r2, r4
MobiClip_Code_020AB210:
    ldr r2, [lr, #0x18]
MobiClip_Code_020AB214:
    mla r4, sb, r3, r4
MobiClip_Code_020AB218:
    ldr r3, [lr, #0x14]
MobiClip_Code_020AB21C:
    mla r4, sl, r2, r4
MobiClip_Code_020AB220:
    ldr r2, [lr, #0x10]
MobiClip_Code_020AB224:
    mla r4, fp, r3, r4
MobiClip_Code_020AB228:
    mla r4, ip, r2, r4
MobiClip_Code_020AB22C:
    asr r4, r4, #0xe
MobiClip_Code_020AB230:
    str r4, [lr, #0x10]
MobiClip_Code_020AB234:
    str r4, [r1], #4
MobiClip_Code_020AB238:
    ldr r4, [r0], #4
MobiClip_Code_020AB23C:
    ldr r3, [lr, #0x10]
MobiClip_Code_020AB240:
    lsl r4, r4, #0xe
MobiClip_Code_020AB244:
    ldr r2, [lr, #0xc]
MobiClip_Code_020AB248:
    mla r4, r5, r3, r4
MobiClip_Code_020AB24C:
    ldr r3, [lr, #8]
MobiClip_Code_020AB250:
    mla r4, r6, r2, r4
MobiClip_Code_020AB254:
    ldr r2, [lr, #4]
MobiClip_Code_020AB258:
    mla r4, r7, r3, r4
MobiClip_Code_020AB25C:
    ldr r3, [lr]
MobiClip_Code_020AB260:
    mla r4, r8, r2, r4
MobiClip_Code_020AB264:
    ldr r2, [lr, #0x1c]
MobiClip_Code_020AB268:
    mla r4, sb, r3, r4
MobiClip_Code_020AB26C:
    ldr r3, [lr, #0x18]
MobiClip_Code_020AB270:
    mla r4, sl, r2, r4
MobiClip_Code_020AB274:
    ldr r2, [lr, #0x14]
MobiClip_Code_020AB278:
    mla r4, fp, r3, r4
MobiClip_Code_020AB27C:
    mla r4, ip, r2, r4
MobiClip_Code_020AB280:
    asr r4, r4, #0xe
MobiClip_Code_020AB284:
    str r4, [lr, #0x14]
MobiClip_Code_020AB288:
    str r4, [r1], #4
MobiClip_Code_020AB28C:
    ldr r4, [r0], #4
MobiClip_Code_020AB290:
    ldr r3, [lr, #0x14]
MobiClip_Code_020AB294:
    lsl r4, r4, #0xe
MobiClip_Code_020AB298:
    ldr r2, [lr, #0x10]
MobiClip_Code_020AB29C:
    mla r4, r5, r3, r4
MobiClip_Code_020AB2A0:
    ldr r3, [lr, #0xc]
MobiClip_Code_020AB2A4:
    mla r4, r6, r2, r4
MobiClip_Code_020AB2A8:
    ldr r2, [lr, #8]
MobiClip_Code_020AB2AC:
    mla r4, r7, r3, r4
MobiClip_Code_020AB2B0:
    ldr r3, [lr, #4]
MobiClip_Code_020AB2B4:
    mla r4, r8, r2, r4
MobiClip_Code_020AB2B8:
    ldr r2, [lr]
MobiClip_Code_020AB2BC:
    mla r4, sb, r3, r4
MobiClip_Code_020AB2C0:
    ldr r3, [lr, #0x1c]
MobiClip_Code_020AB2C4:
    mla r4, sl, r2, r4
MobiClip_Code_020AB2C8:
    ldr r2, [lr, #0x18]
MobiClip_Code_020AB2CC:
    mla r4, fp, r3, r4
MobiClip_Code_020AB2D0:
    mla r4, ip, r2, r4
MobiClip_Code_020AB2D4:
    asr r4, r4, #0xe
MobiClip_Code_020AB2D8:
    str r4, [lr, #0x18]
MobiClip_Code_020AB2DC:
    str r4, [r1], #4
MobiClip_Code_020AB2E0:
    ldr r4, [r0], #4
MobiClip_Code_020AB2E4:
    ldr r3, [lr, #0x18]
MobiClip_Code_020AB2E8:
    lsl r4, r4, #0xe
MobiClip_Code_020AB2EC:
    ldr r2, [lr, #0x14]
MobiClip_Code_020AB2F0:
    mla r4, r5, r3, r4
MobiClip_Code_020AB2F4:
    ldr r3, [lr, #0x10]
MobiClip_Code_020AB2F8:
    mla r4, r6, r2, r4
MobiClip_Code_020AB2FC:
    ldr r2, [lr, #0xc]
MobiClip_Code_020AB300:
    mla r4, r7, r3, r4
MobiClip_Code_020AB304:
    ldr r3, [lr, #8]
MobiClip_Code_020AB308:
    mla r4, r8, r2, r4
MobiClip_Code_020AB30C:
    ldr r2, [lr, #4]
MobiClip_Code_020AB310:
    mla r4, sb, r3, r4
MobiClip_Code_020AB314:
    ldr r3, [lr]
MobiClip_Code_020AB318:
    mla r4, sl, r2, r4
MobiClip_Code_020AB31C:
    ldr r2, [lr, #0x1c]
MobiClip_Code_020AB320:
    mla r4, fp, r3, r4
MobiClip_Code_020AB324:
    mla r4, ip, r2, r4
MobiClip_Code_020AB328:
    asr r4, r4, #0xe
MobiClip_Code_020AB32C:
    str r4, [lr, #0x1c]
MobiClip_Code_020AB330:
    str r4, [r1], #4
MobiClip_Code_020AB334:
    pop {r2}
MobiClip_Code_020AB338:
    subs r2, r2, #8
MobiClip_Code_020AB33C:
    bne MobiClip_Code_020AB090
MobiClip_Code_020AB340:
    ldr r4, [sp]
MobiClip_Code_020AB344:
    str r1, [r4, #0x74]
MobiClip_Code_020AB348:
    pop {r1, r3, r4, pc}
    .global gMobiClipAudioAlign_AverageCoefficients
    .type gMobiClipAudioAlign_AverageCoefficients, %object
gMobiClipAudioAlign_AverageCoefficients:
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    /* MobiClip_AudioAverageCoefficients: r5-ip = (r5-ip + [r2]) / 2 */
MobiClip_Code_020AB354:
    push {r0, lr}
MobiClip_Code_020AB358:
    ldr r0, [r2], #4
MobiClip_Code_020AB35C:
    ldr lr, [r2], #4
MobiClip_Code_020AB360:
    add r5, r5, r0
MobiClip_Code_020AB364:
    add r6, r6, lr
MobiClip_Code_020AB368:
    ldr r0, [r2], #4
MobiClip_Code_020AB36C:
    ldr lr, [r2], #4
MobiClip_Code_020AB370:
    add r7, r7, r0
MobiClip_Code_020AB374:
    add r8, r8, lr
MobiClip_Code_020AB378:
    ldr r0, [r2], #4
MobiClip_Code_020AB37C:
    ldr lr, [r2], #4
MobiClip_Code_020AB380:
    add sb, sb, r0
MobiClip_Code_020AB384:
    add sl, sl, lr
MobiClip_Code_020AB388:
    ldr r0, [r2], #4
MobiClip_Code_020AB38C:
    ldr lr, [r2], #4
MobiClip_Code_020AB390:
    add fp, fp, r0
MobiClip_Code_020AB394:
    add ip, ip, lr
MobiClip_Code_020AB398:
    asr r5, r5, #1
MobiClip_Code_020AB39C:
    asr r6, r6, #1
MobiClip_Code_020AB3A0:
    asr r7, r7, #1
MobiClip_Code_020AB3A4:
    asr r8, r8, #1
MobiClip_Code_020AB3A8:
    asr sb, sb, #1
MobiClip_Code_020AB3AC:
    asr sl, sl, #1
MobiClip_Code_020AB3B0:
    asr fp, fp, #1
MobiClip_Code_020AB3B4:
    asr ip, ip, #1
MobiClip_Code_020AB3B8:
    pop {r0, pc}
    .global gMobiClipAudioAlign_SynthesiseSubframes
    .type gMobiClipAudioAlign_SynthesiseSubframes, %object
gMobiClipAudioAlign_SynthesiseSubframes:
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    /* MobiClip_AudioSynthesiseSubframes: four 32-sample subframes, interpolated coefficients */
MobiClip_Code_020AB3C4:
    push {r1, r4, lr}
MobiClip_Code_020AB3C8:
    ldr r2, [r1, #0x6c]
MobiClip_Code_020AB3CC:
    cmp r2, #1
MobiClip_Code_020AB3D0:
    add r0, r3, #0x200
MobiClip_Code_020AB3D4:
    str r4, [r1, #0x74]
MobiClip_Code_020AB3D8:
    addne r3, r1, #0x28
MobiClip_Code_020AB3DC:
    addne r4, r3, #0x20
MobiClip_Code_020AB3E0:
    addeq r4, r1, #0x28
MobiClip_Code_020AB3E4:
    addeq r3, r4, #0x20
MobiClip_Code_020AB3E8:
    stm r3, {r5, r6, r7, r8, sb, sl, fp, ip}
MobiClip_Code_020AB3EC:
    mov r2, r4
MobiClip_Code_020AB3F0:
    bl MobiClip_Code_020AB354
MobiClip_Code_020AB3F4:
    push {r5, r6, r7, r8, sb, sl, fp, ip}
MobiClip_Code_020AB3F8:
    mov r2, r4
MobiClip_Code_020AB3FC:
    bl MobiClip_Code_020AB354
MobiClip_Code_020AB400:
    mov r2, #0x20
MobiClip_Code_020AB404:
    bl MobiClip_Code_020AB084
MobiClip_Code_020AB408:
    pop {r5, r6, r7, r8, sb, sl, fp, ip}
MobiClip_Code_020AB40C:
    mov r2, #0x20
MobiClip_Code_020AB410:
    bl MobiClip_Code_020AB084
MobiClip_Code_020AB414:
    mov r2, r3
MobiClip_Code_020AB418:
    bl MobiClip_Code_020AB354
MobiClip_Code_020AB41C:
    mov r2, #0x20
MobiClip_Code_020AB420:
    bl MobiClip_Code_020AB084
MobiClip_Code_020AB424:
    ldm r3, {r5, r6, r7, r8, sb, sl, fp, ip}
MobiClip_Code_020AB428:
    mov r2, #0x20
MobiClip_Code_020AB42C:
    bl MobiClip_Code_020AB084
MobiClip_Code_020AB430:
    pop {r1, r4, pc}
    /* MobiClip_AudioResetChannel: gain, buffer toggle and filter history */
MobiClip_Code_020AB434:
    add r8, r1, #0x8c0
MobiClip_Code_020AB438:
    ldr r7, [r8, #0xc30]
MobiClip_Code_020AB43C:
    mov sb, #1
MobiClip_Code_020AB440:
    str r7, [r1, #0x68]
MobiClip_Code_020AB444:
    mov r7, #8
MobiClip_Code_020AB448:
    str sb, [r1, #0x6c]
MobiClip_Code_020AB44C:
    add r8, r1, #0x78
MobiClip_Code_020AB450:
    mov sb, #0
MobiClip_Code_020AB454:
    str sb, [r8], #4
MobiClip_Code_020AB458:
    subs r7, r7, #1
MobiClip_Code_020AB45C:
    bne MobiClip_Code_020AB454
MobiClip_Code_020AB460:
    mov pc, lr
    /* MobiClip_AudioDecodeFrame: decode one frame, saturate 128 samples to s16 */
MobiClip_Code_020AB464:
    push {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_020AB468:
    mov r1, r0
MobiClip_Code_020AB46C:
    ldr r0, [r0]
MobiClip_Code_020AB470:
    ldrh r5, [r0], #2
MobiClip_Code_020AB474:
    lsr r6, r5, #9
MobiClip_Code_020AB478:
    cmp r6, #0x7f
MobiClip_Code_020AB47C:
    bleq MobiClip_Code_020AB574
MobiClip_Code_020AB480:
    blne MobiClip_Code_020AB5B4
MobiClip_Code_020AB484:
    ldr r7, [r1, #0x6c]
MobiClip_Code_020AB488:
    eor r7, r7, #1
MobiClip_Code_020AB48C:
    str r7, [r1, #0x6c]
MobiClip_Code_020AB490:
    add r3, r1, #0x1000
MobiClip_Code_020AB494:
    ldr r2, [r1, #4]
MobiClip_Code_020AB498:
    mov r0, #0x80
MobiClip_Code_020AB49C:
    ldr r5, gMobiClipAudioSampleMax
MobiClip_Code_020AB4A0:
    ldr r6, gMobiClipAudioSampleMin
MobiClip_Code_020AB4A4:
    ldr r3, [r3, #0x4f4]
MobiClip_Code_020AB4A8:
    ldr r7, [r4], #4
MobiClip_Code_020AB4AC:
    cmp r7, r5
MobiClip_Code_020AB4B0:
    movgt r7, r5
MobiClip_Code_020AB4B4:
    cmp r7, r6
MobiClip_Code_020AB4B8:
    movlt r7, r6
MobiClip_Code_020AB4BC:
    strh r7, [r2], r3
MobiClip_Code_020AB4C0:
    subs r0, r0, #1
MobiClip_Code_020AB4C4:
    bne MobiClip_Code_020AB4A8
MobiClip_Code_020AB4C8:
    ldrb r0, [r1, #0x73]
MobiClip_Code_020AB4CC:
    adr r2, gMobiClipAudioFrameBytes
MobiClip_Code_020AB4D0:
    ldrb r0, [r2, r0]
MobiClip_Code_020AB4D4:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_020AB4D8:
    bx lr
    /* pulse modes 1, 2, 3: (halfwords of two-bit pulses, store step in bytes) */
    .global gMobiClipAudioPulseLayout
    .type gMobiClipAudioPulseLayout, %object
gMobiClipAudioPulseLayout:
    .byte 0x05, 0x0c, 0x04, 0x10, 0x03, 0x14
    /* bytes one frame consumes, by pulse mode 0-3 */
    .global gMobiClipAudioFrameBytes
    .type gMobiClipAudioFrameBytes, %object
gMobiClipAudioFrameBytes:
    .byte 0x14, 0x0e, 0x0c, 0x0a
    .global gMobiClipAudioAlign_ReadFrameHeader
    .type gMobiClipAudioAlign_ReadFrameHeader, %object
gMobiClipAudioAlign_ReadFrameHeader:
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    /* MobiClip_AudioReadFrameHeader: gain, codebook indices, pulse mode */
MobiClip_Code_020AB4F4:
    push {r1, lr}
MobiClip_Code_020AB4F8:
    add ip, r1, #0x70
MobiClip_Code_020AB4FC:
    lsr r6, r5, #6
MobiClip_Code_020AB500:
    and r6, r6, #7
MobiClip_Code_020AB504:
    and r5, r5, #0x3f
MobiClip_Code_020AB508:
    strb r5, [ip], #1
MobiClip_Code_020AB50C:
    ldrh r5, [r0], #2
MobiClip_Code_020AB510:
    add r8, r1, #0x14c0
MobiClip_Code_020AB514:
    lsr r7, r5, #0xe
MobiClip_Code_020AB518:
    and r7, r7, #3
MobiClip_Code_020AB51C:
    add r6, r8, r6, lsl #1
MobiClip_Code_020AB520:
    ldrsh r8, [r6]
MobiClip_Code_020AB524:
    ldr r6, [r1, #0x68]
MobiClip_Code_020AB528:
    lsr fp, r5, #0xc
MobiClip_Code_020AB52C:
    mul r6, r8, r6
MobiClip_Code_020AB530:
    lsr sl, r5, #6
MobiClip_Code_020AB534:
    asr r6, r6, #0xd
MobiClip_Code_020AB538:
    str r6, [r1, #0x68]
MobiClip_Code_020AB53C:
    and sl, sl, #0x3f
MobiClip_Code_020AB540:
    strb sl, [ip], #1
MobiClip_Code_020AB544:
    and r5, r5, #0x3f
MobiClip_Code_020AB548:
    strb r5, [ip]
MobiClip_Code_020AB54C:
    ands fp, fp, #3
MobiClip_Code_020AB550:
    strb fp, [r1, #0x73]
MobiClip_Code_020AB554:
    beq MobiClip_Code_020AAE34
MobiClip_Code_020AB558:
    adr sl, gMobiClipAudioPulseLayout - 2  /* indexed by pulse mode 1-3 */
MobiClip_Code_020AB55C:
    add sl, sl, fp, lsl #1
MobiClip_Code_020AB560:
    ldrb r8, [sl]
MobiClip_Code_020AB564:
    ldrb sb, [sl, #1]
MobiClip_Code_020AB568:
    b MobiClip_Code_020AADE4
    .global gMobiClipAudioAlign_DecodeResetFrame
    .type gMobiClipAudioAlign_DecodeResetFrame, %object
gMobiClipAudioAlign_DecodeResetFrame:
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    /* MobiClip_AudioDecodeResetFrame: lag 127, start from the default coefficients */
MobiClip_Code_020AB574:
    push {r1, lr}
MobiClip_Code_020AB578:
    bl MobiClip_Code_020AB434
MobiClip_Code_020AB57C:
    add r4, r1, #0xc0
MobiClip_Code_020AB580:
    add r3, r4, #0x400
MobiClip_Code_020AB584:
    bl MobiClip_Code_020AAC64
MobiClip_Code_020AB588:
    bl MobiClip_Code_020AB4F4
MobiClip_Code_020AB58C:
    add r2, r1, #0x8c0
MobiClip_Code_020AB590:
    add r2, r2, #0xc10
MobiClip_Code_020AB594:
    bl MobiClip_Code_020AAEC4
MobiClip_Code_020AB598:
    add r2, r1, #0x48
MobiClip_Code_020AB59C:
    stm r2, {r5, r6, r7, r8, sb, sl, fp, ip}
MobiClip_Code_020AB5A0:
    str r4, [r1, #0x74]
MobiClip_Code_020AB5A4:
    add r0, r3, #0x200
MobiClip_Code_020AB5A8:
    mov r2, #0x80
MobiClip_Code_020AB5AC:
    bl MobiClip_Code_020AB084
MobiClip_Code_020AB5B0:
    pop {r1, pc}
    /* MobiClip_AudioDecodeNextFrame: rotate the excitation history and predict */
MobiClip_Code_020AB5B4:
    push {r1, lr}
MobiClip_Code_020AB5B8:
    mov r7, #0x400
MobiClip_Code_020AB5BC:
    ldr r2, [r1, #0x6c]
MobiClip_Code_020AB5C0:
    add r8, r1, #0xc0
MobiClip_Code_020AB5C4:
    mla r3, r2, r7, r8
MobiClip_Code_020AB5C8:
    eor r2, r2, #1
MobiClip_Code_020AB5CC:
    mla r4, r2, r7, r8
MobiClip_Code_020AB5D0:
    mov r8, r3
MobiClip_Code_020AB5D4:
    add r7, r4, #0x200
MobiClip_Code_020AB5D8:
    mov r2, #0x20
MobiClip_Code_020AB5DC:
    ldm r7!, {sb, sl, fp, ip}
MobiClip_Code_020AB5E0:
    stm r8!, {sb, sl, fp, ip}
MobiClip_Code_020AB5E4:
    subs r2, r2, #1
MobiClip_Code_020AB5E8:
    bne MobiClip_Code_020AB5DC
MobiClip_Code_020AB5EC:
    cmp r6, #0x7e
MobiClip_Code_020AB5F0:
    bleq MobiClip_Code_020AAC64
MobiClip_Code_020AB5F4:
    blne MobiClip_Code_020AAC94
MobiClip_Code_020AB5F8:
    bl MobiClip_Code_020AB4F4
MobiClip_Code_020AB5FC:
    add r2, r1, #8
MobiClip_Code_020AB600:
    bl MobiClip_Code_020AAEC4
MobiClip_Code_020AB604:
    bl MobiClip_Code_020AB3C4
MobiClip_Code_020AB608:
    pop {r1, pc}
    /* saturation bounds of the output stage: 0x7fff and -0x8000 */
    .global gMobiClipAudioSampleMax
    .type gMobiClipAudioSampleMax, %object
gMobiClipAudioSampleMax:
    .byte 0xff, 0x7f, 0x00, 0x00
    .global gMobiClipAudioSampleMin
    .type gMobiClipAudioSampleMin, %object
gMobiClipAudioSampleMin:
    .byte 0x00, 0x80, 0xff, 0xff
    .size MobiClip_AudioTransformDecode, . - MobiClip_AudioTransformDecode
