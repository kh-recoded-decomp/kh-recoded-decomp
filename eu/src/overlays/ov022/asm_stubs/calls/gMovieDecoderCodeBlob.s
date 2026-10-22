/* MobiClip video decoder payload. Position-independent hand-written ARM that the player copies into
 * its work arena and runs from there: the header and dispatch tables (self-relative words) come first,
 * followed by the bitstream parsers, the run/level and intra-prediction routines, the motion
 * interpolators and the inverse transforms. Code and data follow the control flow. */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global gMovieDecoderCodeBlob
    .type gMovieDecoderCodeBlob, %function
gMovieDecoderCodeBlob:
MobiClip_Code_020B0BC0:
    b MobiClip_Code_020B22B0
    /* control metadata 0x0208c8c8..0x0208c8d0 */
    .global gMobiClip_payload_header
    .type gMobiClip_payload_header, %object
gMobiClip_payload_header:
    /* payload_configuration */
    .byte 0x00, 0x01, 0x00, 0x00, 0x9e, 0x00, 0x00, 0x00
    /* control metadata 0x0208c8d0..0x0208c910 */
    .global gMobiClip_luma_interpolation_dispatch
    .type gMobiClip_luma_interpolation_dispatch, %object
gMobiClip_luma_interpolation_dispatch:
    /* luma_interpolation */
    .global gMobiClip_luma_interpolation
gMobiClip_luma_interpolation:
    .word MobiClip_Code_020B55B4 - .
    .word MobiClip_Code_020b5660 - . + 0x4
    .word MobiClip_Code_020B57EC - . + 0x8
    .word MobiClip_Code_020b592c - . + 0xc
    .word MobiClip_Code_020b5b40 - . + 0x10
    .word MobiClip_Code_020b5c80 - . + 0x14
    .word MobiClip_Code_020B5E84 - . + 0x18
    .word MobiClip_Code_020B5FB4 - . + 0x1c
    .word MobiClip_Code_020B55D0 - . + 0x20
    .word MobiClip_Code_020B56B8 - . + 0x24
    .word MobiClip_Code_020b5830 - . + 0x28
    .word MobiClip_Code_020B59A8 - . + 0x2c
    .word MobiClip_Code_020b5b84 - . + 0x30
    .word MobiClip_Code_020B5CF8 - . + 0x34
    .word MobiClip_Code_020B5EC4 - . + 0x38
    .word MobiClip_Code_020B6010 - . + 0x3c
    /* control metadata 0x0208c910..0x0208c950 */
    .global gMobiClip_chroma_interpolation_dispatch
    .type gMobiClip_chroma_interpolation_dispatch, %object
gMobiClip_chroma_interpolation_dispatch:
    /* chroma_interpolation */
    .global gMobiClip_chroma_interpolation
gMobiClip_chroma_interpolation:
    .word MobiClip_Code_020B614C - .
    .word MobiClip_Code_020B61D0 - . + 0x4
    .word MobiClip_Code_020B62D8 - . + 0x8
    .word MobiClip_Code_020B63B4 - . + 0xc
    .word MobiClip_Code_020b6504 - . + 0x10
    .word MobiClip_Code_020B65D8 - . + 0x14
    .word MobiClip_Code_020B6718 - . + 0x18
    .word MobiClip_Code_020B67E4 - . + 0x1c
    .word MobiClip_Code_020B6168 - . + 0x20
    .word MobiClip_Code_020B6210 - . + 0x24
    .word MobiClip_Code_020b630c - . + 0x28
    .word MobiClip_Code_020B6408 - . + 0x2c
    .word MobiClip_Code_020b6534 - . + 0x30
    .word MobiClip_Code_020B6628 - . + 0x34
    .word MobiClip_Code_020B6748 - . + 0x38
    .word MobiClip_Code_020B6828 - . + 0x3c
MobiClip_Code_020B0C4C:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B0C50:
    bl MobiClip_Code_020B2C38
MobiClip_Code_020B0C54:
    mov r5, r6
MobiClip_Code_020B0C58:
    bl MobiClip_Code_020B2C38
MobiClip_Code_020B0C5C:
    add sb, r0, #0x3bc
MobiClip_Code_020B0C60:
    ldm sb, {r7, r8}
MobiClip_Code_020B0C64:
    add r5, r5, r7
MobiClip_Code_020B0C68:
    add r6, r6, r8
MobiClip_Code_020B0C6C:
    stm r4, {r5, r6}
MobiClip_Code_020B0C70:
    add r7, r5, fp, lsl #1
MobiClip_Code_020B0C74:
    and r7, r7, #7
MobiClip_Code_020B0C78:
    and r8, r6, #1
MobiClip_Code_020B0C7C:
    add r7, r7, r8, lsl #3
MobiClip_Code_020B0C80:
    push {r0, r1, r2, r3}
MobiClip_Code_020B0C84:
    ldr r2, [sp, #0x14]
MobiClip_Code_020B0C88:
    ldr r1, [r0, #0xc]
MobiClip_Code_020B0C8C:
    add r0, r0, r2
MobiClip_Code_020B0C90:
    ldr r0, [r0, #0xc]
MobiClip_Code_020B0C94:
    asr r8, r6, #1
MobiClip_Code_020B0C98:
    add r0, r0, fp
MobiClip_Code_020B0C9C:
    add r0, r0, r8, lsl #8
MobiClip_Code_020B0CA0:
    add r0, r0, r5, asr #1
MobiClip_Code_020B0CA4:
    add r1, r1, fp
MobiClip_Code_020B0CA8:
    ldr r2, [sp, #0x18]
MobiClip_Code_020B0CAC:
    sub r3, pc, #0xe8
MobiClip_Code_020B0CB0:
    add lr, pc, #4
MobiClip_Code_020B0CB4:
    ldr r8, [r3, r7, lsl #2]
MobiClip_Code_020B0CB8:
    add pc, r8, r3
MobiClip_Code_020B0CBC:
    ldr r0, [sp]
MobiClip_Code_020B0CC0:
    ldr r2, [sp, #0x14]
MobiClip_Code_020B0CC4:
    ldr r1, [r0, #0x24]
MobiClip_Code_020B0CC8:
    add r0, r0, r2
MobiClip_Code_020B0CCC:
    ldr r0, [r0, #0x24]
MobiClip_Code_020B0CD0:
    asr r8, r6, #2
MobiClip_Code_020B0CD4:
    add r0, r0, fp, lsr #1
MobiClip_Code_020B0CD8:
    add r0, r0, r8, lsl #8
MobiClip_Code_020B0CDC:
    add r0, r0, r5, asr #2
MobiClip_Code_020B0CE0:
    add r1, r1, fp, lsr #1
MobiClip_Code_020B0CE4:
    ldr r2, [sp, #0x18]
MobiClip_Code_020B0CE8:
    lsr r2, r2, #1
MobiClip_Code_020B0CEC:
    sub r3, pc, #0xe8
MobiClip_Code_020B0CF0:
    add r5, r5, fp, lsl #1
MobiClip_Code_020B0CF4:
    asr r5, r5, #1
MobiClip_Code_020B0CF8:
    and r5, r5, #7
MobiClip_Code_020B0CFC:
    asr r8, r6, #1
MobiClip_Code_020B0D00:
    and r8, r8, #1
MobiClip_Code_020B0D04:
    add r5, r5, r8, lsl #3
MobiClip_Code_020B0D08:
    add lr, pc, #8
MobiClip_Code_020B0D0C:
    mov r6, r0
MobiClip_Code_020B0D10:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_020B0D14:
    add pc, r8, r3
MobiClip_Code_020B0D18:
    ldr r2, [sp, #0x18]
MobiClip_Code_020B0D1C:
    lsr r2, r2, #1
MobiClip_Code_020B0D20:
    add r0, r6, #0x80
MobiClip_Code_020B0D24:
    sub r1, r1, r2, lsl #8
MobiClip_Code_020B0D28:
    add r1, r1, #0x80
MobiClip_Code_020B0D2C:
    sub r3, pc, #0x128
MobiClip_Code_020B0D30:
    add lr, pc, #4
MobiClip_Code_020B0D34:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_020B0D38:
    add pc, r8, r3
MobiClip_Code_020B0D3C:
    pop {r0, r1, r2, r3, r4, r5, r6, fp, ip, pc}
    /* control metadata 0x0208ca44..0x0208ca98 */
    .global gMobiClip_pframe_prefix_offsets_and_lengths
    .type gMobiClip_pframe_prefix_offsets_and_lengths, %object
gMobiClip_pframe_prefix_offsets_and_lengths:
    /* pframe_prefix_codes */
    .byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x08, 0x08, 0x08, 0x08, 0x09, 0x09, 0x09, 0x09
    .byte 0x04, 0x03, 0x02, 0x02, 0x07, 0x07, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    /* pframe_macroblock */
    .global gMobiClip_pframe_macroblock
gMobiClip_pframe_macroblock:
    .word MobiClip_Code_020B0D94 - .
    .word MobiClip_Code_020B0DBC - . + 0x4
    .word MobiClip_Code_020B0DD4 - . + 0x8
    .word MobiClip_Code_020B0DEC - . + 0xc
    .word MobiClip_Code_020B0E04 - . + 0x10
    .word MobiClip_Code_020B0E1C - . + 0x14
    .word MobiClip_Code_020B24C4 - . + 0x18
    .word MobiClip_Code_020B2588 - . + 0x1c
    .word MobiClip_Code_020B0E34 - . + 0x20
    .word MobiClip_Code_020B0E50 - . + 0x24
    /* pframe_code_lengths */
    .byte 0x02, 0x02, 0x04, 0x05, 0x05, 0x05, 0x05, 0x04, 0x03, 0x03, 0x00, 0x00
MobiClip_Code_020B0D94:
    str lr, [sp, #-4]!
MobiClip_Code_020B0D98:
    mov r5, #4
MobiClip_Code_020B0D9C:
    mov r6, #0x10
MobiClip_Code_020B0DA0:
    add lr, pc, #0xc
MobiClip_Code_020B0DA4:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B0DA8:
    add sb, r0, #0x3bc
MobiClip_Code_020B0DAC:
    ldm sb, {r5, r6}
MobiClip_Code_020B0DB0:
    b MobiClip_Code_020B0C6C
MobiClip_Code_020B0DB4:
    bl MobiClip_Code_020B2660
MobiClip_Code_020B0DB8:
    pop {pc}
MobiClip_Code_020B0DBC:
    str lr, [sp, #-4]!
MobiClip_Code_020B0DC0:
    mov r5, #4
MobiClip_Code_020B0DC4:
    mov r6, #0x10
MobiClip_Code_020B0DC8:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B0DCC:
    bl MobiClip_Code_020B2660
MobiClip_Code_020B0DD0:
    pop {pc}
MobiClip_Code_020B0DD4:
    str lr, [sp, #-4]!
MobiClip_Code_020B0DD8:
    mov r5, #8
MobiClip_Code_020B0DDC:
    mov r6, #0x10
MobiClip_Code_020B0DE0:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B0DE4:
    bl MobiClip_Code_020B2660
MobiClip_Code_020B0DE8:
    pop {pc}
MobiClip_Code_020B0DEC:
    str lr, [sp, #-4]!
MobiClip_Code_020B0DF0:
    mov r5, #0xc
MobiClip_Code_020B0DF4:
    mov r6, #0x10
MobiClip_Code_020B0DF8:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B0DFC:
    bl MobiClip_Code_020B2660
MobiClip_Code_020B0E00:
    pop {pc}
MobiClip_Code_020B0E04:
    str lr, [sp, #-4]!
MobiClip_Code_020B0E08:
    mov r5, #0x10
MobiClip_Code_020B0E0C:
    mov r6, #0x10
MobiClip_Code_020B0E10:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B0E14:
    bl MobiClip_Code_020B2660
MobiClip_Code_020B0E18:
    pop {pc}
MobiClip_Code_020B0E1C:
    str lr, [sp, #-4]!
MobiClip_Code_020B0E20:
    mov r5, #0x14
MobiClip_Code_020B0E24:
    mov r6, #0x10
MobiClip_Code_020B0E28:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B0E2C:
    bl MobiClip_Code_020B2660
MobiClip_Code_020B0E30:
    pop {pc}
MobiClip_Code_020B0E34:
    str lr, [sp, #-4]!
MobiClip_Code_020B0E38:
    bl MobiClip_Code_020B1648
MobiClip_Code_020B0E3C:
    add fp, fp, #0x800
MobiClip_Code_020B0E40:
    bl MobiClip_Code_020B1648
MobiClip_Code_020B0E44:
    sub fp, fp, #0x800
MobiClip_Code_020B0E48:
    bl MobiClip_Code_020B2660
MobiClip_Code_020B0E4C:
    pop {pc}
MobiClip_Code_020B0E50:
    str lr, [sp, #-4]!
MobiClip_Code_020B0E54:
    bl MobiClip_Code_020B10C4
MobiClip_Code_020B0E58:
    add fp, fp, #8
MobiClip_Code_020B0E5C:
    bl MobiClip_Code_020B10C4
MobiClip_Code_020B0E60:
    sub fp, fp, #8
MobiClip_Code_020B0E64:
    bl MobiClip_Code_020B2660
MobiClip_Code_020B0E68:
    pop {pc}
MobiClip_Code_020B0E6C:
    lsr r6, r3, #0x1b
MobiClip_Code_020B0E70:
    sub r5, pc, #0x138
MobiClip_Code_020B0E74:
    ldrb r5, [r5, r6]
MobiClip_Code_020B0E78:
    sub r6, pc, #0xf8
MobiClip_Code_020B0E7C:
    ldrb r6, [r6, r5]
MobiClip_Code_020B0E80:
    lsl r3, r3, r6
MobiClip_Code_020B0E84:
    subs r2, r2, r6
MobiClip_Code_020B0E88:
    mov r8, lr
MobiClip_Code_020B0E8C:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B0E90:
    sub r6, pc, #0x138
MobiClip_Code_020B0E94:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B0E98:
    mov lr, r8
MobiClip_Code_020B0E9C:
    add pc, r5, r6
    /* control metadata 0x0208cba4..0x0208cbe4 */
    .global gMobiClip_luma_kernel_dispatch
    .type gMobiClip_luma_kernel_dispatch, %object
gMobiClip_luma_kernel_dispatch:
    /* motion16_dispatch */
    .global gMobiClip_motion16_dispatch
gMobiClip_motion16_dispatch:
    .word MobiClip_Code_020B68F8 - .
    .word MobiClip_Code_020b694c - . + 0x4
    .word MobiClip_Code_020b6a04 - . + 0x8
    .word MobiClip_Code_020B6AA0 - . + 0xc
    .word MobiClip_Code_020b6b80 - . + 0x10
    .word MobiClip_Code_020b6c04 - . + 0x14
    .word MobiClip_Code_020B6CC4 - . + 0x18
    .word MobiClip_Code_020B6D40 - . + 0x1c
    .word MobiClip_Code_020b690c - . + 0x20
    .word MobiClip_Code_020b697c - . + 0x24
    .word MobiClip_Code_020b6a2c - . + 0x28
    .word MobiClip_Code_020B6ADC - . + 0x2c
    .word MobiClip_Code_020B6BA0 - . + 0x30
    .word MobiClip_Code_020B6C38 - . + 0x34
    .word MobiClip_Code_020B6CE4 - . + 0x38
    .word MobiClip_Code_020B6D70 - . + 0x3c
MobiClip_Code_020B0EE0:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B0EE4:
    bl MobiClip_Code_020B2C38
MobiClip_Code_020B0EE8:
    mov r5, r6
MobiClip_Code_020B0EEC:
    bl MobiClip_Code_020B2C38
MobiClip_Code_020B0EF0:
    add sb, r0, #0x3bc
MobiClip_Code_020B0EF4:
    ldm sb, {r7, r8}
MobiClip_Code_020B0EF8:
    add r5, r5, r7
MobiClip_Code_020B0EFC:
    add r6, r6, r8
MobiClip_Code_020B0F00:
    stm r4, {r5, r6}
MobiClip_Code_020B0F04:
    add r7, r5, fp, lsl #1
MobiClip_Code_020B0F08:
    and r7, r7, #7
MobiClip_Code_020B0F0C:
    and r8, r6, #1
MobiClip_Code_020B0F10:
    add r7, r7, r8, lsl #3
MobiClip_Code_020B0F14:
    push {r0, r1, r2, r3}
MobiClip_Code_020B0F18:
    ldr r2, [sp, #0x14]
MobiClip_Code_020B0F1C:
    ldr r1, [r0, #0xc]
MobiClip_Code_020B0F20:
    add r0, r0, r2
MobiClip_Code_020B0F24:
    ldr r0, [r0, #0xc]
MobiClip_Code_020B0F28:
    asr r8, r6, #1
MobiClip_Code_020B0F2C:
    add r0, r0, fp
MobiClip_Code_020B0F30:
    add r0, r0, r8, lsl #8
MobiClip_Code_020B0F34:
    add r0, r0, r5, asr #1
MobiClip_Code_020B0F38:
    add r1, r1, fp
MobiClip_Code_020B0F3C:
    ldr r2, [sp, #0x18]
MobiClip_Code_020B0F40:
    sub r3, pc, #0x33c
MobiClip_Code_020B0F44:
    add lr, pc, #4
MobiClip_Code_020B0F48:
    ldr r8, [r3, r7, lsl #2]
MobiClip_Code_020B0F4C:
    add pc, r8, r3
MobiClip_Code_020B0F50:
    ldr r0, [sp]
MobiClip_Code_020B0F54:
    ldr r2, [sp, #0x14]
MobiClip_Code_020B0F58:
    ldr r1, [r0, #0x24]
MobiClip_Code_020B0F5C:
    add r0, r0, r2
MobiClip_Code_020B0F60:
    ldr r0, [r0, #0x24]
MobiClip_Code_020B0F64:
    asr r8, r6, #2
MobiClip_Code_020B0F68:
    add r0, r0, fp, lsr #1
MobiClip_Code_020B0F6C:
    add r0, r0, r8, lsl #8
MobiClip_Code_020B0F70:
    add r0, r0, r5, asr #2
MobiClip_Code_020B0F74:
    add r1, r1, fp, lsr #1
MobiClip_Code_020B0F78:
    ldr r2, [sp, #0x18]
MobiClip_Code_020B0F7C:
    lsr r2, r2, #1
MobiClip_Code_020B0F80:
    sub r3, pc, #0xe8
MobiClip_Code_020B0F84:
    add r5, r5, fp, lsl #1
MobiClip_Code_020B0F88:
    asr r5, r5, #1
MobiClip_Code_020B0F8C:
    and r5, r5, #7
MobiClip_Code_020B0F90:
    asr r8, r6, #1
MobiClip_Code_020B0F94:
    and r8, r8, #1
MobiClip_Code_020B0F98:
    add r5, r5, r8, lsl #3
MobiClip_Code_020B0F9C:
    add lr, pc, #8
MobiClip_Code_020B0FA0:
    mov r6, r0
MobiClip_Code_020B0FA4:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_020B0FA8:
    add pc, r8, r3
MobiClip_Code_020B0FAC:
    ldr r2, [sp, #0x18]
MobiClip_Code_020B0FB0:
    lsr r2, r2, #1
MobiClip_Code_020B0FB4:
    add r0, r6, #0x80
MobiClip_Code_020B0FB8:
    sub r1, r1, r2, lsl #8
MobiClip_Code_020B0FBC:
    add r1, r1, #0x80
MobiClip_Code_020B0FC0:
    sub r3, pc, #0x128
MobiClip_Code_020B0FC4:
    add lr, pc, #4
MobiClip_Code_020B0FC8:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_020B0FCC:
    add pc, r8, r3
MobiClip_Code_020B0FD0:
    pop {r0, r1, r2, r3, r4, r5, r6, fp, ip, pc}
    /* control metadata 0x0208ccd8..0x0208cd1c */
    .global gMobiClip_motion16_selector_and_offsets
    .type gMobiClip_motion16_selector_and_offsets, %object
gMobiClip_motion16_selector_and_offsets:
    /* motion16_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x09, 0x09, 0x05, 0x04, 0x02, 0x02, 0x03, 0x08, 0x01, 0x01, 0x01, 0x01
    /* motion16_modes */
    .global gMobiClip_motion16_modes
gMobiClip_motion16_modes:
    .word MobiClip_Code_020B1018 - .
    .word MobiClip_Code_020B1030 - . + 0x4
    .word MobiClip_Code_020B1044 - . + 0x8
    .word MobiClip_Code_020B1058 - . + 0xc
    .word MobiClip_Code_020B106C - . + 0x10
    .word MobiClip_Code_020B1080 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_020B1094 - . + 0x20
    .word MobiClip_Code_020B10AC - . + 0x24
    /* motion16_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x04, 0x04, 0x04, 0x00, 0x00, 0x04, 0x03, 0x00, 0x00
MobiClip_Code_020B1018:
    mov r5, #4
MobiClip_Code_020B101C:
    mov r6, #0x10
MobiClip_Code_020B1020:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B1024:
    add sb, r0, #0x3bc
MobiClip_Code_020B1028:
    ldm sb, {r5, r6}
MobiClip_Code_020B102C:
    b MobiClip_Code_020B0F00
MobiClip_Code_020B1030:
    str lr, [sp, #-4]!
MobiClip_Code_020B1034:
    mov r5, #4
MobiClip_Code_020B1038:
    mov r6, #0x10
MobiClip_Code_020B103C:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1040:
    pop {pc}
MobiClip_Code_020B1044:
    str lr, [sp, #-4]!
MobiClip_Code_020B1048:
    mov r5, #8
MobiClip_Code_020B104C:
    mov r6, #0x10
MobiClip_Code_020B1050:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1054:
    pop {pc}
MobiClip_Code_020B1058:
    str lr, [sp, #-4]!
MobiClip_Code_020B105C:
    mov r5, #0xc
MobiClip_Code_020B1060:
    mov r6, #0x10
MobiClip_Code_020B1064:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1068:
    pop {pc}
MobiClip_Code_020B106C:
    str lr, [sp, #-4]!
MobiClip_Code_020B1070:
    mov r5, #0x10
MobiClip_Code_020B1074:
    mov r6, #0x10
MobiClip_Code_020B1078:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B107C:
    pop {pc}
MobiClip_Code_020B1080:
    str lr, [sp, #-4]!
MobiClip_Code_020B1084:
    mov r5, #0x14
MobiClip_Code_020B1088:
    mov r6, #0x10
MobiClip_Code_020B108C:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1090:
    pop {pc}
MobiClip_Code_020B1094:
    str lr, [sp, #-4]!
MobiClip_Code_020B1098:
    bl MobiClip_Code_020B199C
MobiClip_Code_020B109C:
    add fp, fp, #0x800
MobiClip_Code_020B10A0:
    bl MobiClip_Code_020B199C
MobiClip_Code_020B10A4:
    sub fp, fp, #0x800
MobiClip_Code_020B10A8:
    pop {pc}
MobiClip_Code_020B10AC:
    str lr, [sp, #-4]!
MobiClip_Code_020B10B0:
    bl MobiClip_Code_020B12FC
MobiClip_Code_020B10B4:
    add fp, fp, #4
MobiClip_Code_020B10B8:
    bl MobiClip_Code_020B12FC
MobiClip_Code_020B10BC:
    sub fp, fp, #4
MobiClip_Code_020B10C0:
    pop {pc}
MobiClip_Code_020B10C4:
    lsr r6, r3, #0x1c
MobiClip_Code_020B10C8:
    sub r5, pc, #0xfc
MobiClip_Code_020B10CC:
    ldrb r5, [r5, r6]
MobiClip_Code_020B10D0:
    sub r6, pc, #0xcc
MobiClip_Code_020B10D4:
    ldrb r6, [r6, r5]
MobiClip_Code_020B10D8:
    lsl r3, r3, r6
MobiClip_Code_020B10DC:
    subs r2, r2, r6
MobiClip_Code_020B10E0:
    mov r8, lr
MobiClip_Code_020B10E4:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B10E8:
    sub r6, pc, #0x10c
MobiClip_Code_020B10EC:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B10F0:
    mov lr, r8
MobiClip_Code_020B10F4:
    add pc, r5, r6
    /* control metadata 0x0208cdfc..0x0208ce1c */
    .global gMobiClip_chroma_kernel_dispatch
    .type gMobiClip_chroma_kernel_dispatch, %object
gMobiClip_chroma_kernel_dispatch:
    /* motion8x16_dispatch */
    .global gMobiClip_motion8x16_dispatch
gMobiClip_motion8x16_dispatch:
    .word MobiClip_Code_020B6CE0 - . + 0x114
    .word MobiClip_Code_020B6D50 - . + 0x118
    .word MobiClip_Code_020B6E14 - . + 0x11c
    .word MobiClip_Code_020B6E9C - . + 0x120
    .word MobiClip_Code_020B6CFC - . + 0x124
    .word MobiClip_Code_020B6D84 - . + 0x128
    .word MobiClip_Code_020B6E38 - . + 0x12c
    .word MobiClip_Code_020B6ED4 - . + 0x130
MobiClip_Code_020B1118:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B111C:
    bl MobiClip_Code_020B2C38
MobiClip_Code_020B1120:
    mov r5, r6
MobiClip_Code_020B1124:
    bl MobiClip_Code_020B2C38
MobiClip_Code_020B1128:
    add sb, r0, #0x3bc
MobiClip_Code_020B112C:
    ldm sb, {r7, r8}
MobiClip_Code_020B1130:
    add r5, r5, r7
MobiClip_Code_020B1134:
    add r6, r6, r8
MobiClip_Code_020B1138:
    stm r4, {r5, r6}
MobiClip_Code_020B113C:
    add r7, r5, fp, lsl #1
MobiClip_Code_020B1140:
    and r7, r7, #7
MobiClip_Code_020B1144:
    and r8, r6, #1
MobiClip_Code_020B1148:
    add r7, r7, r8, lsl #3
MobiClip_Code_020B114C:
    push {r0, r1, r2, r3}
MobiClip_Code_020B1150:
    ldr r2, [sp, #0x14]
MobiClip_Code_020B1154:
    ldr r1, [r0, #0xc]
MobiClip_Code_020B1158:
    add r0, r0, r2
MobiClip_Code_020B115C:
    ldr r0, [r0, #0xc]
MobiClip_Code_020B1160:
    asr r8, r6, #1
MobiClip_Code_020B1164:
    add r0, r0, fp
MobiClip_Code_020B1168:
    add r0, r0, r8, lsl #8
MobiClip_Code_020B116C:
    add r0, r0, r5, asr #1
MobiClip_Code_020B1170:
    add r1, r1, fp
MobiClip_Code_020B1174:
    ldr r2, [sp, #0x18]
MobiClip_Code_020B1178:
    sub r3, pc, #0x2e0
MobiClip_Code_020B117C:
    add lr, pc, #4
MobiClip_Code_020B1180:
    ldr r8, [r3, r7, lsl #2]
MobiClip_Code_020B1184:
    add pc, r8, r3
MobiClip_Code_020B1188:
    ldr r0, [sp]
MobiClip_Code_020B118C:
    ldr r2, [sp, #0x14]
MobiClip_Code_020B1190:
    ldr r1, [r0, #0x24]
MobiClip_Code_020B1194:
    add r0, r0, r2
MobiClip_Code_020B1198:
    ldr r0, [r0, #0x24]
MobiClip_Code_020B119C:
    asr r8, r6, #2
MobiClip_Code_020B11A0:
    add r0, r0, fp, lsr #1
MobiClip_Code_020B11A4:
    add r0, r0, r8, lsl #8
MobiClip_Code_020B11A8:
    add r0, r0, r5, asr #2
MobiClip_Code_020B11AC:
    add r1, r1, fp, lsr #1
MobiClip_Code_020B11B0:
    ldr r2, [sp, #0x18]
MobiClip_Code_020B11B4:
    lsr r2, r2, #1
MobiClip_Code_020B11B8:
    sub r3, pc, #0xc8
MobiClip_Code_020B11BC:
    add r5, r5, fp, lsl #1
MobiClip_Code_020B11C0:
    asr r5, r5, #1
MobiClip_Code_020B11C4:
    and r5, r5, #3
MobiClip_Code_020B11C8:
    asr r8, r6, #1
MobiClip_Code_020B11CC:
    and r8, r8, #1
MobiClip_Code_020B11D0:
    add r5, r5, r8, lsl #2
MobiClip_Code_020B11D4:
    add lr, pc, #8
MobiClip_Code_020B11D8:
    mov r6, r0
MobiClip_Code_020B11DC:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_020B11E0:
    add pc, r8, r3
MobiClip_Code_020B11E4:
    ldr r2, [sp, #0x18]
MobiClip_Code_020B11E8:
    lsr r2, r2, #1
MobiClip_Code_020B11EC:
    add r0, r6, #0x80
MobiClip_Code_020B11F0:
    sub r1, r1, r2, lsl #8
MobiClip_Code_020B11F4:
    add r1, r1, #0x80
MobiClip_Code_020B11F8:
    sub r3, pc, #0x108
MobiClip_Code_020B11FC:
    add lr, pc, #4
MobiClip_Code_020B1200:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_020B1204:
    add pc, r8, r3
MobiClip_Code_020B1208:
    pop {r0, r1, r2, r3, r4, r5, r6, fp, ip, pc}
    /* control metadata 0x0208cf10..0x0208cf54 */
    .global gMobiClip_motion8x16_selector_and_offsets
    .type gMobiClip_motion8x16_selector_and_offsets, %object
gMobiClip_motion8x16_selector_and_offsets:
    /* motion8x16_selectors */
    .byte 0x03, 0x03, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01
    /* motion8x16_modes */
    .global gMobiClip_motion8x16_modes
gMobiClip_motion8x16_modes:
    .word MobiClip_Code_020B1250 - .
    .word MobiClip_Code_020B1268 - . + 0x4
    .word MobiClip_Code_020B127C - . + 0x8
    .word MobiClip_Code_020B1290 - . + 0xc
    .word MobiClip_Code_020B12A4 - . + 0x10
    .word MobiClip_Code_020B12B8 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_020B12CC - . + 0x20
    .word MobiClip_Code_020B12E4 - . + 0x24
    /* motion8x16_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00
MobiClip_Code_020B1250:
    mov r5, #4
MobiClip_Code_020B1254:
    mov r6, #0x10
MobiClip_Code_020B1258:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B125C:
    add sb, r0, #0x3bc
MobiClip_Code_020B1260:
    ldm sb, {r5, r6}
MobiClip_Code_020B1264:
    b MobiClip_Code_020B1138
MobiClip_Code_020B1268:
    str lr, [sp, #-4]!
MobiClip_Code_020B126C:
    mov r5, #4
MobiClip_Code_020B1270:
    mov r6, #0x10
MobiClip_Code_020B1274:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1278:
    pop {pc}
MobiClip_Code_020B127C:
    str lr, [sp, #-4]!
MobiClip_Code_020B1280:
    mov r5, #8
MobiClip_Code_020B1284:
    mov r6, #0x10
MobiClip_Code_020B1288:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B128C:
    pop {pc}
MobiClip_Code_020B1290:
    str lr, [sp, #-4]!
MobiClip_Code_020B1294:
    mov r5, #0xc
MobiClip_Code_020B1298:
    mov r6, #0x10
MobiClip_Code_020B129C:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B12A0:
    pop {pc}
MobiClip_Code_020B12A4:
    str lr, [sp, #-4]!
MobiClip_Code_020B12A8:
    mov r5, #0x10
MobiClip_Code_020B12AC:
    mov r6, #0x10
MobiClip_Code_020B12B0:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B12B4:
    pop {pc}
MobiClip_Code_020B12B8:
    str lr, [sp, #-4]!
MobiClip_Code_020B12BC:
    mov r5, #0x14
MobiClip_Code_020B12C0:
    mov r6, #0x10
MobiClip_Code_020B12C4:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B12C8:
    pop {pc}
MobiClip_Code_020B12CC:
    str lr, [sp, #-4]!
MobiClip_Code_020B12D0:
    bl MobiClip_Code_020B1CFC
MobiClip_Code_020B12D4:
    add fp, fp, #0x800
MobiClip_Code_020B12D8:
    bl MobiClip_Code_020B1CFC
MobiClip_Code_020B12DC:
    sub fp, fp, #0x800
MobiClip_Code_020B12E0:
    pop {pc}
MobiClip_Code_020B12E4:
    str lr, [sp, #-4]!
MobiClip_Code_020B12E8:
    bl MobiClip_Code_020B1524
MobiClip_Code_020B12EC:
    add fp, fp, #2
MobiClip_Code_020B12F0:
    bl MobiClip_Code_020B1524
MobiClip_Code_020B12F4:
    sub fp, fp, #2
MobiClip_Code_020B12F8:
    pop {pc}
MobiClip_Code_020B12FC:
    lsr r6, r3, #0x1c
MobiClip_Code_020B1300:
    sub r5, pc, #0xfc
MobiClip_Code_020B1304:
    ldrb r5, [r5, r6]
MobiClip_Code_020B1308:
    sub r6, pc, #0xcc
MobiClip_Code_020B130C:
    ldrb r6, [r6, r5]
MobiClip_Code_020B1310:
    lsl r3, r3, r6
MobiClip_Code_020B1314:
    subs r2, r2, r6
MobiClip_Code_020B1318:
    mov r8, lr
MobiClip_Code_020B131C:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B1320:
    sub r6, pc, #0x10c
MobiClip_Code_020B1324:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B1328:
    mov lr, r8
MobiClip_Code_020B132C:
    add pc, r5, r6
    /* control metadata 0x0208d034..0x0208d044 */
    .global gMobiClip_chroma_narrow_kernel_dispatch
    .type gMobiClip_chroma_narrow_kernel_dispatch, %object
gMobiClip_chroma_narrow_kernel_dispatch:
    /* intra16_dispatch */
    .global gMobiClip_intra16_dispatch
gMobiClip_intra16_dispatch:
    .word MobiClip_Code_020B6F74 - . + 0x114
    .word MobiClip_Code_020B6FC4 - . + 0x118
    .word MobiClip_Code_020B6F88 - . + 0x11c
    .word MobiClip_Code_020B6FE8 - . + 0x120
MobiClip_Code_020B1340:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B1344:
    bl MobiClip_Code_020B2C38
MobiClip_Code_020B1348:
    mov r5, r6
MobiClip_Code_020B134C:
    bl MobiClip_Code_020B2C38
MobiClip_Code_020B1350:
    add sb, r0, #0x3bc
MobiClip_Code_020B1354:
    ldm sb, {r7, r8}
MobiClip_Code_020B1358:
    add r5, r5, r7
MobiClip_Code_020B135C:
    add r6, r6, r8
MobiClip_Code_020B1360:
    stm r4, {r5, r6}
MobiClip_Code_020B1364:
    add r7, r5, fp, lsl #1
MobiClip_Code_020B1368:
    and r7, r7, #3
MobiClip_Code_020B136C:
    and r8, r6, #1
MobiClip_Code_020B1370:
    add r7, r7, r8, lsl #2
MobiClip_Code_020B1374:
    push {r0, r1, r2, r3}
MobiClip_Code_020B1378:
    ldr r2, [sp, #0x14]
MobiClip_Code_020B137C:
    ldr r1, [r0, #0xc]
MobiClip_Code_020B1380:
    add r0, r0, r2
MobiClip_Code_020B1384:
    ldr r0, [r0, #0xc]
MobiClip_Code_020B1388:
    asr r8, r6, #1
MobiClip_Code_020B138C:
    add r0, r0, fp
MobiClip_Code_020B1390:
    add r0, r0, r8, lsl #8
MobiClip_Code_020B1394:
    add r0, r0, r5, asr #1
MobiClip_Code_020B1398:
    add r1, r1, fp
MobiClip_Code_020B139C:
    ldr r2, [sp, #0x18]
MobiClip_Code_020B13A0:
    sub r3, pc, #0x2b0
MobiClip_Code_020B13A4:
    add lr, pc, #4
MobiClip_Code_020B13A8:
    ldr r8, [r3, r7, lsl #2]
MobiClip_Code_020B13AC:
    add pc, r8, r3
MobiClip_Code_020B13B0:
    ldr r0, [sp]
MobiClip_Code_020B13B4:
    ldr r2, [sp, #0x14]
MobiClip_Code_020B13B8:
    ldr r1, [r0, #0x24]
MobiClip_Code_020B13BC:
    add r0, r0, r2
MobiClip_Code_020B13C0:
    ldr r0, [r0, #0x24]
MobiClip_Code_020B13C4:
    asr r8, r6, #2
MobiClip_Code_020B13C8:
    add r0, r0, fp, lsr #1
MobiClip_Code_020B13CC:
    add r0, r0, r8, lsl #8
MobiClip_Code_020B13D0:
    add r0, r0, r5, asr #2
MobiClip_Code_020B13D4:
    add r1, r1, fp, lsr #1
MobiClip_Code_020B13D8:
    ldr r2, [sp, #0x18]
MobiClip_Code_020B13DC:
    lsr r2, r2, #1
MobiClip_Code_020B13E0:
    sub r3, pc, #0xb8
MobiClip_Code_020B13E4:
    add r5, r5, fp, lsl #1
MobiClip_Code_020B13E8:
    asr r5, r5, #1
MobiClip_Code_020B13EC:
    and r5, r5, #1
MobiClip_Code_020B13F0:
    asr r8, r6, #1
MobiClip_Code_020B13F4:
    and r8, r8, #1
MobiClip_Code_020B13F8:
    add r5, r5, r8, lsl #1
MobiClip_Code_020B13FC:
    add lr, pc, #8
MobiClip_Code_020B1400:
    mov r6, r0
MobiClip_Code_020B1404:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_020B1408:
    add pc, r8, r3
MobiClip_Code_020B140C:
    ldr r2, [sp, #0x18]
MobiClip_Code_020B1410:
    lsr r2, r2, #1
MobiClip_Code_020B1414:
    add r0, r6, #0x80
MobiClip_Code_020B1418:
    sub r1, r1, r2, lsl #8
MobiClip_Code_020B141C:
    add r1, r1, #0x80
MobiClip_Code_020B1420:
    sub r3, pc, #0xf8
MobiClip_Code_020B1424:
    add lr, pc, #4
MobiClip_Code_020B1428:
    ldr r8, [r3, r5, lsl #2]
MobiClip_Code_020B142C:
    add pc, r8, r3
MobiClip_Code_020B1430:
    pop {r0, r1, r2, r3, r4, r5, r6, fp, ip, pc}
    /* control metadata 0x0208d138..0x0208d194 */
    .global gMobiClip_intra16_selector_and_offsets
    .type gMobiClip_intra16_selector_and_offsets, %object
gMobiClip_intra16_selector_and_offsets:
    /* intra16_selectors */
    .byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
    .byte 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x08, 0x05, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00
    /* intra16_modes_a */
    .global gMobiClip_intra16_modes_a
gMobiClip_intra16_modes_a:
    .word MobiClip_Code_020B1490 - .
    .word MobiClip_Code_020B14A8 - . + 0x4
    .word MobiClip_Code_020B14BC - . + 0x8
    .word MobiClip_Code_020B14D0 - . + 0xc
    .word MobiClip_Code_020B14E4 - . + 0x10
    .word MobiClip_Code_020B14F8 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_020B150C - . + 0x20
    .word 0 /* reserved */
    /* intra16_code_lengths */
    .byte 0x03, 0x01, 0x03, 0x03, 0x04, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .byte 0x00, 0x00, 0x00, 0x00
MobiClip_Code_020B1490:
    mov r5, #4
MobiClip_Code_020B1494:
    mov r6, #0x10
MobiClip_Code_020B1498:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B149C:
    add sb, r0, #0x3bc
MobiClip_Code_020B14A0:
    ldm sb, {r5, r6}
MobiClip_Code_020B14A4:
    b MobiClip_Code_020B1360
MobiClip_Code_020B14A8:
    str lr, [sp, #-4]!
MobiClip_Code_020B14AC:
    mov r5, #4
MobiClip_Code_020B14B0:
    mov r6, #0x10
MobiClip_Code_020B14B4:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B14B8:
    pop {pc}
MobiClip_Code_020B14BC:
    str lr, [sp, #-4]!
MobiClip_Code_020B14C0:
    mov r5, #8
MobiClip_Code_020B14C4:
    mov r6, #0x10
MobiClip_Code_020B14C8:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B14CC:
    pop {pc}
MobiClip_Code_020B14D0:
    str lr, [sp, #-4]!
MobiClip_Code_020B14D4:
    mov r5, #0xc
MobiClip_Code_020B14D8:
    mov r6, #0x10
MobiClip_Code_020B14DC:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B14E0:
    pop {pc}
MobiClip_Code_020B14E4:
    str lr, [sp, #-4]!
MobiClip_Code_020B14E8:
    mov r5, #0x10
MobiClip_Code_020B14EC:
    mov r6, #0x10
MobiClip_Code_020B14F0:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B14F4:
    pop {pc}
MobiClip_Code_020B14F8:
    str lr, [sp, #-4]!
MobiClip_Code_020B14FC:
    mov r5, #0x14
MobiClip_Code_020B1500:
    mov r6, #0x10
MobiClip_Code_020B1504:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B1508:
    pop {pc}
MobiClip_Code_020B150C:
    str lr, [sp, #-4]!
MobiClip_Code_020B1510:
    bl MobiClip_Code_020B2074
MobiClip_Code_020B1514:
    add fp, fp, #0x800
MobiClip_Code_020B1518:
    bl MobiClip_Code_020B2074
MobiClip_Code_020B151C:
    sub fp, fp, #0x800
MobiClip_Code_020B1520:
    pop {pc}
MobiClip_Code_020B1524:
    lsr r6, r3, #0x1b
MobiClip_Code_020B1528:
    sub r5, pc, #0xfc
MobiClip_Code_020B152C:
    ldrb r5, [r5, r6]
MobiClip_Code_020B1530:
    sub r6, pc, #0xbc
MobiClip_Code_020B1534:
    ldrb r6, [r6, r5]
MobiClip_Code_020B1538:
    lsl r3, r3, r6
MobiClip_Code_020B153C:
    subs r2, r2, r6
MobiClip_Code_020B1540:
    mov r8, lr
MobiClip_Code_020B1544:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B1548:
    sub r6, pc, #0xfc
MobiClip_Code_020B154C:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B1550:
    mov lr, r8
MobiClip_Code_020B1554:
    add pc, r5, r6
    /* control metadata 0x0208d25c..0x0208d2a0 */
    .global gMobiClip_motion8x8_selector_and_offsets
    .type gMobiClip_motion8x8_selector_and_offsets, %object
gMobiClip_motion8x8_selector_and_offsets:
    /* motion8x8_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x05, 0x04, 0x08, 0x08, 0x02, 0x02, 0x03, 0x09, 0x01, 0x01, 0x01, 0x01
    /* intra16_modes_b */
    .global gMobiClip_intra16_modes_b
gMobiClip_intra16_modes_b:
    .word MobiClip_Code_020B159C - .
    .word MobiClip_Code_020B15B4 - . + 0x4
    .word MobiClip_Code_020B15C8 - . + 0x8
    .word MobiClip_Code_020B15DC - . + 0xc
    .word MobiClip_Code_020B15F0 - . + 0x10
    .word MobiClip_Code_020B1604 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_020B1618 - . + 0x20
    .word MobiClip_Code_020B1630 - . + 0x24
    /* motion8x8_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x04, 0x04, 0x04, 0x00, 0x00, 0x03, 0x04, 0x00, 0x00
MobiClip_Code_020B159C:
    mov r5, #4
MobiClip_Code_020B15A0:
    mov r6, #8
MobiClip_Code_020B15A4:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B15A8:
    add sb, r0, #0x3bc
MobiClip_Code_020B15AC:
    ldm sb, {r5, r6}
MobiClip_Code_020B15B0:
    b MobiClip_Code_020B0C6C
MobiClip_Code_020B15B4:
    str lr, [sp, #-4]!
MobiClip_Code_020B15B8:
    mov r5, #4
MobiClip_Code_020B15BC:
    mov r6, #8
MobiClip_Code_020B15C0:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B15C4:
    pop {pc}
MobiClip_Code_020B15C8:
    str lr, [sp, #-4]!
MobiClip_Code_020B15CC:
    mov r5, #8
MobiClip_Code_020B15D0:
    mov r6, #8
MobiClip_Code_020B15D4:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B15D8:
    pop {pc}
MobiClip_Code_020B15DC:
    str lr, [sp, #-4]!
MobiClip_Code_020B15E0:
    mov r5, #0xc
MobiClip_Code_020B15E4:
    mov r6, #8
MobiClip_Code_020B15E8:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B15EC:
    pop {pc}
MobiClip_Code_020B15F0:
    str lr, [sp, #-4]!
MobiClip_Code_020B15F4:
    mov r5, #0x10
MobiClip_Code_020B15F8:
    mov r6, #8
MobiClip_Code_020B15FC:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B1600:
    pop {pc}
MobiClip_Code_020B1604:
    str lr, [sp, #-4]!
MobiClip_Code_020B1608:
    mov r5, #0x14
MobiClip_Code_020B160C:
    mov r6, #8
MobiClip_Code_020B1610:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B1614:
    pop {pc}
MobiClip_Code_020B1618:
    str lr, [sp, #-4]!
MobiClip_Code_020B161C:
    bl MobiClip_Code_020B176C
MobiClip_Code_020B1620:
    add fp, fp, #0x400
MobiClip_Code_020B1624:
    bl MobiClip_Code_020B176C
MobiClip_Code_020B1628:
    sub fp, fp, #0x400
MobiClip_Code_020B162C:
    pop {pc}
MobiClip_Code_020B1630:
    str lr, [sp, #-4]!
MobiClip_Code_020B1634:
    bl MobiClip_Code_020B199C
MobiClip_Code_020B1638:
    add fp, fp, #8
MobiClip_Code_020B163C:
    bl MobiClip_Code_020B199C
MobiClip_Code_020B1640:
    sub fp, fp, #8
MobiClip_Code_020B1644:
    pop {pc}
MobiClip_Code_020B1648:
    lsr r6, r3, #0x1c
MobiClip_Code_020B164C:
    sub r5, pc, #0xfc
MobiClip_Code_020B1650:
    ldrb r5, [r5, r6]
MobiClip_Code_020B1654:
    sub r6, pc, #0xcc
MobiClip_Code_020B1658:
    ldrb r6, [r6, r5]
MobiClip_Code_020B165C:
    lsl r3, r3, r6
MobiClip_Code_020B1660:
    subs r2, r2, r6
MobiClip_Code_020B1664:
    mov r8, lr
MobiClip_Code_020B1668:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B166C:
    sub r6, pc, #0x10c
MobiClip_Code_020B1670:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B1674:
    mov lr, r8
MobiClip_Code_020B1678:
    add pc, r5, r6
    /* control metadata 0x0208d380..0x0208d3c4 */
    .global gMobiClip_motion16x4_selector_and_offsets
    .type gMobiClip_motion16x4_selector_and_offsets, %object
gMobiClip_motion16x4_selector_and_offsets:
    /* motion16x4_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x08, 0x04, 0x02, 0x02, 0x05, 0x09, 0x01, 0x01, 0x01, 0x01
    /* motion16x8_modes_a */
    .global gMobiClip_motion16x8_modes_a
gMobiClip_motion16x8_modes_a:
    .word MobiClip_Code_020B16C0 - .
    .word MobiClip_Code_020B16D8 - . + 0x4
    .word MobiClip_Code_020B16EC - . + 0x8
    .word MobiClip_Code_020B1700 - . + 0xc
    .word MobiClip_Code_020B1714 - . + 0x10
    .word MobiClip_Code_020B1728 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_020B173C - . + 0x20
    .word MobiClip_Code_020B1754 - . + 0x24
    /* motion16x4_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00
MobiClip_Code_020B16C0:
    mov r5, #4
MobiClip_Code_020B16C4:
    mov r6, #4
MobiClip_Code_020B16C8:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B16CC:
    add sb, r0, #0x3bc
MobiClip_Code_020B16D0:
    ldm sb, {r5, r6}
MobiClip_Code_020B16D4:
    b MobiClip_Code_020B0C6C
MobiClip_Code_020B16D8:
    str lr, [sp, #-4]!
MobiClip_Code_020B16DC:
    mov r5, #4
MobiClip_Code_020B16E0:
    mov r6, #4
MobiClip_Code_020B16E4:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B16E8:
    pop {pc}
MobiClip_Code_020B16EC:
    str lr, [sp, #-4]!
MobiClip_Code_020B16F0:
    mov r5, #8
MobiClip_Code_020B16F4:
    mov r6, #4
MobiClip_Code_020B16F8:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B16FC:
    pop {pc}
MobiClip_Code_020B1700:
    str lr, [sp, #-4]!
MobiClip_Code_020B1704:
    mov r5, #0xc
MobiClip_Code_020B1708:
    mov r6, #4
MobiClip_Code_020B170C:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B1710:
    pop {pc}
MobiClip_Code_020B1714:
    str lr, [sp, #-4]!
MobiClip_Code_020B1718:
    mov r5, #0x10
MobiClip_Code_020B171C:
    mov r6, #4
MobiClip_Code_020B1720:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B1724:
    pop {pc}
MobiClip_Code_020B1728:
    str lr, [sp, #-4]!
MobiClip_Code_020B172C:
    mov r5, #0x14
MobiClip_Code_020B1730:
    mov r6, #4
MobiClip_Code_020B1734:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B1738:
    pop {pc}
MobiClip_Code_020B173C:
    str lr, [sp, #-4]!
MobiClip_Code_020B1740:
    bl MobiClip_Code_020B1878
MobiClip_Code_020B1744:
    add fp, fp, #0x200
MobiClip_Code_020B1748:
    bl MobiClip_Code_020B1878
MobiClip_Code_020B174C:
    sub fp, fp, #0x200
MobiClip_Code_020B1750:
    pop {pc}
MobiClip_Code_020B1754:
    str lr, [sp, #-4]!
MobiClip_Code_020B1758:
    bl MobiClip_Code_020B1AC0
MobiClip_Code_020B175C:
    add fp, fp, #8
MobiClip_Code_020B1760:
    bl MobiClip_Code_020B1AC0
MobiClip_Code_020B1764:
    sub fp, fp, #8
MobiClip_Code_020B1768:
    pop {pc}
MobiClip_Code_020B176C:
    lsr r6, r3, #0x1c
MobiClip_Code_020B1770:
    sub r5, pc, #0xfc
MobiClip_Code_020B1774:
    ldrb r5, [r5, r6]
MobiClip_Code_020B1778:
    sub r6, pc, #0xcc
MobiClip_Code_020B177C:
    ldrb r6, [r6, r5]
MobiClip_Code_020B1780:
    lsl r3, r3, r6
MobiClip_Code_020B1784:
    subs r2, r2, r6
MobiClip_Code_020B1788:
    mov r8, lr
MobiClip_Code_020B178C:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B1790:
    sub r6, pc, #0x10c
MobiClip_Code_020B1794:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B1798:
    mov lr, r8
MobiClip_Code_020B179C:
    add pc, r5, r6
    /* control metadata 0x0208d4a4..0x0208d4e8 */
    .global gMobiClip_motion16x2_selector_and_offsets
    .type gMobiClip_motion16x2_selector_and_offsets, %object
gMobiClip_motion16x2_selector_and_offsets:
    /* motion16x2_selectors */
    .byte 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x09, 0x04, 0x02, 0x02, 0x00, 0x00, 0x05, 0x03
    /* motion16x8_modes_b */
    .global gMobiClip_motion16x8_modes_b
gMobiClip_motion16x8_modes_b:
    .word MobiClip_Code_020B17E4 - .
    .word MobiClip_Code_020B17FC - . + 0x4
    .word MobiClip_Code_020B1810 - . + 0x8
    .word MobiClip_Code_020B1824 - . + 0xc
    .word MobiClip_Code_020B1838 - . + 0x10
    .word MobiClip_Code_020B184C - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_020B1860 - . + 0x24
    /* motion16x2_code_lengths */
    .byte 0x03, 0x01, 0x03, 0x04, 0x04, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00
MobiClip_Code_020B17E4:
    mov r5, #4
MobiClip_Code_020B17E8:
    mov r6, #2
MobiClip_Code_020B17EC:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B17F0:
    add sb, r0, #0x3bc
MobiClip_Code_020B17F4:
    ldm sb, {r5, r6}
MobiClip_Code_020B17F8:
    b MobiClip_Code_020B0C6C
MobiClip_Code_020B17FC:
    str lr, [sp, #-4]!
MobiClip_Code_020B1800:
    mov r5, #4
MobiClip_Code_020B1804:
    mov r6, #2
MobiClip_Code_020B1808:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B180C:
    pop {pc}
MobiClip_Code_020B1810:
    str lr, [sp, #-4]!
MobiClip_Code_020B1814:
    mov r5, #8
MobiClip_Code_020B1818:
    mov r6, #2
MobiClip_Code_020B181C:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B1820:
    pop {pc}
MobiClip_Code_020B1824:
    str lr, [sp, #-4]!
MobiClip_Code_020B1828:
    mov r5, #0xc
MobiClip_Code_020B182C:
    mov r6, #2
MobiClip_Code_020B1830:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B1834:
    pop {pc}
MobiClip_Code_020B1838:
    str lr, [sp, #-4]!
MobiClip_Code_020B183C:
    mov r5, #0x10
MobiClip_Code_020B1840:
    mov r6, #2
MobiClip_Code_020B1844:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B1848:
    pop {pc}
MobiClip_Code_020B184C:
    str lr, [sp, #-4]!
MobiClip_Code_020B1850:
    mov r5, #0x14
MobiClip_Code_020B1854:
    mov r6, #2
MobiClip_Code_020B1858:
    bl MobiClip_Code_020B0C4C
MobiClip_Code_020B185C:
    pop {pc}
MobiClip_Code_020B1860:
    str lr, [sp, #-4]!
MobiClip_Code_020B1864:
    bl MobiClip_Code_020B1BCC
MobiClip_Code_020B1868:
    add fp, fp, #8
MobiClip_Code_020B186C:
    bl MobiClip_Code_020B1BCC
MobiClip_Code_020B1870:
    sub fp, fp, #8
MobiClip_Code_020B1874:
    pop {pc}
MobiClip_Code_020B1878:
    lsr r6, r3, #0x1c
MobiClip_Code_020B187C:
    sub r5, pc, #0xe4
MobiClip_Code_020B1880:
    ldrb r5, [r5, r6]
MobiClip_Code_020B1884:
    sub r6, pc, #0xb4
MobiClip_Code_020B1888:
    ldrb r6, [r6, r5]
MobiClip_Code_020B188C:
    lsl r3, r3, r6
MobiClip_Code_020B1890:
    subs r2, r2, r6
MobiClip_Code_020B1894:
    mov r8, lr
MobiClip_Code_020B1898:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B189C:
    sub r6, pc, #0xf4
MobiClip_Code_020B18A0:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B18A4:
    mov lr, r8
MobiClip_Code_020B18A8:
    add pc, r5, r6
    /* control metadata 0x0208d5b0..0x0208d5f4 */
    .global gMobiClip_motion8x8_alt_selector_and_offsets
    .type gMobiClip_motion8x8_alt_selector_and_offsets, %object
gMobiClip_motion8x8_alt_selector_and_offsets:
    /* motion8x8_alt_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x05, 0x09, 0x04, 0x08, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01
    /* motion16x8_modes_c */
    .global gMobiClip_motion16x8_modes_c
gMobiClip_motion16x8_modes_c:
    .word MobiClip_Code_020B18F0 - .
    .word MobiClip_Code_020B1908 - . + 0x4
    .word MobiClip_Code_020B191C - . + 0x8
    .word MobiClip_Code_020B1930 - . + 0xc
    .word MobiClip_Code_020B1944 - . + 0x10
    .word MobiClip_Code_020B1958 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_020B196C - . + 0x20
    .word MobiClip_Code_020B1984 - . + 0x24
    /* motion8x8_alt_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00
MobiClip_Code_020B18F0:
    mov r5, #4
MobiClip_Code_020B18F4:
    mov r6, #8
MobiClip_Code_020B18F8:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B18FC:
    add sb, r0, #0x3bc
MobiClip_Code_020B1900:
    ldm sb, {r5, r6}
MobiClip_Code_020B1904:
    b MobiClip_Code_020B0F00
MobiClip_Code_020B1908:
    str lr, [sp, #-4]!
MobiClip_Code_020B190C:
    mov r5, #4
MobiClip_Code_020B1910:
    mov r6, #8
MobiClip_Code_020B1914:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1918:
    pop {pc}
MobiClip_Code_020B191C:
    str lr, [sp, #-4]!
MobiClip_Code_020B1920:
    mov r5, #8
MobiClip_Code_020B1924:
    mov r6, #8
MobiClip_Code_020B1928:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B192C:
    pop {pc}
MobiClip_Code_020B1930:
    str lr, [sp, #-4]!
MobiClip_Code_020B1934:
    mov r5, #0xc
MobiClip_Code_020B1938:
    mov r6, #8
MobiClip_Code_020B193C:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1940:
    pop {pc}
MobiClip_Code_020B1944:
    str lr, [sp, #-4]!
MobiClip_Code_020B1948:
    mov r5, #0x10
MobiClip_Code_020B194C:
    mov r6, #8
MobiClip_Code_020B1950:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1954:
    pop {pc}
MobiClip_Code_020B1958:
    str lr, [sp, #-4]!
MobiClip_Code_020B195C:
    mov r5, #0x14
MobiClip_Code_020B1960:
    mov r6, #8
MobiClip_Code_020B1964:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1968:
    pop {pc}
MobiClip_Code_020B196C:
    str lr, [sp, #-4]!
MobiClip_Code_020B1970:
    bl MobiClip_Code_020B1AC0
MobiClip_Code_020B1974:
    add fp, fp, #0x400
MobiClip_Code_020B1978:
    bl MobiClip_Code_020B1AC0
MobiClip_Code_020B197C:
    sub fp, fp, #0x400
MobiClip_Code_020B1980:
    pop {pc}
MobiClip_Code_020B1984:
    str lr, [sp, #-4]!
MobiClip_Code_020B1988:
    bl MobiClip_Code_020B1CFC
MobiClip_Code_020B198C:
    add fp, fp, #4
MobiClip_Code_020B1990:
    bl MobiClip_Code_020B1CFC
MobiClip_Code_020B1994:
    sub fp, fp, #4
MobiClip_Code_020B1998:
    pop {pc}
MobiClip_Code_020B199C:
    lsr r6, r3, #0x1c
MobiClip_Code_020B19A0:
    sub r5, pc, #0xfc
MobiClip_Code_020B19A4:
    ldrb r5, [r5, r6]
MobiClip_Code_020B19A8:
    sub r6, pc, #0xcc
MobiClip_Code_020B19AC:
    ldrb r6, [r6, r5]
MobiClip_Code_020B19B0:
    lsl r3, r3, r6
MobiClip_Code_020B19B4:
    subs r2, r2, r6
MobiClip_Code_020B19B8:
    mov r8, lr
MobiClip_Code_020B19BC:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B19C0:
    sub r6, pc, #0x10c
MobiClip_Code_020B19C4:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B19C8:
    mov lr, r8
MobiClip_Code_020B19CC:
    add pc, r5, r6
    /* control metadata 0x0208d6d4..0x0208d718 */
    .global gMobiClip_predicted_mode_a_selector_and_offsets
    .type gMobiClip_predicted_mode_a_selector_and_offsets, %object
gMobiClip_predicted_mode_a_selector_and_offsets:
    /* predicted_mode_a_selectors */
    .byte 0x02, 0x02, 0x02, 0x02, 0x08, 0x09, 0x03, 0x03, 0x05, 0x04, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01
    /* predicted_intra_modes_a */
    .global gMobiClip_predicted_intra_modes_a
gMobiClip_predicted_intra_modes_a:
    .word MobiClip_Code_020B1A14 - .
    .word MobiClip_Code_020B1A2C - . + 0x4
    .word MobiClip_Code_020B1A40 - . + 0x8
    .word MobiClip_Code_020B1A54 - . + 0xc
    .word MobiClip_Code_020B1A68 - . + 0x10
    .word MobiClip_Code_020B1A7C - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_020B1A90 - . + 0x20
    .word MobiClip_Code_020B1AA8 - . + 0x24
    /* predicted_mode_a_code_lengths */
    .byte 0x03, 0x02, 0x02, 0x03, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00
MobiClip_Code_020B1A14:
    mov r5, #4
MobiClip_Code_020B1A18:
    mov r6, #4
MobiClip_Code_020B1A1C:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B1A20:
    add sb, r0, #0x3bc
MobiClip_Code_020B1A24:
    ldm sb, {r5, r6}
MobiClip_Code_020B1A28:
    b MobiClip_Code_020B0F00
MobiClip_Code_020B1A2C:
    str lr, [sp, #-4]!
MobiClip_Code_020B1A30:
    mov r5, #4
MobiClip_Code_020B1A34:
    mov r6, #4
MobiClip_Code_020B1A38:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1A3C:
    pop {pc}
MobiClip_Code_020B1A40:
    str lr, [sp, #-4]!
MobiClip_Code_020B1A44:
    mov r5, #8
MobiClip_Code_020B1A48:
    mov r6, #4
MobiClip_Code_020B1A4C:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1A50:
    pop {pc}
MobiClip_Code_020B1A54:
    str lr, [sp, #-4]!
MobiClip_Code_020B1A58:
    mov r5, #0xc
MobiClip_Code_020B1A5C:
    mov r6, #4
MobiClip_Code_020B1A60:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1A64:
    pop {pc}
MobiClip_Code_020B1A68:
    str lr, [sp, #-4]!
MobiClip_Code_020B1A6C:
    mov r5, #0x10
MobiClip_Code_020B1A70:
    mov r6, #4
MobiClip_Code_020B1A74:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1A78:
    pop {pc}
MobiClip_Code_020B1A7C:
    str lr, [sp, #-4]!
MobiClip_Code_020B1A80:
    mov r5, #0x14
MobiClip_Code_020B1A84:
    mov r6, #4
MobiClip_Code_020B1A88:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1A8C:
    pop {pc}
MobiClip_Code_020B1A90:
    str lr, [sp, #-4]!
MobiClip_Code_020B1A94:
    bl MobiClip_Code_020B1BCC
MobiClip_Code_020B1A98:
    add fp, fp, #0x200
MobiClip_Code_020B1A9C:
    bl MobiClip_Code_020B1BCC
MobiClip_Code_020B1AA0:
    sub fp, fp, #0x200
MobiClip_Code_020B1AA4:
    pop {pc}
MobiClip_Code_020B1AA8:
    str lr, [sp, #-4]!
MobiClip_Code_020B1AAC:
    bl MobiClip_Code_020B1E3C
MobiClip_Code_020B1AB0:
    add fp, fp, #4
MobiClip_Code_020B1AB4:
    bl MobiClip_Code_020B1E3C
MobiClip_Code_020B1AB8:
    sub fp, fp, #4
MobiClip_Code_020B1ABC:
    pop {pc}
MobiClip_Code_020B1AC0:
    lsr r6, r3, #0x1c
MobiClip_Code_020B1AC4:
    sub r5, pc, #0xfc
MobiClip_Code_020B1AC8:
    ldrb r5, [r5, r6]
MobiClip_Code_020B1ACC:
    sub r6, pc, #0xcc
MobiClip_Code_020B1AD0:
    ldrb r6, [r6, r5]
MobiClip_Code_020B1AD4:
    lsl r3, r3, r6
MobiClip_Code_020B1AD8:
    subs r2, r2, r6
MobiClip_Code_020B1ADC:
    mov r8, lr
MobiClip_Code_020B1AE0:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B1AE4:
    sub r6, pc, #0x10c
MobiClip_Code_020B1AE8:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B1AEC:
    mov lr, r8
MobiClip_Code_020B1AF0:
    add pc, r5, r6
    /* control metadata 0x0208d7f8..0x0208d83c */
    .global gMobiClip_predicted_mode_b_selector_and_offsets
    .type gMobiClip_predicted_mode_b_selector_and_offsets, %object
gMobiClip_predicted_mode_b_selector_and_offsets:
    /* predicted_mode_b_selectors */
    .byte 0x02, 0x02, 0x02, 0x02, 0x04, 0x04, 0x09, 0x05, 0x03, 0x03, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01
    /* predicted_intra_modes_b */
    .global gMobiClip_predicted_intra_modes_b
gMobiClip_predicted_intra_modes_b:
    .word MobiClip_Code_020B1B38 - .
    .word MobiClip_Code_020B1B50 - . + 0x4
    .word MobiClip_Code_020B1B64 - . + 0x8
    .word MobiClip_Code_020B1B78 - . + 0xc
    .word MobiClip_Code_020B1B8C - . + 0x10
    .word MobiClip_Code_020B1BA0 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_020B1BB4 - . + 0x24
    /* predicted_mode_b_code_lengths */
    .byte 0x03, 0x02, 0x02, 0x03, 0x03, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00
MobiClip_Code_020B1B38:
    mov r5, #4
MobiClip_Code_020B1B3C:
    mov r6, #2
MobiClip_Code_020B1B40:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B1B44:
    add sb, r0, #0x3bc
MobiClip_Code_020B1B48:
    ldm sb, {r5, r6}
MobiClip_Code_020B1B4C:
    b MobiClip_Code_020B0F00
MobiClip_Code_020B1B50:
    str lr, [sp, #-4]!
MobiClip_Code_020B1B54:
    mov r5, #4
MobiClip_Code_020B1B58:
    mov r6, #2
MobiClip_Code_020B1B5C:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1B60:
    pop {pc}
MobiClip_Code_020B1B64:
    str lr, [sp, #-4]!
MobiClip_Code_020B1B68:
    mov r5, #8
MobiClip_Code_020B1B6C:
    mov r6, #2
MobiClip_Code_020B1B70:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1B74:
    pop {pc}
MobiClip_Code_020B1B78:
    str lr, [sp, #-4]!
MobiClip_Code_020B1B7C:
    mov r5, #0xc
MobiClip_Code_020B1B80:
    mov r6, #2
MobiClip_Code_020B1B84:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1B88:
    pop {pc}
MobiClip_Code_020B1B8C:
    str lr, [sp, #-4]!
MobiClip_Code_020B1B90:
    mov r5, #0x10
MobiClip_Code_020B1B94:
    mov r6, #2
MobiClip_Code_020B1B98:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1B9C:
    pop {pc}
MobiClip_Code_020B1BA0:
    str lr, [sp, #-4]!
MobiClip_Code_020B1BA4:
    mov r5, #0x14
MobiClip_Code_020B1BA8:
    mov r6, #2
MobiClip_Code_020B1BAC:
    bl MobiClip_Code_020B0EE0
MobiClip_Code_020B1BB0:
    pop {pc}
MobiClip_Code_020B1BB4:
    str lr, [sp, #-4]!
MobiClip_Code_020B1BB8:
    bl MobiClip_Code_020B1F54
MobiClip_Code_020B1BBC:
    add fp, fp, #4
MobiClip_Code_020B1BC0:
    bl MobiClip_Code_020B1F54
MobiClip_Code_020B1BC4:
    sub fp, fp, #4
MobiClip_Code_020B1BC8:
    pop {pc}
MobiClip_Code_020B1BCC:
    lsr r6, r3, #0x1c
MobiClip_Code_020B1BD0:
    sub r5, pc, #0xe4
MobiClip_Code_020B1BD4:
    ldrb r5, [r5, r6]
MobiClip_Code_020B1BD8:
    sub r6, pc, #0xb4
MobiClip_Code_020B1BDC:
    ldrb r6, [r6, r5]
MobiClip_Code_020B1BE0:
    lsl r3, r3, r6
MobiClip_Code_020B1BE4:
    subs r2, r2, r6
MobiClip_Code_020B1BE8:
    mov r8, lr
MobiClip_Code_020B1BEC:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B1BF0:
    sub r6, pc, #0xf4
MobiClip_Code_020B1BF4:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B1BF8:
    mov lr, r8
MobiClip_Code_020B1BFC:
    add pc, r5, r6
    /* control metadata 0x0208d904..0x0208d954 */
    .global gMobiClip_predicted_mode_c_selector_and_offsets
    .type gMobiClip_predicted_mode_c_selector_and_offsets, %object
gMobiClip_predicted_mode_c_selector_and_offsets:
    /* predicted_mode_c_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x09, 0x05, 0x08, 0x04, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01
    /* predicted_intra_modes_c */
    .global gMobiClip_predicted_intra_modes_c
gMobiClip_predicted_intra_modes_c:
    .word MobiClip_Code_020B1C50 - .
    .word MobiClip_Code_020B1C68 - . + 0x4
    .word MobiClip_Code_020B1C7C - . + 0x8
    .word MobiClip_Code_020B1C90 - . + 0xc
    .word MobiClip_Code_020B1CA4 - . + 0x10
    .word MobiClip_Code_020B1CB8 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_020B1CCC - . + 0x20
    .word MobiClip_Code_020B1CE4 - . + 0x24
    /* predicted_mode_c_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x04, 0x04, 0x00, 0x00, 0x04, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
MobiClip_Code_020B1C50:
    mov r5, #4
MobiClip_Code_020B1C54:
    mov r6, #8
MobiClip_Code_020B1C58:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B1C5C:
    add sb, r0, #0x3bc
MobiClip_Code_020B1C60:
    ldm sb, {r5, r6}
MobiClip_Code_020B1C64:
    b MobiClip_Code_020B1138
MobiClip_Code_020B1C68:
    str lr, [sp, #-4]!
MobiClip_Code_020B1C6C:
    mov r5, #4
MobiClip_Code_020B1C70:
    mov r6, #8
MobiClip_Code_020B1C74:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1C78:
    pop {pc}
MobiClip_Code_020B1C7C:
    str lr, [sp, #-4]!
MobiClip_Code_020B1C80:
    mov r5, #8
MobiClip_Code_020B1C84:
    mov r6, #8
MobiClip_Code_020B1C88:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1C8C:
    pop {pc}
MobiClip_Code_020B1C90:
    str lr, [sp, #-4]!
MobiClip_Code_020B1C94:
    mov r5, #0xc
MobiClip_Code_020B1C98:
    mov r6, #8
MobiClip_Code_020B1C9C:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1CA0:
    pop {pc}
MobiClip_Code_020B1CA4:
    str lr, [sp, #-4]!
MobiClip_Code_020B1CA8:
    mov r5, #0x10
MobiClip_Code_020B1CAC:
    mov r6, #8
MobiClip_Code_020B1CB0:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1CB4:
    pop {pc}
MobiClip_Code_020B1CB8:
    str lr, [sp, #-4]!
MobiClip_Code_020B1CBC:
    mov r5, #0x14
MobiClip_Code_020B1CC0:
    mov r6, #8
MobiClip_Code_020B1CC4:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1CC8:
    pop {pc}
MobiClip_Code_020B1CCC:
    str lr, [sp, #-4]!
MobiClip_Code_020B1CD0:
    bl MobiClip_Code_020B1E3C
MobiClip_Code_020B1CD4:
    add fp, fp, #0x400
MobiClip_Code_020B1CD8:
    bl MobiClip_Code_020B1E3C
MobiClip_Code_020B1CDC:
    sub fp, fp, #0x400
MobiClip_Code_020B1CE0:
    pop {pc}
MobiClip_Code_020B1CE4:
    str lr, [sp, #-4]!
MobiClip_Code_020B1CE8:
    bl MobiClip_Code_020B2074
MobiClip_Code_020B1CEC:
    add fp, fp, #2
MobiClip_Code_020B1CF0:
    bl MobiClip_Code_020B2074
MobiClip_Code_020B1CF4:
    sub fp, fp, #2
MobiClip_Code_020B1CF8:
    pop {pc}
MobiClip_Code_020B1CFC:
    lsr r6, r3, #0x1c
MobiClip_Code_020B1D00:
    sub r5, pc, #0x108
MobiClip_Code_020B1D04:
    ldrb r5, [r5, r6]
MobiClip_Code_020B1D08:
    sub r6, pc, #0xd8
MobiClip_Code_020B1D0C:
    ldrb r6, [r6, r5]
MobiClip_Code_020B1D10:
    lsl r3, r3, r6
MobiClip_Code_020B1D14:
    subs r2, r2, r6
MobiClip_Code_020B1D18:
    mov r8, lr
MobiClip_Code_020B1D1C:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B1D20:
    sub r6, pc, #0x118
MobiClip_Code_020B1D24:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B1D28:
    mov lr, r8
MobiClip_Code_020B1D2C:
    add pc, r5, r6
    /* control metadata 0x0208da34..0x0208da94 */
    .global gMobiClip_predicted_mode_d_selector_and_offsets
    .type gMobiClip_predicted_mode_d_selector_and_offsets, %object
gMobiClip_predicted_mode_d_selector_and_offsets:
    /* predicted_mode_d_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x04, 0x04, 0x03, 0x03, 0x03, 0x03
    .byte 0x08, 0x09, 0x05, 0x05, 0x02, 0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
    /* predicted_intra_modes_d */
    .global gMobiClip_predicted_intra_modes_d
gMobiClip_predicted_intra_modes_d:
    .word MobiClip_Code_020B1D90 - .
    .word MobiClip_Code_020B1DA8 - . + 0x4
    .word MobiClip_Code_020B1DBC - . + 0x8
    .word MobiClip_Code_020B1DD0 - . + 0xc
    .word MobiClip_Code_020B1DE4 - . + 0x10
    .word MobiClip_Code_020B1DF8 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_020B1E0C - . + 0x20
    .word MobiClip_Code_020B1E24 - . + 0x24
    /* predicted_mode_d_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x03, 0x04, 0x00, 0x00, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
MobiClip_Code_020B1D90:
    mov r5, #4
MobiClip_Code_020B1D94:
    mov r6, #4
MobiClip_Code_020B1D98:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B1D9C:
    add sb, r0, #0x3bc
MobiClip_Code_020B1DA0:
    ldm sb, {r5, r6}
MobiClip_Code_020B1DA4:
    b MobiClip_Code_020B1138
MobiClip_Code_020B1DA8:
    str lr, [sp, #-4]!
MobiClip_Code_020B1DAC:
    mov r5, #4
MobiClip_Code_020B1DB0:
    mov r6, #4
MobiClip_Code_020B1DB4:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1DB8:
    pop {pc}
MobiClip_Code_020B1DBC:
    str lr, [sp, #-4]!
MobiClip_Code_020B1DC0:
    mov r5, #8
MobiClip_Code_020B1DC4:
    mov r6, #4
MobiClip_Code_020B1DC8:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1DCC:
    pop {pc}
MobiClip_Code_020B1DD0:
    str lr, [sp, #-4]!
MobiClip_Code_020B1DD4:
    mov r5, #0xc
MobiClip_Code_020B1DD8:
    mov r6, #4
MobiClip_Code_020B1DDC:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1DE0:
    pop {pc}
MobiClip_Code_020B1DE4:
    str lr, [sp, #-4]!
MobiClip_Code_020B1DE8:
    mov r5, #0x10
MobiClip_Code_020B1DEC:
    mov r6, #4
MobiClip_Code_020B1DF0:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1DF4:
    pop {pc}
MobiClip_Code_020B1DF8:
    str lr, [sp, #-4]!
MobiClip_Code_020B1DFC:
    mov r5, #0x14
MobiClip_Code_020B1E00:
    mov r6, #4
MobiClip_Code_020B1E04:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1E08:
    pop {pc}
MobiClip_Code_020B1E0C:
    str lr, [sp, #-4]!
MobiClip_Code_020B1E10:
    bl MobiClip_Code_020B1F54
MobiClip_Code_020B1E14:
    add fp, fp, #0x200
MobiClip_Code_020B1E18:
    bl MobiClip_Code_020B1F54
MobiClip_Code_020B1E1C:
    sub fp, fp, #0x200
MobiClip_Code_020B1E20:
    pop {pc}
MobiClip_Code_020B1E24:
    str lr, [sp, #-4]!
MobiClip_Code_020B1E28:
    bl MobiClip_Code_020B2184
MobiClip_Code_020B1E2C:
    add fp, fp, #2
MobiClip_Code_020B1E30:
    bl MobiClip_Code_020B2184
MobiClip_Code_020B1E34:
    sub fp, fp, #2
MobiClip_Code_020B1E38:
    pop {pc}
MobiClip_Code_020B1E3C:
    lsr r6, r3, #0x1b
MobiClip_Code_020B1E40:
    sub r5, pc, #0x118
MobiClip_Code_020B1E44:
    ldrb r5, [r5, r6]
MobiClip_Code_020B1E48:
    sub r6, pc, #0xd8
MobiClip_Code_020B1E4C:
    ldrb r6, [r6, r5]
MobiClip_Code_020B1E50:
    lsl r3, r3, r6
MobiClip_Code_020B1E54:
    subs r2, r2, r6
MobiClip_Code_020B1E58:
    mov r8, lr
MobiClip_Code_020B1E5C:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B1E60:
    sub r6, pc, #0x118
MobiClip_Code_020B1E64:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B1E68:
    mov lr, r8
MobiClip_Code_020B1E6C:
    add pc, r5, r6
    /* control metadata 0x0208db74..0x0208dbc4 */
    .global gMobiClip_predicted_mode_e_selector_and_offsets
    .type gMobiClip_predicted_mode_e_selector_and_offsets, %object
gMobiClip_predicted_mode_e_selector_and_offsets:
    /* predicted_mode_e_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x09, 0x05, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01
    /* predicted_intra_modes_e */
    .global gMobiClip_predicted_intra_modes_e
gMobiClip_predicted_intra_modes_e:
    .word MobiClip_Code_020B1EC0 - .
    .word MobiClip_Code_020B1ED8 - . + 0x4
    .word MobiClip_Code_020B1EEC - . + 0x8
    .word MobiClip_Code_020B1F00 - . + 0xc
    .word MobiClip_Code_020B1F14 - . + 0x10
    .word MobiClip_Code_020B1F28 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_020B1F3C - . + 0x24
    /* predicted_mode_e_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x03, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
MobiClip_Code_020B1EC0:
    mov r5, #4
MobiClip_Code_020B1EC4:
    mov r6, #2
MobiClip_Code_020B1EC8:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B1ECC:
    add sb, r0, #0x3bc
MobiClip_Code_020B1ED0:
    ldm sb, {r5, r6}
MobiClip_Code_020B1ED4:
    b MobiClip_Code_020B1138
MobiClip_Code_020B1ED8:
    str lr, [sp, #-4]!
MobiClip_Code_020B1EDC:
    mov r5, #4
MobiClip_Code_020B1EE0:
    mov r6, #2
MobiClip_Code_020B1EE4:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1EE8:
    pop {pc}
MobiClip_Code_020B1EEC:
    str lr, [sp, #-4]!
MobiClip_Code_020B1EF0:
    mov r5, #8
MobiClip_Code_020B1EF4:
    mov r6, #2
MobiClip_Code_020B1EF8:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1EFC:
    pop {pc}
MobiClip_Code_020B1F00:
    str lr, [sp, #-4]!
MobiClip_Code_020B1F04:
    mov r5, #0xc
MobiClip_Code_020B1F08:
    mov r6, #2
MobiClip_Code_020B1F0C:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1F10:
    pop {pc}
MobiClip_Code_020B1F14:
    str lr, [sp, #-4]!
MobiClip_Code_020B1F18:
    mov r5, #0x10
MobiClip_Code_020B1F1C:
    mov r6, #2
MobiClip_Code_020B1F20:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1F24:
    pop {pc}
MobiClip_Code_020B1F28:
    str lr, [sp, #-4]!
MobiClip_Code_020B1F2C:
    mov r5, #0x14
MobiClip_Code_020B1F30:
    mov r6, #2
MobiClip_Code_020B1F34:
    bl MobiClip_Code_020B1118
MobiClip_Code_020B1F38:
    pop {pc}
MobiClip_Code_020B1F3C:
    str lr, [sp, #-4]!
MobiClip_Code_020B1F40:
    bl MobiClip_Code_020B227C
MobiClip_Code_020B1F44:
    add fp, fp, #2
MobiClip_Code_020B1F48:
    bl MobiClip_Code_020B227C
MobiClip_Code_020B1F4C:
    sub fp, fp, #2
MobiClip_Code_020B1F50:
    pop {pc}
MobiClip_Code_020B1F54:
    lsr r6, r3, #0x1c
MobiClip_Code_020B1F58:
    sub r5, pc, #0xf0
MobiClip_Code_020B1F5C:
    ldrb r5, [r5, r6]
MobiClip_Code_020B1F60:
    sub r6, pc, #0xc0
MobiClip_Code_020B1F64:
    ldrb r6, [r6, r5]
MobiClip_Code_020B1F68:
    lsl r3, r3, r6
MobiClip_Code_020B1F6C:
    subs r2, r2, r6
MobiClip_Code_020B1F70:
    mov r8, lr
MobiClip_Code_020B1F74:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B1F78:
    sub r6, pc, #0x100
MobiClip_Code_020B1F7C:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B1F80:
    mov lr, r8
MobiClip_Code_020B1F84:
    add pc, r5, r6
    /* control metadata 0x0208dc8c..0x0208dce4 */
    .global gMobiClip_predicted_mode_f_selector_and_offsets
    .type gMobiClip_predicted_mode_f_selector_and_offsets, %object
gMobiClip_predicted_mode_f_selector_and_offsets:
    /* predicted_mode_f_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02
    .byte 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x08, 0x05, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
    /* predicted_intra_modes_f */
    .global gMobiClip_predicted_intra_modes_f
gMobiClip_predicted_intra_modes_f:
    .word MobiClip_Code_020B1FE0 - .
    .word MobiClip_Code_020B1FF8 - . + 0x4
    .word MobiClip_Code_020B200C - . + 0x8
    .word MobiClip_Code_020B2020 - . + 0xc
    .word MobiClip_Code_020B2034 - . + 0x10
    .word MobiClip_Code_020B2048 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_020B205C - . + 0x20
    .word 0 /* reserved */
    /* predicted_mode_f_code_lengths */
    .byte 0x02, 0x02, 0x02, 0x03, 0x04, 0x05, 0x00, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
MobiClip_Code_020B1FE0:
    mov r5, #4
MobiClip_Code_020B1FE4:
    mov r6, #8
MobiClip_Code_020B1FE8:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B1FEC:
    add sb, r0, #0x3bc
MobiClip_Code_020B1FF0:
    ldm sb, {r5, r6}
MobiClip_Code_020B1FF4:
    b MobiClip_Code_020B1360
MobiClip_Code_020B1FF8:
    str lr, [sp, #-4]!
MobiClip_Code_020B1FFC:
    mov r5, #4
MobiClip_Code_020B2000:
    mov r6, #8
MobiClip_Code_020B2004:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B2008:
    pop {pc}
MobiClip_Code_020B200C:
    str lr, [sp, #-4]!
MobiClip_Code_020B2010:
    mov r5, #8
MobiClip_Code_020B2014:
    mov r6, #8
MobiClip_Code_020B2018:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B201C:
    pop {pc}
MobiClip_Code_020B2020:
    str lr, [sp, #-4]!
MobiClip_Code_020B2024:
    mov r5, #0xc
MobiClip_Code_020B2028:
    mov r6, #8
MobiClip_Code_020B202C:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B2030:
    pop {pc}
MobiClip_Code_020B2034:
    str lr, [sp, #-4]!
MobiClip_Code_020B2038:
    mov r5, #0x10
MobiClip_Code_020B203C:
    mov r6, #8
MobiClip_Code_020B2040:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B2044:
    pop {pc}
MobiClip_Code_020B2048:
    str lr, [sp, #-4]!
MobiClip_Code_020B204C:
    mov r5, #0x14
MobiClip_Code_020B2050:
    mov r6, #8
MobiClip_Code_020B2054:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B2058:
    pop {pc}
MobiClip_Code_020B205C:
    str lr, [sp, #-4]!
MobiClip_Code_020B2060:
    bl MobiClip_Code_020B2184
MobiClip_Code_020B2064:
    add fp, fp, #0x400
MobiClip_Code_020B2068:
    bl MobiClip_Code_020B2184
MobiClip_Code_020B206C:
    sub fp, fp, #0x400
MobiClip_Code_020B2070:
    pop {pc}
MobiClip_Code_020B2074:
    lsr r6, r3, #0x1b
MobiClip_Code_020B2078:
    sub r5, pc, #0xf8
MobiClip_Code_020B207C:
    ldrb r5, [r5, r6]
MobiClip_Code_020B2080:
    sub r6, pc, #0xb8
MobiClip_Code_020B2084:
    ldrb r6, [r6, r5]
MobiClip_Code_020B2088:
    lsl r3, r3, r6
MobiClip_Code_020B208C:
    subs r2, r2, r6
MobiClip_Code_020B2090:
    mov r8, lr
MobiClip_Code_020B2094:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B2098:
    sub r6, pc, #0xf8
MobiClip_Code_020B209C:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B20A0:
    mov lr, r8
MobiClip_Code_020B20A4:
    add pc, r5, r6
    /* control metadata 0x0208ddac..0x0208ddf4 */
    .global gMobiClip_predicted_mode_g_selector_and_offsets
    .type gMobiClip_predicted_mode_g_selector_and_offsets, %object
gMobiClip_predicted_mode_g_selector_and_offsets:
    /* predicted_mode_g_selectors */
    .byte 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x08, 0x05, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01
    /* predicted_intra_modes_g */
    .global gMobiClip_predicted_intra_modes_g
gMobiClip_predicted_intra_modes_g:
    .word MobiClip_Code_020B20F0 - .
    .word MobiClip_Code_020B2108 - . + 0x4
    .word MobiClip_Code_020B211C - . + 0x8
    .word MobiClip_Code_020B2130 - . + 0xc
    .word MobiClip_Code_020B2144 - . + 0x10
    .word MobiClip_Code_020B2158 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word MobiClip_Code_020B216C - . + 0x20
    .word 0 /* reserved */
    /* predicted_mode_g_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x03, 0x04, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
MobiClip_Code_020B20F0:
    mov r5, #4
MobiClip_Code_020B20F4:
    mov r6, #4
MobiClip_Code_020B20F8:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B20FC:
    add sb, r0, #0x3bc
MobiClip_Code_020B2100:
    ldm sb, {r5, r6}
MobiClip_Code_020B2104:
    b MobiClip_Code_020B1360
MobiClip_Code_020B2108:
    str lr, [sp, #-4]!
MobiClip_Code_020B210C:
    mov r5, #4
MobiClip_Code_020B2110:
    mov r6, #4
MobiClip_Code_020B2114:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B2118:
    pop {pc}
MobiClip_Code_020B211C:
    str lr, [sp, #-4]!
MobiClip_Code_020B2120:
    mov r5, #8
MobiClip_Code_020B2124:
    mov r6, #4
MobiClip_Code_020B2128:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B212C:
    pop {pc}
MobiClip_Code_020B2130:
    str lr, [sp, #-4]!
MobiClip_Code_020B2134:
    mov r5, #0xc
MobiClip_Code_020B2138:
    mov r6, #4
MobiClip_Code_020B213C:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B2140:
    pop {pc}
MobiClip_Code_020B2144:
    str lr, [sp, #-4]!
MobiClip_Code_020B2148:
    mov r5, #0x10
MobiClip_Code_020B214C:
    mov r6, #4
MobiClip_Code_020B2150:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B2154:
    pop {pc}
MobiClip_Code_020B2158:
    str lr, [sp, #-4]!
MobiClip_Code_020B215C:
    mov r5, #0x14
MobiClip_Code_020B2160:
    mov r6, #4
MobiClip_Code_020B2164:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B2168:
    pop {pc}
MobiClip_Code_020B216C:
    str lr, [sp, #-4]!
MobiClip_Code_020B2170:
    bl MobiClip_Code_020B227C
MobiClip_Code_020B2174:
    add fp, fp, #0x200
MobiClip_Code_020B2178:
    bl MobiClip_Code_020B227C
MobiClip_Code_020B217C:
    sub fp, fp, #0x200
MobiClip_Code_020B2180:
    pop {pc}
MobiClip_Code_020B2184:
    lsr r6, r3, #0x1c
MobiClip_Code_020B2188:
    sub r5, pc, #0xe8
MobiClip_Code_020B218C:
    ldrb r5, [r5, r6]
MobiClip_Code_020B2190:
    sub r6, pc, #0xb8
MobiClip_Code_020B2194:
    ldrb r6, [r6, r5]
MobiClip_Code_020B2198:
    lsl r3, r3, r6
MobiClip_Code_020B219C:
    subs r2, r2, r6
MobiClip_Code_020B21A0:
    mov r8, lr
MobiClip_Code_020B21A4:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B21A8:
    sub r6, pc, #0xf8
MobiClip_Code_020B21AC:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B21B0:
    mov lr, r8
MobiClip_Code_020B21B4:
    add pc, r5, r6
    /* control metadata 0x0208debc..0x0208df04 */
    .global gMobiClip_predicted_mode_h_selector_and_offsets
    .type gMobiClip_predicted_mode_h_selector_and_offsets, %object
gMobiClip_predicted_mode_h_selector_and_offsets:
    /* predicted_mode_h_selectors */
    .byte 0x05, 0x04, 0x01, 0x01, 0x00, 0x00, 0x03, 0x02
    /* predicted_intra_modes_h */
    .global gMobiClip_predicted_intra_modes_h
gMobiClip_predicted_intra_modes_h:
    .word MobiClip_Code_020B2200 - .
    .word MobiClip_Code_020B2218 - . + 0x4
    .word MobiClip_Code_020B222C - . + 0x8
    .word MobiClip_Code_020B2240 - . + 0xc
    .word MobiClip_Code_020B2254 - . + 0x10
    .word MobiClip_Code_020B2268 - . + 0x14
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word 0 /* reserved */
    .word 0 /* reserved */
    /* predicted_mode_h_code_lengths */
    .byte 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
MobiClip_Code_020B2200:
    mov r5, #4
MobiClip_Code_020B2204:
    mov r6, #2
MobiClip_Code_020B2208:
    push {r4, r5, r6, fp, ip, lr}
MobiClip_Code_020B220C:
    add sb, r0, #0x3bc
MobiClip_Code_020B2210:
    ldm sb, {r5, r6}
MobiClip_Code_020B2214:
    b MobiClip_Code_020B1360
MobiClip_Code_020B2218:
    str lr, [sp, #-4]!
MobiClip_Code_020B221C:
    mov r5, #4
MobiClip_Code_020B2220:
    mov r6, #2
MobiClip_Code_020B2224:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B2228:
    pop {pc}
MobiClip_Code_020B222C:
    str lr, [sp, #-4]!
MobiClip_Code_020B2230:
    mov r5, #8
MobiClip_Code_020B2234:
    mov r6, #2
MobiClip_Code_020B2238:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B223C:
    pop {pc}
MobiClip_Code_020B2240:
    str lr, [sp, #-4]!
MobiClip_Code_020B2244:
    mov r5, #0xc
MobiClip_Code_020B2248:
    mov r6, #2
MobiClip_Code_020B224C:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B2250:
    pop {pc}
MobiClip_Code_020B2254:
    str lr, [sp, #-4]!
MobiClip_Code_020B2258:
    mov r5, #0x10
MobiClip_Code_020B225C:
    mov r6, #2
MobiClip_Code_020B2260:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B2264:
    pop {pc}
MobiClip_Code_020B2268:
    str lr, [sp, #-4]!
MobiClip_Code_020B226C:
    mov r5, #0x14
MobiClip_Code_020B2270:
    mov r6, #2
MobiClip_Code_020B2274:
    bl MobiClip_Code_020B1340
MobiClip_Code_020B2278:
    pop {pc}
MobiClip_Code_020B227C:
    lsr r6, r3, #0x1d
MobiClip_Code_020B2280:
    sub r5, pc, #0xd0
MobiClip_Code_020B2284:
    ldrb r5, [r5, r6]
MobiClip_Code_020B2288:
    sub r6, pc, #0xa8
MobiClip_Code_020B228C:
    ldrb r6, [r6, r5]
MobiClip_Code_020B2290:
    lsl r3, r3, r6
MobiClip_Code_020B2294:
    subs r2, r2, r6
MobiClip_Code_020B2298:
    mov r8, lr
MobiClip_Code_020B229C:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B22A0:
    sub r6, pc, #0xe8
MobiClip_Code_020B22A4:
    ldr r5, [r6, r5, lsl #2]
MobiClip_Code_020B22A8:
    mov lr, r8
MobiClip_Code_020B22AC:
    add pc, r5, r6
MobiClip_Code_020B22B0:
    push {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_020B22B4:
    ldr r1, [r0]
MobiClip_Code_020B22B8:
    mov r2, #0
MobiClip_Code_020B22BC:
    ldrh r3, [r1], #2
MobiClip_Code_020B22C0:
    lsl r3, r3, #0x10
MobiClip_Code_020B22C4:
    adds r3, r3, r3
MobiClip_Code_020B22C8:
    bhs MobiClip_Code_020B23DC
MobiClip_Code_020B22CC:
    subs r2, r2, #1
MobiClip_Code_020B22D0:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B22D4:
    bl MobiClip_Code_020B2C38
MobiClip_Code_020B22D8:
    cmp r6, #0
MobiClip_Code_020B22DC:
    ldrne r4, [r0, #0x3b4]
MobiClip_Code_020B22E0:
    addne r4, r4, r6
MobiClip_Code_020B22E4:
    blne MobiClip_Code_020b5514
MobiClip_Code_020B22E8:
    ldr fp, [r0, #0x3c]
MobiClip_Code_020B22EC:
    str fp, [r0, #0x3b8]
MobiClip_Code_020B22F0:
    add r4, r0, #0x3c4
MobiClip_Code_020B22F4:
    mov r5, #0
MobiClip_Code_020B22F8:
    mov r6, #0
MobiClip_Code_020B22FC:
    ldr ip, [r0, #4]
MobiClip_Code_020B2300:
    add ip, ip, #0x20
MobiClip_Code_020B2304:
    stm r4!, {r5, r6}
MobiClip_Code_020B2308:
    subs ip, ip, #0x10
MobiClip_Code_020B230C:
    bne MobiClip_Code_020B2304
MobiClip_Code_020B2310:
    mov fp, #0
MobiClip_Code_020B2314:
    ldr ip, [r0, #8]
MobiClip_Code_020B2318:
    str ip, [sp, #-4]!
MobiClip_Code_020B231C:
    add r4, r0, #0x3c4
MobiClip_Code_020B2320:
    ldr ip, [r0, #4]
MobiClip_Code_020B2324:
    ldm r4, {r5, r6, r7, r8, sb, sl}
MobiClip_Code_020B2328:
    add r4, r4, #8
MobiClip_Code_020B232C:
    cmp r5, r7
MobiClip_Code_020B2330:
    movgt lr, r5
MobiClip_Code_020B2334:
    movgt r5, r7
MobiClip_Code_020B2338:
    movgt r7, lr
MobiClip_Code_020B233C:
    cmp r7, sb
MobiClip_Code_020B2340:
    movgt lr, r7
MobiClip_Code_020B2344:
    movgt r7, sb
MobiClip_Code_020B2348:
    movgt sb, lr
MobiClip_Code_020B234C:
    cmp r5, r7
MobiClip_Code_020B2350:
    movgt lr, r5
MobiClip_Code_020B2354:
    movgt r5, r7
MobiClip_Code_020B2358:
    movgt r7, lr
MobiClip_Code_020B235C:
    cmp r6, r8
MobiClip_Code_020B2360:
    movgt lr, r6
MobiClip_Code_020B2364:
    movgt r6, r8
MobiClip_Code_020B2368:
    movgt r8, lr
MobiClip_Code_020B236C:
    cmp r8, sl
MobiClip_Code_020B2370:
    movgt lr, r8
MobiClip_Code_020B2374:
    movgt r8, sl
MobiClip_Code_020B2378:
    movgt sl, lr
MobiClip_Code_020B237C:
    cmp r6, r8
MobiClip_Code_020B2380:
    movgt lr, r6
MobiClip_Code_020B2384:
    movgt r6, r8
MobiClip_Code_020B2388:
    movgt r8, lr
MobiClip_Code_020B238C:
    add lr, r0, #0x3bc
MobiClip_Code_020B2390:
    stm lr, {r7, r8}
MobiClip_Code_020B2394:
    mov r7, #0
MobiClip_Code_020B2398:
    mov r8, #0
MobiClip_Code_020B239C:
    stm r4, {r7, r8}
MobiClip_Code_020B23A0:
    bl MobiClip_Code_020B0E6C
MobiClip_Code_020B23A4:
    add fp, fp, #0x10
MobiClip_Code_020B23A8:
    subs ip, ip, #0x10
MobiClip_Code_020B23AC:
    bne MobiClip_Code_020B2324
MobiClip_Code_020B23B0:
    pop {ip}
MobiClip_Code_020B23B4:
    ldr sl, [r0, #4]
MobiClip_Code_020B23B8:
    add fp, fp, #0x1000
MobiClip_Code_020B23BC:
    sub fp, fp, sl
MobiClip_Code_020B23C0:
    subs ip, ip, #0x10
MobiClip_Code_020B23C4:
    bne MobiClip_Code_020B2318
MobiClip_Code_020B23C8:
    ldr r2, [r0]
MobiClip_Code_020B23CC:
    sub r0, r1, r2
MobiClip_Code_020B23D0:
    sub r0, r0, #2
MobiClip_Code_020B23D4:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_020B23D8:
    bx lr
MobiClip_Code_020B23DC:
    adds r3, r3, r3
MobiClip_Code_020B23E0:
    movhs fp, #1
MobiClip_Code_020B23E4:
    movlo fp, #0
MobiClip_Code_020B23E8:
    str fp, [r0, #0x48]
MobiClip_Code_020B23EC:
    adds r3, r3, r3
MobiClip_Code_020B23F0:
    ldrlo fp, [r0, #0x3c]
MobiClip_Code_020B23F4:
    ldrhs fp, [r0, #0x40]
MobiClip_Code_020B23F8:
    str fp, [r0, #0x3b8]
MobiClip_Code_020B23FC:
    subs r2, r2, #3
MobiClip_Code_020B2400:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B2404:
    lsr r4, r3, #0x1a
MobiClip_Code_020B2408:
    lsl r3, r3, #6
MobiClip_Code_020B240C:
    subs r2, r2, #6
MobiClip_Code_020B2410:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B2414:
    ldr r5, [r0, #0x3b4]
MobiClip_Code_020B2418:
    cmp r5, r4
MobiClip_Code_020B241C:
    blne MobiClip_Code_020b5514
MobiClip_Code_020B2420:
    mov fp, #0
MobiClip_Code_020B2424:
    ldr ip, [r0, #8]
MobiClip_Code_020B2428:
    str ip, [sp, #-4]!
MobiClip_Code_020B242C:
    ldr ip, [r0, #4]
MobiClip_Code_020B2430:
    adds r3, r3, r3
MobiClip_Code_020B2434:
    addhs r4, pc, #0x14c
MobiClip_Code_020B2438:
    addlo r4, pc, #0x84
MobiClip_Code_020B243C:
    subs r2, r2, #1
MobiClip_Code_020B2440:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B2444:
    add lr, pc, #0
MobiClip_Code_020B2448:
    bx r4
MobiClip_Code_020B244C:
    add fp, fp, #0x10
MobiClip_Code_020B2450:
    subs ip, ip, #0x10
MobiClip_Code_020B2454:
    bne MobiClip_Code_020B2430
MobiClip_Code_020B2458:
    pop {ip}
MobiClip_Code_020B245C:
    ldr sl, [r0, #4]
MobiClip_Code_020B2460:
    add fp, fp, #0x1000
MobiClip_Code_020B2464:
    sub fp, fp, sl
MobiClip_Code_020B2468:
    subs ip, ip, #0x10
MobiClip_Code_020B246C:
    bne MobiClip_Code_020B2428
MobiClip_Code_020B2470:
    ldr r2, [r0]
MobiClip_Code_020B2474:
    sub r0, r1, r2
MobiClip_Code_020B2478:
    sub r0, r0, #2
MobiClip_Code_020B247C:
    pop {r4, r5, r6, r7, r8, sb, sl, fp, ip, lr}
MobiClip_Code_020B2480:
    bx lr
    /* semantic constants 0x0208e188..0x0208e1c8 */
    .global gMobiClipIFrameResidualPermutation
    .type gMobiClipIFrameResidualPermutation, %object
gMobiClipIFrameResidualPermutation:
    .byte 0x00, 0x1f, 0x3f, 0x0f, 0x08, 0x04, 0x02, 0x01, 0x0b, 0x0e, 0x1b, 0x0d, 0x03, 0x07, 0x0c, 0x17
    .byte 0x1d, 0x0a, 0x1e, 0x05, 0x10, 0x2f, 0x37, 0x3b, 0x13, 0x3d, 0x3e, 0x09, 0x1c, 0x06, 0x15, 0x1a
    .byte 0x33, 0x11, 0x12, 0x14, 0x18, 0x20, 0x3c, 0x35, 0x19, 0x16, 0x3a, 0x30, 0x31, 0x32, 0x27, 0x34
    .byte 0x2b, 0x2d, 0x39, 0x38, 0x23, 0x36, 0x2e, 0x21, 0x25, 0x22, 0x24, 0x2c, 0x2a, 0x28, 0x29, 0x26
MobiClip_Code_020B24C4:
    push {r4, ip, lr}
MobiClip_Code_020B24C8:
    bl MobiClip_Code_020B2BF4
MobiClip_Code_020B24CC:
    sub r4, pc, #0x50
MobiClip_Code_020B24D0:
    ldrb r4, [r4, r6]
MobiClip_Code_020B24D4:
    lsr ip, r3, #0x1d
MobiClip_Code_020B24D8:
    lsl r3, r3, #3
MobiClip_Code_020B24DC:
    subs r2, r2, #3
MobiClip_Code_020B24E0:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B24E4:
    ldr sl, [r0, #0xc]
MobiClip_Code_020B24E8:
    add fp, fp, sl
MobiClip_Code_020B24EC:
    cmp ip, #2
MobiClip_Code_020B24F0:
    moveq ip, #9
MobiClip_Code_020B24F4:
    bleq MobiClip_Code_020B2C78
MobiClip_Code_020B24F8:
    str r4, [sp, #-4]!
MobiClip_Code_020B24FC:
    tst r4, #1
MobiClip_Code_020B2500:
    add lr, pc, #0xc
MobiClip_Code_020B2504:
    bne MobiClip_Code_020B29C8
MobiClip_Code_020B2508:
    add r5, pc, #0x2c8
MobiClip_Code_020B250C:
    ldr r6, [r5, ip, lsl #2]
MobiClip_Code_020B2510:
    add pc, r6, r5
MobiClip_Code_020B2514:
    add fp, fp, #8
MobiClip_Code_020B2518:
    ldr r4, [sp]
MobiClip_Code_020B251C:
    tst r4, #2
MobiClip_Code_020B2520:
    add lr, pc, #0xc
MobiClip_Code_020B2524:
    bne MobiClip_Code_020B29C8
MobiClip_Code_020B2528:
    add r5, pc, #0x2a8
MobiClip_Code_020B252C:
    ldr r6, [r5, ip, lsl #2]
MobiClip_Code_020B2530:
    add pc, r6, r5
MobiClip_Code_020B2534:
    add fp, fp, #0x800
MobiClip_Code_020B2538:
    sub fp, fp, #8
MobiClip_Code_020B253C:
    ldr r4, [sp]
MobiClip_Code_020B2540:
    tst r4, #4
MobiClip_Code_020B2544:
    add lr, pc, #0xc
MobiClip_Code_020B2548:
    bne MobiClip_Code_020B29C8
MobiClip_Code_020B254C:
    add r5, pc, #0x284
MobiClip_Code_020B2550:
    ldr r6, [r5, ip, lsl #2]
MobiClip_Code_020B2554:
    add pc, r6, r5
MobiClip_Code_020B2558:
    add fp, fp, #8
MobiClip_Code_020B255C:
    ldr r4, [sp]
MobiClip_Code_020B2560:
    tst r4, #8
MobiClip_Code_020B2564:
    add lr, pc, #0xc
MobiClip_Code_020B2568:
    bne MobiClip_Code_020B29C8
MobiClip_Code_020B256C:
    add r5, pc, #0x264
MobiClip_Code_020B2570:
    ldr r6, [r5, ip, lsl #2]
MobiClip_Code_020B2574:
    add pc, r6, r5
MobiClip_Code_020B2578:
    sub fp, fp, #0x800
MobiClip_Code_020B257C:
    sub fp, fp, #8
MobiClip_Code_020B2580:
    sub fp, fp, sl
MobiClip_Code_020B2584:
    b MobiClip_Code_020B2750
MobiClip_Code_020B2588:
    push {r4, ip, lr}
MobiClip_Code_020B258C:
    bl MobiClip_Code_020B2BF4
MobiClip_Code_020B2590:
    sub r4, pc, #0x114
MobiClip_Code_020B2594:
    ldrb r4, [r4, r6]
MobiClip_Code_020B2598:
    ldr sl, [r0, #0xc]
MobiClip_Code_020B259C:
    add fp, fp, sl
MobiClip_Code_020B25A0:
    str r4, [sp, #-4]!
MobiClip_Code_020B25A4:
    add r5, r0, #0x55
MobiClip_Code_020B25A8:
    tst r4, #1
MobiClip_Code_020B25AC:
    add lr, pc, #4
MobiClip_Code_020B25B0:
    beq MobiClip_Code_020B26E0
MobiClip_Code_020B25B4:
    bne MobiClip_Code_020B2828
MobiClip_Code_020B25B8:
    add fp, fp, #8
MobiClip_Code_020B25BC:
    add r5, r0, #0x57
MobiClip_Code_020B25C0:
    ldr r4, [sp]
MobiClip_Code_020B25C4:
    tst r4, #2
MobiClip_Code_020B25C8:
    add lr, pc, #4
MobiClip_Code_020B25CC:
    beq MobiClip_Code_020B26E0
MobiClip_Code_020B25D0:
    bne MobiClip_Code_020B2828
MobiClip_Code_020B25D4:
    add fp, fp, #0x800
MobiClip_Code_020B25D8:
    sub fp, fp, #8
MobiClip_Code_020B25DC:
    add r5, r0, #0x65
MobiClip_Code_020B25E0:
    ldr r4, [sp]
MobiClip_Code_020B25E4:
    tst r4, #4
MobiClip_Code_020B25E8:
    add lr, pc, #4
MobiClip_Code_020B25EC:
    beq MobiClip_Code_020B26E0
MobiClip_Code_020B25F0:
    bne MobiClip_Code_020B2828
MobiClip_Code_020B25F4:
    add fp, fp, #8
MobiClip_Code_020B25F8:
    add r5, r0, #0x67
MobiClip_Code_020B25FC:
    ldr r4, [sp]
MobiClip_Code_020B2600:
    tst r4, #8
MobiClip_Code_020B2604:
    add lr, pc, #4
MobiClip_Code_020B2608:
    beq MobiClip_Code_020B26E0
MobiClip_Code_020B260C:
    bne MobiClip_Code_020B2828
MobiClip_Code_020B2610:
    sub fp, fp, #0x800
MobiClip_Code_020B2614:
    sub fp, fp, #8
MobiClip_Code_020B2618:
    sub fp, fp, sl
MobiClip_Code_020B261C:
    b MobiClip_Code_020B2750
    /* semantic constants 0x0208e324..0x0208e364 */
    .global gMobiClipPFrameResidualMask
    .type gMobiClipPFrameResidualMask, %object
gMobiClipPFrameResidualMask:
    .byte 0x00, 0x0f, 0x04, 0x01, 0x08, 0x02, 0x0c, 0x03, 0x05, 0x0a, 0x0d, 0x07, 0x0e, 0x0b, 0x1f, 0x09
    .byte 0x06, 0x10, 0x3f, 0x1e, 0x17, 0x1d, 0x1b, 0x1c, 0x13, 0x18, 0x1a, 0x12, 0x11, 0x14, 0x15, 0x20
    .byte 0x2f, 0x16, 0x19, 0x37, 0x3d, 0x3e, 0x3b, 0x3c, 0x33, 0x35, 0x21, 0x24, 0x22, 0x28, 0x23, 0x2c
    .byte 0x30, 0x27, 0x2d, 0x25, 0x3a, 0x2b, 0x2e, 0x2a, 0x31, 0x34, 0x38, 0x32, 0x29, 0x26, 0x39, 0x36
MobiClip_Code_020B2660:
    push {r4, ip, lr}
MobiClip_Code_020B2664:
    bl MobiClip_Code_020B2BF4
MobiClip_Code_020B2668:
    sub ip, pc, #0x50
MobiClip_Code_020B266C:
    ldrb ip, [ip, r6]
MobiClip_Code_020B2670:
    ldr sl, [r0, #0xc]
MobiClip_Code_020B2674:
    add fp, fp, sl
MobiClip_Code_020B2678:
    tst ip, #1
MobiClip_Code_020B267C:
    blne MobiClip_Code_020B29EC
MobiClip_Code_020B2680:
    add fp, fp, #8
MobiClip_Code_020B2684:
    tst ip, #2
MobiClip_Code_020B2688:
    blne MobiClip_Code_020B29EC
MobiClip_Code_020B268C:
    add fp, fp, #0x800
MobiClip_Code_020B2690:
    sub fp, fp, #8
MobiClip_Code_020B2694:
    tst ip, #4
MobiClip_Code_020B2698:
    blne MobiClip_Code_020B29EC
MobiClip_Code_020B269C:
    add fp, fp, #8
MobiClip_Code_020B26A0:
    tst ip, #8
MobiClip_Code_020B26A4:
    blne MobiClip_Code_020B29EC
MobiClip_Code_020B26A8:
    sub fp, fp, #0x800
MobiClip_Code_020B26AC:
    sub fp, fp, #8
MobiClip_Code_020B26B0:
    sub fp, fp, sl
MobiClip_Code_020B26B4:
    ldr sl, [r0, #0x24]
MobiClip_Code_020B26B8:
    add fp, sl, fp, lsr #1
MobiClip_Code_020B26BC:
    tst ip, #0x10
MobiClip_Code_020B26C0:
    blne MobiClip_Code_020B29EC
MobiClip_Code_020B26C4:
    add sl, sl, #0x80
MobiClip_Code_020B26C8:
    add fp, fp, #0x80
MobiClip_Code_020B26CC:
    tst ip, #0x20
MobiClip_Code_020B26D0:
    blne MobiClip_Code_020B29EC
MobiClip_Code_020B26D4:
    sub fp, fp, sl
MobiClip_Code_020B26D8:
    lsl fp, fp, #1
MobiClip_Code_020B26DC:
    pop {r4, ip, pc}
MobiClip_Code_020B26E0:
    ldrb ip, [r5, #-8]
MobiClip_Code_020B26E4:
    ldrb r6, [r5, #-1]
MobiClip_Code_020B26E8:
    cmp ip, r6
MobiClip_Code_020B26EC:
    movgt ip, r6
MobiClip_Code_020B26F0:
    cmp ip, #9
MobiClip_Code_020B26F4:
    moveq ip, #3
MobiClip_Code_020B26F8:
    lsr r6, r3, #0x1c
MobiClip_Code_020B26FC:
    cmp r6, ip
MobiClip_Code_020B2700:
    addge r6, r6, #1
MobiClip_Code_020B2704:
    cmp r6, #9
MobiClip_Code_020B2708:
    movlt ip, r6
MobiClip_Code_020B270C:
    movlt r7, #4
MobiClip_Code_020B2710:
    movge r7, #1
MobiClip_Code_020B2714:
    strb ip, [r5]
MobiClip_Code_020B2718:
    strb ip, [r5, #1]
MobiClip_Code_020B271C:
    strb ip, [r5, #8]
MobiClip_Code_020B2720:
    strb ip, [r5, #9]
MobiClip_Code_020B2724:
    add r6, pc, #0xac
MobiClip_Code_020B2728:
    ldr ip, [r6, ip, lsl #2]
MobiClip_Code_020B272C:
    add r6, r6, ip
MobiClip_Code_020B2730:
    lsl r3, r3, r7
MobiClip_Code_020B2734:
    subs r2, r2, r7
MobiClip_Code_020B2738:
    mov r8, sl
MobiClip_Code_020B273C:
    mov ip, lr
MobiClip_Code_020B2740:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B2744:
    mov sl, r8
MobiClip_Code_020B2748:
    mov lr, ip
MobiClip_Code_020B274C:
    mov pc, r6
MobiClip_Code_020B2750:
    lsr ip, r3, #0x1d
MobiClip_Code_020B2754:
    lsl r3, r3, #3
MobiClip_Code_020B2758:
    subs r2, r2, #3
MobiClip_Code_020B275C:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B2760:
    ldr sl, [r0, #0x24]
MobiClip_Code_020B2764:
    add fp, sl, fp, lsr #1
MobiClip_Code_020B2768:
    cmp ip, #2
MobiClip_Code_020B276C:
    bne MobiClip_Code_020B278C
MobiClip_Code_020B2770:
    mov ip, #9
MobiClip_Code_020B2774:
    bl MobiClip_Code_020B3188
MobiClip_Code_020B2778:
    add sl, sl, #0x80
MobiClip_Code_020B277C:
    add fp, fp, #0x80
MobiClip_Code_020B2780:
    bl MobiClip_Code_020B3188
MobiClip_Code_020B2784:
    sub sl, sl, #0x80
MobiClip_Code_020B2788:
    sub fp, fp, #0x80
MobiClip_Code_020B278C:
    ldr r4, [sp]
MobiClip_Code_020B2790:
    tst r4, #0x10
MobiClip_Code_020B2794:
    add lr, pc, #0xc
MobiClip_Code_020B2798:
    bne MobiClip_Code_020B29C8
MobiClip_Code_020B279C:
    add r5, pc, #0x34
MobiClip_Code_020B27A0:
    ldr r6, [r5, ip, lsl #2]
MobiClip_Code_020B27A4:
    add pc, r6, r5
MobiClip_Code_020B27A8:
    add sl, sl, #0x80
MobiClip_Code_020B27AC:
    add fp, fp, #0x80
MobiClip_Code_020B27B0:
    pop {r4}
MobiClip_Code_020B27B4:
    tst r4, #0x20
MobiClip_Code_020B27B8:
    add lr, pc, #0xc
MobiClip_Code_020B27BC:
    bne MobiClip_Code_020B29C8
MobiClip_Code_020B27C0:
    add r5, pc, #0x10
MobiClip_Code_020B27C4:
    ldr r6, [r5, ip, lsl #2]
MobiClip_Code_020B27C8:
    add pc, r6, r5
MobiClip_Code_020B27CC:
    sub fp, fp, sl
MobiClip_Code_020B27D0:
    lsl fp, fp, #1
MobiClip_Code_020B27D4:
    pop {r4, ip, pc}
    /* control metadata 0x0208e4dc..0x0208e52c */
    .global gMobiClip_intra_prediction_dispatch
    .type gMobiClip_intra_prediction_dispatch, %object
gMobiClip_intra_prediction_dispatch:
    /* intra_prediction */
    .global gMobiClip_intra_prediction
gMobiClip_intra_prediction:
    .word MobiClip_Code_020B3074 - .
    .word MobiClip_Code_020B30C0 - . + 0x4
    .word MobiClip_Code_020B3188 - . + 0x8
    .word MobiClip_Code_020B3604 - . + 0xc
    .word MobiClip_Code_020B3628 - . + 0x10
    .word MobiClip_Code_020B37CC - . + 0x14
    .word MobiClip_Code_020B3A24 - . + 0x18
    .word MobiClip_Code_020B3D78 - . + 0x1c
    .word MobiClip_Code_020B3FB0 - . + 0x20
    .word MobiClip_Code_020B2C74 - . + 0x24
    .word MobiClip_Code_020B42F0 - . + 0x28
    .word MobiClip_Code_020b430c - . + 0x2c
    .word MobiClip_Code_020b4354 - . + 0x30
    .word MobiClip_Code_020B45B8 - . + 0x34
    .word MobiClip_Code_020B45DC - . + 0x38
    .word MobiClip_Code_020b467c - . + 0x3c
    .word MobiClip_Code_020b4780 - . + 0x40
    .word MobiClip_Code_020B4888 - . + 0x44
    .word MobiClip_Code_020b4970 - . + 0x48
    .word MobiClip_Code_020B2C74 - . + 0x4c
MobiClip_Code_020B2828:
    tst r3, #0x80000000
MobiClip_Code_020B282C:
    beq MobiClip_Code_020B28F4
MobiClip_Code_020B2830:
    add r3, r3, r3
MobiClip_Code_020B2834:
    sub r2, r2, #1
MobiClip_Code_020B2838:
    ldrb ip, [r5, #-8]
MobiClip_Code_020B283C:
    ldrb r6, [r5, #-1]
MobiClip_Code_020B2840:
    cmp ip, r6
MobiClip_Code_020B2844:
    movgt ip, r6
MobiClip_Code_020B2848:
    cmp ip, #9
MobiClip_Code_020B284C:
    moveq ip, #3
MobiClip_Code_020B2850:
    lsr r6, r3, #0x1c
MobiClip_Code_020B2854:
    cmp r6, ip
MobiClip_Code_020B2858:
    addge r6, r6, #1
MobiClip_Code_020B285C:
    cmp r6, #9
MobiClip_Code_020B2860:
    movlt ip, r6
MobiClip_Code_020B2864:
    movlt r7, #4
MobiClip_Code_020B2868:
    movge r7, #1
MobiClip_Code_020B286C:
    lsl r3, r3, r7
MobiClip_Code_020B2870:
    subs r2, r2, r7
MobiClip_Code_020B2874:
    mov r7, lr
MobiClip_Code_020B2878:
    mov r8, sl
MobiClip_Code_020B287C:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B2880:
    mov lr, r7
MobiClip_Code_020B2884:
    mov sl, r8
MobiClip_Code_020B2888:
    strb ip, [r5]
MobiClip_Code_020B288C:
    strb ip, [r5, #1]
MobiClip_Code_020B2890:
    strb ip, [r5, #8]
MobiClip_Code_020B2894:
    strb ip, [r5, #9]
MobiClip_Code_020B2898:
    b MobiClip_Code_020B29D8
MobiClip_Code_020B289C:
    ldrb ip, [r5, #-8]
MobiClip_Code_020B28A0:
    ldrb r6, [r5, #-1]
MobiClip_Code_020B28A4:
    cmp ip, r6
MobiClip_Code_020B28A8:
    movgt ip, r6
MobiClip_Code_020B28AC:
    cmp ip, #9
MobiClip_Code_020B28B0:
    moveq ip, #3
MobiClip_Code_020B28B4:
    lsr r6, r3, #0x1c
MobiClip_Code_020B28B8:
    cmp r6, ip
MobiClip_Code_020B28BC:
    addge r6, r6, #1
MobiClip_Code_020B28C0:
    cmp r6, #9
MobiClip_Code_020B28C4:
    movlt ip, r6
MobiClip_Code_020B28C8:
    movlt r7, #4
MobiClip_Code_020B28CC:
    movge r7, #1
MobiClip_Code_020B28D0:
    strb ip, [r5]
MobiClip_Code_020B28D4:
    add ip, ip, #0xa
MobiClip_Code_020B28D8:
    lsl r3, r3, r7
MobiClip_Code_020B28DC:
    subs r2, r2, r7
MobiClip_Code_020B28E0:
    mov r8, sl
MobiClip_Code_020B28E4:
    mov r6, lr
MobiClip_Code_020B28E8:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B28EC:
    mov sl, r8
MobiClip_Code_020B28F0:
    mov pc, r6
MobiClip_Code_020B28F4:
    push {r5, lr}
MobiClip_Code_020B28F8:
    mov r8, sl
MobiClip_Code_020B28FC:
    bl MobiClip_Code_020B2BF4
MobiClip_Code_020B2900:
    add r4, pc, #0xac
MobiClip_Code_020B2904:
    ldrb r4, [r4, r6]
MobiClip_Code_020B2908:
    mov sl, r8
MobiClip_Code_020B290C:
    str r4, [sp, #-4]!
MobiClip_Code_020B2910:
    bl MobiClip_Code_020B289C
MobiClip_Code_020B2914:
    tst r4, #1
MobiClip_Code_020B2918:
    add lr, pc, #0xc
MobiClip_Code_020B291C:
    bne MobiClip_Code_020B2B90
MobiClip_Code_020B2920:
    sub r6, pc, #0x150
MobiClip_Code_020B2924:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_020B2928:
    add pc, r6, r7
MobiClip_Code_020B292C:
    add fp, fp, #4
MobiClip_Code_020B2930:
    ldm sp, {r4, r5}
MobiClip_Code_020B2934:
    add r5, r5, #1
MobiClip_Code_020B2938:
    bl MobiClip_Code_020B289C
MobiClip_Code_020B293C:
    tst r4, #2
MobiClip_Code_020B2940:
    add lr, pc, #0xc
MobiClip_Code_020B2944:
    bne MobiClip_Code_020B2B90
MobiClip_Code_020B2948:
    sub r6, pc, #0x178
MobiClip_Code_020B294C:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_020B2950:
    add pc, r6, r7
MobiClip_Code_020B2954:
    add fp, fp, #0x400
MobiClip_Code_020B2958:
    sub fp, fp, #4
MobiClip_Code_020B295C:
    ldm sp, {r4, r5}
MobiClip_Code_020B2960:
    add r5, r5, #8
MobiClip_Code_020B2964:
    bl MobiClip_Code_020B289C
MobiClip_Code_020B2968:
    tst r4, #4
MobiClip_Code_020B296C:
    add lr, pc, #0xc
MobiClip_Code_020B2970:
    bne MobiClip_Code_020B2B90
MobiClip_Code_020B2974:
    sub r6, pc, #0x1a4
MobiClip_Code_020B2978:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_020B297C:
    add pc, r6, r7
MobiClip_Code_020B2980:
    add fp, fp, #4
MobiClip_Code_020B2984:
    pop {r4, r5}
MobiClip_Code_020B2988:
    add r5, r5, #9
MobiClip_Code_020B298C:
    bl MobiClip_Code_020B289C
MobiClip_Code_020B2990:
    tst r4, #8
MobiClip_Code_020B2994:
    add lr, pc, #0xc
MobiClip_Code_020B2998:
    bne MobiClip_Code_020B2B90
MobiClip_Code_020B299C:
    sub r6, pc, #0x1cc
MobiClip_Code_020B29A0:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_020B29A4:
    add pc, r6, r7
MobiClip_Code_020B29A8:
    sub fp, fp, #0x400
MobiClip_Code_020B29AC:
    sub fp, fp, #4
MobiClip_Code_020B29B0:
    pop {pc}
    /* semantic constants 0x0208e6b8..0x0208e6cc */
    .global gMobiClipIntraCoefficientMaskPadded
    .type gMobiClipIntraCoefficientMaskPadded, %object
gMobiClipIntraCoefficientMaskPadded:
    .byte 0x00, 0x0f, 0x00, 0x02, 0x01, 0x04, 0x08, 0x0c, 0x03, 0x0b, 0x0d, 0x0e, 0x07, 0x0a, 0x05, 0x09
    .byte 0x06, 0x00, 0x00, 0x00
MobiClip_Code_020B29C8:
    tst r3, #0x80000000
MobiClip_Code_020B29CC:
    beq MobiClip_Code_020B2AE8
MobiClip_Code_020B29D0:
    add r3, r3, r3
MobiClip_Code_020B29D4:
    sub r2, r2, #1
MobiClip_Code_020B29D8:
    push {sl, fp, ip, lr}
MobiClip_Code_020B29DC:
    add lr, pc, #0x1c
MobiClip_Code_020B29E0:
    sub r5, pc, #0x210
MobiClip_Code_020B29E4:
    ldr ip, [r5, ip, lsl #2]
MobiClip_Code_020B29E8:
    add pc, ip, r5
MobiClip_Code_020B29EC:
    tst r3, #0x80000000
MobiClip_Code_020B29F0:
    beq MobiClip_Code_020B2A94
MobiClip_Code_020B29F4:
    add r3, r3, r3
MobiClip_Code_020B29F8:
    sub r2, r2, #1
MobiClip_Code_020B29FC:
    push {sl, fp, ip, lr}
MobiClip_Code_020B2A00:
    mov r4, #0
MobiClip_Code_020B2A04:
    mov r5, #0
MobiClip_Code_020B2A08:
    mov r6, #0
MobiClip_Code_020B2A0C:
    mov r7, #0
MobiClip_Code_020B2A10:
    mov r8, #0
MobiClip_Code_020B2A14:
    mov sb, #0
MobiClip_Code_020B2A18:
    mov sl, #0
MobiClip_Code_020B2A1C:
    mov fp, #0
MobiClip_Code_020B2A20:
    add ip, r0, #0x1b4
MobiClip_Code_020B2A24:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_020B2A28:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_020B2A2C:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_020B2A30:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_020B2A34:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_020B2A38:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_020B2A3C:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_020B2A40:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_020B2A44:
    add ip, r0, #0x74
MobiClip_Code_020B2A48:
    bl MobiClip_Code_020b4b5c
MobiClip_Code_020B2A4C:
    sub ip, ip, r0
MobiClip_Code_020B2A50:
    add r4, pc, #0x38
MobiClip_Code_020B2A54:
    add r4, r4, #0x2600
MobiClip_Code_020B2A58:
    cmp ip, #0x78
MobiClip_Code_020B2A5C:
    movle pc, r4
MobiClip_Code_020B2A60:
    add r4, pc, #8
MobiClip_Code_020B2A64:
    add r4, r4, #0x2500
MobiClip_Code_020B2A68:
    cmp ip, #0x80
MobiClip_Code_020B2A6C:
    movle pc, r4
MobiClip_Code_020B2A70:
    add r4, pc, #0x4c
MobiClip_Code_020B2A74:
    add r4, r4, #0x2300
MobiClip_Code_020B2A78:
    cmp ip, #0x9c
MobiClip_Code_020B2A7C:
    movle pc, r4
MobiClip_Code_020B2A80:
    b MobiClip_Code_020B4BCC
    /* semantic constants 0x0208e788..0x0208e798 */
    .global gMobiClipPFrameCoefficientMask
    .type gMobiClipPFrameCoefficientMask, %object
gMobiClipPFrameCoefficientMask:
    .byte 0x00, 0x04, 0x01, 0x08, 0x02, 0x0c, 0x03, 0x05, 0x0a, 0x0f, 0x07, 0x0d, 0x0e, 0x0b, 0x09, 0x06
MobiClip_Code_020B2A94:
    push {ip, lr}
MobiClip_Code_020B2A98:
    mov r8, sl
MobiClip_Code_020B2A9C:
    bl MobiClip_Code_020B2BF4
MobiClip_Code_020B2AA0:
    mov sl, r8
MobiClip_Code_020B2AA4:
    sub ip, pc, #0x28
MobiClip_Code_020B2AA8:
    ldrb ip, [ip, r6]
MobiClip_Code_020B2AAC:
    tst ip, #1
MobiClip_Code_020B2AB0:
    blne MobiClip_Code_020B2BA4
MobiClip_Code_020B2AB4:
    add fp, fp, #4
MobiClip_Code_020B2AB8:
    tst ip, #2
MobiClip_Code_020B2ABC:
    blne MobiClip_Code_020B2BA4
MobiClip_Code_020B2AC0:
    add fp, fp, #0x400
MobiClip_Code_020B2AC4:
    sub fp, fp, #4
MobiClip_Code_020B2AC8:
    tst ip, #4
MobiClip_Code_020B2ACC:
    blne MobiClip_Code_020B2BA4
MobiClip_Code_020B2AD0:
    add fp, fp, #4
MobiClip_Code_020B2AD4:
    tst ip, #8
MobiClip_Code_020B2AD8:
    blne MobiClip_Code_020B2BA4
MobiClip_Code_020B2ADC:
    sub fp, fp, #0x400
MobiClip_Code_020B2AE0:
    sub fp, fp, #4
MobiClip_Code_020B2AE4:
    pop {ip, pc}
MobiClip_Code_020B2AE8:
    push {ip, lr}
MobiClip_Code_020B2AEC:
    add ip, ip, #0xa
MobiClip_Code_020B2AF0:
    mov r8, sl
MobiClip_Code_020B2AF4:
    bl MobiClip_Code_020B2BF4
MobiClip_Code_020B2AF8:
    sub r4, pc, #0x14c
MobiClip_Code_020B2AFC:
    ldrb r4, [r4, r6]
MobiClip_Code_020B2B00:
    mov sl, r8
MobiClip_Code_020B2B04:
    str r4, [sp, #-4]!
MobiClip_Code_020B2B08:
    tst r4, #1
MobiClip_Code_020B2B0C:
    add lr, pc, #0xc
MobiClip_Code_020B2B10:
    bne MobiClip_Code_020B2B90
MobiClip_Code_020B2B14:
    sub r6, pc, #0x344
MobiClip_Code_020B2B18:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_020B2B1C:
    add pc, r6, r7
MobiClip_Code_020B2B20:
    add fp, fp, #4
MobiClip_Code_020B2B24:
    ldr r4, [sp]
MobiClip_Code_020B2B28:
    tst r4, #2
MobiClip_Code_020B2B2C:
    add lr, pc, #0xc
MobiClip_Code_020B2B30:
    bne MobiClip_Code_020B2B90
MobiClip_Code_020B2B34:
    sub r6, pc, #0x364
MobiClip_Code_020B2B38:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_020B2B3C:
    add pc, r6, r7
MobiClip_Code_020B2B40:
    add fp, fp, #0x400
MobiClip_Code_020B2B44:
    sub fp, fp, #4
MobiClip_Code_020B2B48:
    ldr r4, [sp]
MobiClip_Code_020B2B4C:
    tst r4, #4
MobiClip_Code_020B2B50:
    add lr, pc, #0xc
MobiClip_Code_020B2B54:
    bne MobiClip_Code_020B2B90
MobiClip_Code_020B2B58:
    sub r6, pc, #0x388
MobiClip_Code_020B2B5C:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_020B2B60:
    add pc, r6, r7
MobiClip_Code_020B2B64:
    add fp, fp, #4
MobiClip_Code_020B2B68:
    pop {r4}
MobiClip_Code_020B2B6C:
    tst r4, #8
MobiClip_Code_020B2B70:
    add lr, pc, #0xc
MobiClip_Code_020B2B74:
    bne MobiClip_Code_020B2B90
MobiClip_Code_020B2B78:
    sub r6, pc, #0x3a8
MobiClip_Code_020B2B7C:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_020B2B80:
    add pc, r6, r7
MobiClip_Code_020B2B84:
    sub fp, fp, #0x400
MobiClip_Code_020B2B88:
    sub fp, fp, #4
MobiClip_Code_020B2B8C:
    pop {ip, pc}
MobiClip_Code_020B2B90:
    push {sl, fp, ip, lr}
MobiClip_Code_020B2B94:
    add lr, pc, #0xc
MobiClip_Code_020B2B98:
    sub r6, pc, #0x3c8
MobiClip_Code_020B2B9C:
    ldr r7, [r6, ip, lsl #2]
MobiClip_Code_020B2BA0:
    add pc, r6, r7
MobiClip_Code_020B2BA4:
    push {sl, fp, ip, lr}
MobiClip_Code_020B2BA8:
    mov r4, #0
MobiClip_Code_020B2BAC:
    mov r5, #0
MobiClip_Code_020B2BB0:
    mov r6, #0
MobiClip_Code_020B2BB4:
    mov r7, #0
MobiClip_Code_020B2BB8:
    mov r8, #0
MobiClip_Code_020B2BBC:
    mov sb, #0
MobiClip_Code_020B2BC0:
    mov sl, #0
MobiClip_Code_020B2BC4:
    mov fp, #0
MobiClip_Code_020B2BC8:
    add ip, r0, #0x1b4
MobiClip_Code_020B2BCC:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_020B2BD0:
    stm ip!, {r4, r5, r6, r7, r8, sb, sl, fp}
MobiClip_Code_020B2BD4:
    add ip, r0, #0x174
MobiClip_Code_020B2BD8:
    bl MobiClip_Code_020b4b5c
MobiClip_Code_020B2BDC:
    sub ip, ip, r0
MobiClip_Code_020B2BE0:
    add r4, pc, #0x28
MobiClip_Code_020B2BE4:
    add r4, r4, #0x2600
MobiClip_Code_020B2BE8:
    cmp ip, #0x178
MobiClip_Code_020B2BEC:
    movle pc, r4
MobiClip_Code_020B2BF0:
    b MobiClip_Code_020B513C
MobiClip_Code_020B2BF4:
    clz sl, r3
MobiClip_Code_020B2BF8:
    lsl r3, r3, sl
MobiClip_Code_020B2BFC:
    add r3, r3, r3
MobiClip_Code_020B2C00:
    rsb sb, sl, #0x20
MobiClip_Code_020B2C04:
    lsr r6, r3, sb
MobiClip_Code_020B2C08:
    mov sb, #1
MobiClip_Code_020B2C0C:
    add r6, r6, sb, lsl sl
MobiClip_Code_020B2C10:
    sub r6, r6, #1
MobiClip_Code_020B2C14:
    lsl r3, r3, sl
MobiClip_Code_020B2C18:
    sub r2, r2, sl, lsl #1
MobiClip_Code_020B2C1C:
    subs r2, r2, #1
MobiClip_Code_020B2C20:
    movge pc, lr
MobiClip_Code_020B2C24:
    ldrh sl, [r1], #2
MobiClip_Code_020B2C28:
    add r2, r2, #0x10
MobiClip_Code_020B2C2C:
    rsb sb, r2, #0x10
MobiClip_Code_020B2C30:
    orr r3, r3, sl, lsl sb
MobiClip_Code_020B2C34:
    mov pc, lr
MobiClip_Code_020B2C38:
    clz sl, r3
MobiClip_Code_020B2C3C:
    lsl r3, r3, sl
MobiClip_Code_020B2C40:
    add r3, r3, r3
MobiClip_Code_020B2C44:
    rsb sb, sl, #0x20
MobiClip_Code_020B2C48:
    lsr r6, r3, sb
MobiClip_Code_020B2C4C:
    mov sb, #1
MobiClip_Code_020B2C50:
    add r6, r6, sb, lsl sl
MobiClip_Code_020B2C54:
    tst r6, #1
MobiClip_Code_020B2C58:
    rsbne r6, r6, #1
MobiClip_Code_020B2C5C:
    asr r6, r6, #1
MobiClip_Code_020B2C60:
    lsl r3, r3, sl
MobiClip_Code_020B2C64:
    sub r2, r2, sl, lsl #1
MobiClip_Code_020B2C68:
    subs r2, r2, #1
MobiClip_Code_020B2C6C:
    movge pc, lr
MobiClip_Code_020B2C70:
    b MobiClip_Code_020B2C24
MobiClip_Code_020B2C74:
    mov pc, lr
MobiClip_Code_020B2C78:
    push {r4, sl, ip, lr}
MobiClip_Code_020B2C7C:
    bl MobiClip_Code_020B2C38
MobiClip_Code_020B2C80:
    push {r0, r1, r2, r3}
MobiClip_Code_020B2C84:
    sub lr, fp, #0x100
MobiClip_Code_020B2C88:
    ldm lr, {r0, r1, r2, r3}
MobiClip_Code_020B2C8C:
    add lr, fp, #0xf00
MobiClip_Code_020B2C90:
    ldrb r4, [lr, #-1]
MobiClip_Code_020B2C94:
    lsr sl, r3, #0x18
MobiClip_Code_020B2C98:
    add r5, r4, sl
MobiClip_Code_020B2C9C:
    add r5, r5, #1
MobiClip_Code_020B2CA0:
    asr r5, r5, #1
MobiClip_Code_020B2CA4:
    add r5, r5, r6, lsl #1
MobiClip_Code_020B2CA8:
    sub r6, r5, r4
MobiClip_Code_020B2CAC:
    add r6, r6, #1
MobiClip_Code_020B2CB0:
    lsl r4, r4, #3
MobiClip_Code_020B2CB4:
    sub sp, sp, #0x80
MobiClip_Code_020B2CB8:
    mov lr, sp
MobiClip_Code_020B2CBC:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2CC0:
    mov r8, #0xff
MobiClip_Code_020B2CC4:
    and r7, r8, r0
MobiClip_Code_020B2CC8:
    sub r8, r4, r7, lsl #3
MobiClip_Code_020B2CCC:
    add r8, r8, #1
MobiClip_Code_020B2CD0:
    lsl r7, r7, #6
MobiClip_Code_020B2CD4:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2CD8:
    mov ip, #0xff
MobiClip_Code_020B2CDC:
    and sb, ip, r0, lsr #8
MobiClip_Code_020B2CE0:
    sub ip, r4, sb, lsl #3
MobiClip_Code_020B2CE4:
    add ip, ip, #1
MobiClip_Code_020B2CE8:
    lsl sb, sb, #6
MobiClip_Code_020B2CEC:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020B2CF0:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2CF4:
    mov r8, #0xff
MobiClip_Code_020B2CF8:
    and r7, r8, r0, lsr #16
MobiClip_Code_020B2CFC:
    sub r8, r4, r7, lsl #3
MobiClip_Code_020B2D00:
    add r8, r8, #1
MobiClip_Code_020B2D04:
    lsl r7, r7, #6
MobiClip_Code_020B2D08:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2D0C:
    mov ip, #0xff
MobiClip_Code_020B2D10:
    and sb, ip, r0, lsr #24
MobiClip_Code_020B2D14:
    sub ip, r4, sb, lsl #3
MobiClip_Code_020B2D18:
    add ip, ip, #1
MobiClip_Code_020B2D1C:
    lsl sb, sb, #6
MobiClip_Code_020B2D20:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020B2D24:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2D28:
    mov r8, #0xff
MobiClip_Code_020B2D2C:
    and r7, r8, r1
MobiClip_Code_020B2D30:
    sub r8, r4, r7, lsl #3
MobiClip_Code_020B2D34:
    add r8, r8, #1
MobiClip_Code_020B2D38:
    lsl r7, r7, #6
MobiClip_Code_020B2D3C:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2D40:
    mov ip, #0xff
MobiClip_Code_020B2D44:
    and sb, ip, r1, lsr #8
MobiClip_Code_020B2D48:
    sub ip, r4, sb, lsl #3
MobiClip_Code_020B2D4C:
    add ip, ip, #1
MobiClip_Code_020B2D50:
    lsl sb, sb, #6
MobiClip_Code_020B2D54:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020B2D58:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2D5C:
    mov r8, #0xff
MobiClip_Code_020B2D60:
    and r7, r8, r1, lsr #16
MobiClip_Code_020B2D64:
    sub r8, r4, r7, lsl #3
MobiClip_Code_020B2D68:
    add r8, r8, #1
MobiClip_Code_020B2D6C:
    lsl r7, r7, #6
MobiClip_Code_020B2D70:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2D74:
    mov ip, #0xff
MobiClip_Code_020B2D78:
    and sb, ip, r1, lsr #24
MobiClip_Code_020B2D7C:
    sub ip, r4, sb, lsl #3
MobiClip_Code_020B2D80:
    add ip, ip, #1
MobiClip_Code_020B2D84:
    lsl sb, sb, #6
MobiClip_Code_020B2D88:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020B2D8C:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2D90:
    mov r8, #0xff
MobiClip_Code_020B2D94:
    and r7, r8, r2
MobiClip_Code_020B2D98:
    sub r8, r4, r7, lsl #3
MobiClip_Code_020B2D9C:
    add r8, r8, #1
MobiClip_Code_020B2DA0:
    lsl r7, r7, #6
MobiClip_Code_020B2DA4:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2DA8:
    mov ip, #0xff
MobiClip_Code_020B2DAC:
    and sb, ip, r2, lsr #8
MobiClip_Code_020B2DB0:
    sub ip, r4, sb, lsl #3
MobiClip_Code_020B2DB4:
    add ip, ip, #1
MobiClip_Code_020B2DB8:
    lsl sb, sb, #6
MobiClip_Code_020B2DBC:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020B2DC0:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2DC4:
    mov r8, #0xff
MobiClip_Code_020B2DC8:
    and r7, r8, r2, lsr #16
MobiClip_Code_020B2DCC:
    sub r8, r4, r7, lsl #3
MobiClip_Code_020B2DD0:
    add r8, r8, #1
MobiClip_Code_020B2DD4:
    lsl r7, r7, #6
MobiClip_Code_020B2DD8:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2DDC:
    mov ip, #0xff
MobiClip_Code_020B2DE0:
    and sb, ip, r2, lsr #24
MobiClip_Code_020B2DE4:
    sub ip, r4, sb, lsl #3
MobiClip_Code_020B2DE8:
    add ip, ip, #1
MobiClip_Code_020B2DEC:
    lsl sb, sb, #6
MobiClip_Code_020B2DF0:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020B2DF4:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2DF8:
    mov r8, #0xff
MobiClip_Code_020B2DFC:
    and r7, r8, r3
MobiClip_Code_020B2E00:
    sub r8, r4, r7, lsl #3
MobiClip_Code_020B2E04:
    add r8, r8, #1
MobiClip_Code_020B2E08:
    lsl r7, r7, #6
MobiClip_Code_020B2E0C:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2E10:
    mov ip, #0xff
MobiClip_Code_020B2E14:
    and sb, ip, r3, lsr #8
MobiClip_Code_020B2E18:
    sub ip, r4, sb, lsl #3
MobiClip_Code_020B2E1C:
    add ip, ip, #1
MobiClip_Code_020B2E20:
    lsl sb, sb, #6
MobiClip_Code_020B2E24:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020B2E28:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2E2C:
    mov r8, #0xff
MobiClip_Code_020B2E30:
    and r7, r8, r3, lsr #16
MobiClip_Code_020B2E34:
    sub r8, r4, r7, lsl #3
MobiClip_Code_020B2E38:
    add r8, r8, #1
MobiClip_Code_020B2E3C:
    lsl r7, r7, #6
MobiClip_Code_020B2E40:
    add r4, r4, r6, asr #1
MobiClip_Code_020B2E44:
    mov ip, #0xff
MobiClip_Code_020B2E48:
    and sb, ip, r3, lsr #24
MobiClip_Code_020B2E4C:
    sub ip, r4, sb, lsl #3
MobiClip_Code_020B2E50:
    add ip, ip, #1
MobiClip_Code_020B2E54:
    lsl sb, sb, #6
MobiClip_Code_020B2E58:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020B2E5C:
    sub sb, r5, sl
MobiClip_Code_020B2E60:
    add sb, sb, #1
MobiClip_Code_020B2E64:
    lsl sl, sl, #3
MobiClip_Code_020B2E68:
    mov lr, #0x10
MobiClip_Code_020B2E6C:
    add sl, sl, sb, asr #1
MobiClip_Code_020B2E70:
    ldrb r8, [fp, #-1]
MobiClip_Code_020B2E74:
    sub r7, sl, r8, lsl #3
MobiClip_Code_020B2E78:
    add r7, r7, #1
MobiClip_Code_020B2E7C:
    lsl r8, r8, #6
MobiClip_Code_020B2E80:
    add ip, sp, #0
MobiClip_Code_020B2E84:
    ldm ip, {r0, r1, r2, r3, r4, r5, r6, ip}
MobiClip_Code_020B2E88:
    add r0, r0, r1, asr #1
MobiClip_Code_020B2E8C:
    add r2, r2, r3, asr #1
MobiClip_Code_020B2E90:
    add r4, r4, r5, asr #1
MobiClip_Code_020B2E94:
    add r6, r6, ip, asr #1
MobiClip_Code_020B2E98:
    str r0, [sp]
MobiClip_Code_020B2E9C:
    str r2, [sp, #8]
MobiClip_Code_020B2EA0:
    str r4, [sp, #0x10]
MobiClip_Code_020B2EA4:
    str r6, [sp, #0x18]
MobiClip_Code_020B2EA8:
    add r8, r8, r7, asr #1
MobiClip_Code_020B2EAC:
    add r5, r0, r8
MobiClip_Code_020B2EB0:
    add r5, r5, #0x40
MobiClip_Code_020B2EB4:
    asr r5, r5, #7
MobiClip_Code_020B2EB8:
    add r8, r8, r7, asr #1
MobiClip_Code_020B2EBC:
    add ip, r2, r8
MobiClip_Code_020B2EC0:
    add ip, ip, #0x40
MobiClip_Code_020B2EC4:
    asr ip, ip, #7
MobiClip_Code_020B2EC8:
    orr r5, r5, ip, lsl #8
MobiClip_Code_020B2ECC:
    add r8, r8, r7, asr #1
MobiClip_Code_020B2ED0:
    add ip, r4, r8
MobiClip_Code_020B2ED4:
    add ip, ip, #0x40
MobiClip_Code_020B2ED8:
    asr ip, ip, #7
MobiClip_Code_020B2EDC:
    orr r5, r5, ip, lsl #16
MobiClip_Code_020B2EE0:
    add r8, r8, r7, asr #1
MobiClip_Code_020B2EE4:
    add ip, r6, r8
MobiClip_Code_020B2EE8:
    add ip, ip, #0x40
MobiClip_Code_020B2EEC:
    asr ip, ip, #7
MobiClip_Code_020B2EF0:
    orr r5, r5, ip, lsl #24
MobiClip_Code_020B2EF4:
    str r5, [fp], #4
MobiClip_Code_020B2EF8:
    add ip, sp, #0x20
MobiClip_Code_020B2EFC:
    ldm ip, {r0, r1, r2, r3, r4, r5, r6, ip}
MobiClip_Code_020B2F00:
    add r0, r0, r1, asr #1
MobiClip_Code_020B2F04:
    add r2, r2, r3, asr #1
MobiClip_Code_020B2F08:
    add r4, r4, r5, asr #1
MobiClip_Code_020B2F0C:
    add r6, r6, ip, asr #1
MobiClip_Code_020B2F10:
    str r0, [sp, #0x20]
MobiClip_Code_020B2F14:
    str r2, [sp, #0x28]
MobiClip_Code_020B2F18:
    str r4, [sp, #0x30]
MobiClip_Code_020B2F1C:
    str r6, [sp, #0x38]
MobiClip_Code_020B2F20:
    add r8, r8, r7, asr #1
MobiClip_Code_020B2F24:
    add r5, r0, r8
MobiClip_Code_020B2F28:
    add r5, r5, #0x40
MobiClip_Code_020B2F2C:
    asr r5, r5, #7
MobiClip_Code_020B2F30:
    add r8, r8, r7, asr #1
MobiClip_Code_020B2F34:
    add ip, r2, r8
MobiClip_Code_020B2F38:
    add ip, ip, #0x40
MobiClip_Code_020B2F3C:
    asr ip, ip, #7
MobiClip_Code_020B2F40:
    orr r5, r5, ip, lsl #8
MobiClip_Code_020B2F44:
    add r8, r8, r7, asr #1
MobiClip_Code_020B2F48:
    add ip, r4, r8
MobiClip_Code_020B2F4C:
    add ip, ip, #0x40
MobiClip_Code_020B2F50:
    asr ip, ip, #7
MobiClip_Code_020B2F54:
    orr r5, r5, ip, lsl #16
MobiClip_Code_020B2F58:
    add r8, r8, r7, asr #1
MobiClip_Code_020B2F5C:
    add ip, r6, r8
MobiClip_Code_020B2F60:
    add ip, ip, #0x40
MobiClip_Code_020B2F64:
    asr ip, ip, #7
MobiClip_Code_020B2F68:
    orr r5, r5, ip, lsl #24
MobiClip_Code_020B2F6C:
    str r5, [fp], #4
MobiClip_Code_020B2F70:
    add ip, sp, #0x40
MobiClip_Code_020B2F74:
    ldm ip, {r0, r1, r2, r3, r4, r5, r6, ip}
MobiClip_Code_020B2F78:
    add r0, r0, r1, asr #1
MobiClip_Code_020B2F7C:
    add r2, r2, r3, asr #1
MobiClip_Code_020B2F80:
    add r4, r4, r5, asr #1
MobiClip_Code_020B2F84:
    add r6, r6, ip, asr #1
MobiClip_Code_020B2F88:
    str r0, [sp, #0x40]
MobiClip_Code_020B2F8C:
    str r2, [sp, #0x48]
MobiClip_Code_020B2F90:
    str r4, [sp, #0x50]
MobiClip_Code_020B2F94:
    str r6, [sp, #0x58]
MobiClip_Code_020B2F98:
    add r8, r8, r7, asr #1
MobiClip_Code_020B2F9C:
    add r5, r0, r8
MobiClip_Code_020B2FA0:
    add r5, r5, #0x40
MobiClip_Code_020B2FA4:
    asr r5, r5, #7
MobiClip_Code_020B2FA8:
    add r8, r8, r7, asr #1
MobiClip_Code_020B2FAC:
    add ip, r2, r8
MobiClip_Code_020B2FB0:
    add ip, ip, #0x40
MobiClip_Code_020B2FB4:
    asr ip, ip, #7
MobiClip_Code_020B2FB8:
    orr r5, r5, ip, lsl #8
MobiClip_Code_020B2FBC:
    add r8, r8, r7, asr #1
MobiClip_Code_020B2FC0:
    add ip, r4, r8
MobiClip_Code_020B2FC4:
    add ip, ip, #0x40
MobiClip_Code_020B2FC8:
    asr ip, ip, #7
MobiClip_Code_020B2FCC:
    orr r5, r5, ip, lsl #16
MobiClip_Code_020B2FD0:
    add r8, r8, r7, asr #1
MobiClip_Code_020B2FD4:
    add ip, r6, r8
MobiClip_Code_020B2FD8:
    add ip, ip, #0x40
MobiClip_Code_020B2FDC:
    asr ip, ip, #7
MobiClip_Code_020B2FE0:
    orr r5, r5, ip, lsl #24
MobiClip_Code_020B2FE4:
    str r5, [fp], #4
MobiClip_Code_020B2FE8:
    add ip, sp, #0x60
MobiClip_Code_020B2FEC:
    ldm ip, {r0, r1, r2, r3, r4, r5, r6, ip}
MobiClip_Code_020B2FF0:
    add r0, r0, r1, asr #1
MobiClip_Code_020B2FF4:
    add r2, r2, r3, asr #1
MobiClip_Code_020B2FF8:
    add r4, r4, r5, asr #1
MobiClip_Code_020B2FFC:
    add r6, r6, ip, asr #1
MobiClip_Code_020B3000:
    str r0, [sp, #0x60]
MobiClip_Code_020B3004:
    str r2, [sp, #0x68]
MobiClip_Code_020B3008:
    str r4, [sp, #0x70]
MobiClip_Code_020B300C:
    str r6, [sp, #0x78]
MobiClip_Code_020B3010:
    add r8, r8, r7, asr #1
MobiClip_Code_020B3014:
    add r5, r0, r8
MobiClip_Code_020B3018:
    add r5, r5, #0x40
MobiClip_Code_020B301C:
    asr r5, r5, #7
MobiClip_Code_020B3020:
    add r8, r8, r7, asr #1
MobiClip_Code_020B3024:
    add ip, r2, r8
MobiClip_Code_020B3028:
    add ip, ip, #0x40
MobiClip_Code_020B302C:
    asr ip, ip, #7
MobiClip_Code_020B3030:
    orr r5, r5, ip, lsl #8
MobiClip_Code_020B3034:
    add r8, r8, r7, asr #1
MobiClip_Code_020B3038:
    add ip, r4, r8
MobiClip_Code_020B303C:
    add ip, ip, #0x40
MobiClip_Code_020B3040:
    asr ip, ip, #7
MobiClip_Code_020B3044:
    orr r5, r5, ip, lsl #16
MobiClip_Code_020B3048:
    add r8, r8, r7, asr #1
MobiClip_Code_020B304C:
    add ip, r6, r8
MobiClip_Code_020B3050:
    add ip, ip, #0x40
MobiClip_Code_020B3054:
    asr ip, ip, #7
MobiClip_Code_020B3058:
    orr r5, r5, ip, lsl #24
MobiClip_Code_020B305C:
    str r5, [fp], #0xf4
MobiClip_Code_020B3060:
    subs lr, lr, #1
MobiClip_Code_020B3064:
    bne MobiClip_Code_020B2E6C
MobiClip_Code_020B3068:
    add sp, sp, #0x80
MobiClip_Code_020B306C:
    sub fp, fp, #0x1000
MobiClip_Code_020B3070:
    pop {r0, r1, r2, r3, r4, sl, ip, pc}
MobiClip_Code_020B3074:
    sub r7, fp, #0x100
MobiClip_Code_020B3078:
    ldm r7, {r4, r5}
MobiClip_Code_020B307C:
    add r7, r7, #0x100
MobiClip_Code_020B3080:
    stm r7, {r4, r5}
MobiClip_Code_020B3084:
    add r7, r7, #0x100
MobiClip_Code_020B3088:
    stm r7, {r4, r5}
MobiClip_Code_020B308C:
    add r7, r7, #0x100
MobiClip_Code_020B3090:
    stm r7, {r4, r5}
MobiClip_Code_020B3094:
    add r7, r7, #0x100
MobiClip_Code_020B3098:
    stm r7, {r4, r5}
MobiClip_Code_020B309C:
    add r7, r7, #0x100
MobiClip_Code_020B30A0:
    stm r7, {r4, r5}
MobiClip_Code_020B30A4:
    add r7, r7, #0x100
MobiClip_Code_020B30A8:
    stm r7, {r4, r5}
MobiClip_Code_020B30AC:
    add r7, r7, #0x100
MobiClip_Code_020B30B0:
    stm r7, {r4, r5}
MobiClip_Code_020B30B4:
    add r7, r7, #0x100
MobiClip_Code_020B30B8:
    stm r7, {r4, r5}
MobiClip_Code_020B30BC:
    mov pc, lr
MobiClip_Code_020B30C0:
    ldrb r6, [fp, #-1]
MobiClip_Code_020B30C4:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020B30C8:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B30CC:
    mov r7, r6
MobiClip_Code_020B30D0:
    stm fp, {r6, r7}
MobiClip_Code_020B30D4:
    add fp, fp, #0x100
MobiClip_Code_020B30D8:
    ldrb r6, [fp, #-1]
MobiClip_Code_020B30DC:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020B30E0:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B30E4:
    mov r7, r6
MobiClip_Code_020B30E8:
    stm fp, {r6, r7}
MobiClip_Code_020B30EC:
    add fp, fp, #0x100
MobiClip_Code_020B30F0:
    ldrb r6, [fp, #-1]
MobiClip_Code_020B30F4:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020B30F8:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B30FC:
    mov r7, r6
MobiClip_Code_020B3100:
    stm fp, {r6, r7}
MobiClip_Code_020B3104:
    add fp, fp, #0x100
MobiClip_Code_020B3108:
    ldrb r6, [fp, #-1]
MobiClip_Code_020B310C:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020B3110:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B3114:
    mov r7, r6
MobiClip_Code_020B3118:
    stm fp, {r6, r7}
MobiClip_Code_020B311C:
    add fp, fp, #0x100
MobiClip_Code_020B3120:
    ldrb r6, [fp, #-1]
MobiClip_Code_020B3124:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020B3128:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B312C:
    mov r7, r6
MobiClip_Code_020B3130:
    stm fp, {r6, r7}
MobiClip_Code_020B3134:
    add fp, fp, #0x100
MobiClip_Code_020B3138:
    ldrb r6, [fp, #-1]
MobiClip_Code_020B313C:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020B3140:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B3144:
    mov r7, r6
MobiClip_Code_020B3148:
    stm fp, {r6, r7}
MobiClip_Code_020B314C:
    add fp, fp, #0x100
MobiClip_Code_020B3150:
    ldrb r6, [fp, #-1]
MobiClip_Code_020B3154:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020B3158:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B315C:
    mov r7, r6
MobiClip_Code_020B3160:
    stm fp, {r6, r7}
MobiClip_Code_020B3164:
    add fp, fp, #0x100
MobiClip_Code_020B3168:
    ldrb r6, [fp, #-1]
MobiClip_Code_020B316C:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020B3170:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B3174:
    mov r7, r6
MobiClip_Code_020B3178:
    stm fp, {r6, r7}
MobiClip_Code_020B317C:
    add fp, fp, #0x100
MobiClip_Code_020B3180:
    sub fp, fp, #0x800
MobiClip_Code_020B3184:
    mov pc, lr
MobiClip_Code_020B3188:
    push {r4, sl, ip, lr}
MobiClip_Code_020B318C:
    bl MobiClip_Code_020B2C38
MobiClip_Code_020B3190:
    push {r0, r1, r2, r3}
MobiClip_Code_020B3194:
    sub lr, fp, #0x100
MobiClip_Code_020B3198:
    ldm lr, {r0, r1}
MobiClip_Code_020B319C:
    add lr, fp, #0x700
MobiClip_Code_020B31A0:
    ldrb r4, [lr, #-1]
MobiClip_Code_020B31A4:
    lsr sl, r1, #0x18
MobiClip_Code_020B31A8:
    add r5, r4, sl
MobiClip_Code_020B31AC:
    add r5, r5, #1
MobiClip_Code_020B31B0:
    asr r5, r5, #1
MobiClip_Code_020B31B4:
    add r5, r5, r6, lsl #1
MobiClip_Code_020B31B8:
    sub r6, r5, r4
MobiClip_Code_020B31BC:
    lsl r4, r4, #3
MobiClip_Code_020B31C0:
    sub sp, sp, #0x40
MobiClip_Code_020B31C4:
    mov lr, sp
MobiClip_Code_020B31C8:
    mov r2, #0xff
MobiClip_Code_020B31CC:
    add r4, r4, r6
MobiClip_Code_020B31D0:
    and r7, r2, r0
MobiClip_Code_020B31D4:
    sub r8, r4, r7, lsl #3
MobiClip_Code_020B31D8:
    lsl r7, r7, #6
MobiClip_Code_020B31DC:
    add r4, r4, r6
MobiClip_Code_020B31E0:
    and sb, r2, r0, lsr #8
MobiClip_Code_020B31E4:
    sub ip, r4, sb, lsl #3
MobiClip_Code_020B31E8:
    lsl sb, sb, #6
MobiClip_Code_020B31EC:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020B31F0:
    add r4, r4, r6
MobiClip_Code_020B31F4:
    and r7, r2, r0, lsr #16
MobiClip_Code_020B31F8:
    sub r8, r4, r7, lsl #3
MobiClip_Code_020B31FC:
    lsl r7, r7, #6
MobiClip_Code_020B3200:
    add r4, r4, r6
MobiClip_Code_020B3204:
    and sb, r2, r0, lsr #24
MobiClip_Code_020B3208:
    sub ip, r4, sb, lsl #3
MobiClip_Code_020B320C:
    lsl sb, sb, #6
MobiClip_Code_020B3210:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020B3214:
    add r4, r4, r6
MobiClip_Code_020B3218:
    and r7, r2, r1
MobiClip_Code_020B321C:
    sub r8, r4, r7, lsl #3
MobiClip_Code_020B3220:
    lsl r7, r7, #6
MobiClip_Code_020B3224:
    add r4, r4, r6
MobiClip_Code_020B3228:
    and sb, r2, r1, lsr #8
MobiClip_Code_020B322C:
    sub ip, r4, sb, lsl #3
MobiClip_Code_020B3230:
    lsl sb, sb, #6
MobiClip_Code_020B3234:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020B3238:
    add r4, r4, r6
MobiClip_Code_020B323C:
    and r7, r2, r1, lsr #16
MobiClip_Code_020B3240:
    sub r8, r4, r7, lsl #3
MobiClip_Code_020B3244:
    lsl r7, r7, #6
MobiClip_Code_020B3248:
    add r4, r4, r6
MobiClip_Code_020B324C:
    and sb, r2, r1, lsr #24
MobiClip_Code_020B3250:
    sub ip, r4, sb, lsl #3
MobiClip_Code_020B3254:
    lsl sb, sb, #6
MobiClip_Code_020B3258:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020B325C:
    sub sb, r5, sl
MobiClip_Code_020B3260:
    lsl sl, sl, #3
MobiClip_Code_020B3264:
    mov lr, #8
MobiClip_Code_020B3268:
    add sl, sl, sb
MobiClip_Code_020B326C:
    ldrb r8, [fp, #-1]
MobiClip_Code_020B3270:
    sub r7, sl, r8, lsl #3
MobiClip_Code_020B3274:
    lsl r8, r8, #6
MobiClip_Code_020B3278:
    add ip, sp, #0
MobiClip_Code_020B327C:
    ldm ip, {r0, r1, r2, r3, r4, r5, r6, ip}
MobiClip_Code_020B3280:
    add r0, r0, r1
MobiClip_Code_020B3284:
    add r2, r2, r3
MobiClip_Code_020B3288:
    add r4, r4, r5
MobiClip_Code_020B328C:
    add r6, r6, ip
MobiClip_Code_020B3290:
    str r0, [sp]
MobiClip_Code_020B3294:
    str r2, [sp, #8]
MobiClip_Code_020B3298:
    str r4, [sp, #0x10]
MobiClip_Code_020B329C:
    str r6, [sp, #0x18]
MobiClip_Code_020B32A0:
    add r8, r8, r7
MobiClip_Code_020B32A4:
    add r5, r0, r8
MobiClip_Code_020B32A8:
    add r5, r5, #0x40
MobiClip_Code_020B32AC:
    asr r5, r5, #7
MobiClip_Code_020B32B0:
    add r8, r8, r7
MobiClip_Code_020B32B4:
    add ip, r2, r8
MobiClip_Code_020B32B8:
    add ip, ip, #0x40
MobiClip_Code_020B32BC:
    asr ip, ip, #7
MobiClip_Code_020B32C0:
    orr r5, r5, ip, lsl #8
MobiClip_Code_020B32C4:
    add r8, r8, r7
MobiClip_Code_020B32C8:
    add ip, r4, r8
MobiClip_Code_020B32CC:
    add ip, ip, #0x40
MobiClip_Code_020B32D0:
    asr ip, ip, #7
MobiClip_Code_020B32D4:
    orr r5, r5, ip, lsl #16
MobiClip_Code_020B32D8:
    add r8, r8, r7
MobiClip_Code_020B32DC:
    add ip, r6, r8
MobiClip_Code_020B32E0:
    add ip, ip, #0x40
MobiClip_Code_020B32E4:
    asr ip, ip, #7
MobiClip_Code_020B32E8:
    orr r5, r5, ip, lsl #24
MobiClip_Code_020B32EC:
    str r5, [fp], #4
MobiClip_Code_020B32F0:
    add ip, sp, #0x20
MobiClip_Code_020B32F4:
    ldm ip, {r0, r1, r2, r3, r4, r5, r6, ip}
MobiClip_Code_020B32F8:
    add r0, r0, r1
MobiClip_Code_020B32FC:
    add r2, r2, r3
MobiClip_Code_020B3300:
    add r4, r4, r5
MobiClip_Code_020B3304:
    add r6, r6, ip
MobiClip_Code_020B3308:
    str r0, [sp, #0x20]
MobiClip_Code_020B330C:
    str r2, [sp, #0x28]
MobiClip_Code_020B3310:
    str r4, [sp, #0x30]
MobiClip_Code_020B3314:
    str r6, [sp, #0x38]
MobiClip_Code_020B3318:
    add r8, r8, r7
MobiClip_Code_020B331C:
    add r5, r0, r8
MobiClip_Code_020B3320:
    add r5, r5, #0x40
MobiClip_Code_020B3324:
    asr r5, r5, #7
MobiClip_Code_020B3328:
    add r8, r8, r7
MobiClip_Code_020B332C:
    add ip, r2, r8
MobiClip_Code_020B3330:
    add ip, ip, #0x40
MobiClip_Code_020B3334:
    asr ip, ip, #7
MobiClip_Code_020B3338:
    orr r5, r5, ip, lsl #8
MobiClip_Code_020B333C:
    add r8, r8, r7
MobiClip_Code_020B3340:
    add ip, r4, r8
MobiClip_Code_020B3344:
    add ip, ip, #0x40
MobiClip_Code_020B3348:
    asr ip, ip, #7
MobiClip_Code_020B334C:
    orr r5, r5, ip, lsl #16
MobiClip_Code_020B3350:
    add r8, r8, r7
MobiClip_Code_020B3354:
    add ip, r6, r8
MobiClip_Code_020B3358:
    add ip, ip, #0x40
MobiClip_Code_020B335C:
    asr ip, ip, #7
MobiClip_Code_020B3360:
    orr r5, r5, ip, lsl #24
MobiClip_Code_020B3364:
    str r5, [fp], #0xfc
MobiClip_Code_020B3368:
    subs lr, lr, #1
MobiClip_Code_020B336C:
    bne MobiClip_Code_020B3268
MobiClip_Code_020B3370:
    add sp, sp, #0x40
MobiClip_Code_020B3374:
    sub fp, fp, #0x800
MobiClip_Code_020B3378:
    pop {r0, r1, r2, r3, r4, sl, ip, pc}
MobiClip_Code_020B337C:
    mov r6, #0
MobiClip_Code_020B3380:
    sub r7, fp, #0x100
MobiClip_Code_020B3384:
    ldm r7, {r4, r5}
MobiClip_Code_020B3388:
    add r6, r6, r4, lsr #24
MobiClip_Code_020B338C:
    lsl r4, r4, #8
MobiClip_Code_020B3390:
    add r6, r6, r4, lsr #24
MobiClip_Code_020B3394:
    lsl r4, r4, #8
MobiClip_Code_020B3398:
    add r6, r6, r4, lsr #24
MobiClip_Code_020B339C:
    lsl r4, r4, #8
MobiClip_Code_020B33A0:
    add r6, r6, r4, lsr #24
MobiClip_Code_020B33A4:
    add r6, r6, r5, lsr #24
MobiClip_Code_020B33A8:
    lsl r5, r5, #8
MobiClip_Code_020B33AC:
    add r6, r6, r5, lsr #24
MobiClip_Code_020B33B0:
    lsl r5, r5, #8
MobiClip_Code_020B33B4:
    add r6, r6, r5, lsr #24
MobiClip_Code_020B33B8:
    lsl r5, r5, #8
MobiClip_Code_020B33BC:
    add r6, r6, r5, lsr #24
MobiClip_Code_020B33C0:
    sub fp, fp, #1
MobiClip_Code_020B33C4:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B33C8:
    add r6, r6, r4
MobiClip_Code_020B33CC:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B33D0:
    add r6, r6, r4
MobiClip_Code_020B33D4:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B33D8:
    add r6, r6, r4
MobiClip_Code_020B33DC:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B33E0:
    add r6, r6, r4
MobiClip_Code_020B33E4:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B33E8:
    add r6, r6, r4
MobiClip_Code_020B33EC:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B33F0:
    add r6, r6, r4
MobiClip_Code_020B33F4:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B33F8:
    add r6, r6, r4
MobiClip_Code_020B33FC:
    ldrb r4, [fp], #1
MobiClip_Code_020B3400:
    add r6, r6, r4
MobiClip_Code_020B3404:
    add r6, r6, #8
MobiClip_Code_020B3408:
    asr r6, r6, #4
MobiClip_Code_020B340C:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020B3410:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B3414:
    mov r7, r6
MobiClip_Code_020B3418:
    sub fp, fp, #0x700
MobiClip_Code_020B341C:
    stm fp, {r6, r7}
MobiClip_Code_020B3420:
    add fp, fp, #0x100
MobiClip_Code_020B3424:
    stm fp, {r6, r7}
MobiClip_Code_020B3428:
    add fp, fp, #0x100
MobiClip_Code_020B342C:
    stm fp, {r6, r7}
MobiClip_Code_020B3430:
    add fp, fp, #0x100
MobiClip_Code_020B3434:
    stm fp, {r6, r7}
MobiClip_Code_020B3438:
    add fp, fp, #0x100
MobiClip_Code_020B343C:
    stm fp, {r6, r7}
MobiClip_Code_020B3440:
    add fp, fp, #0x100
MobiClip_Code_020B3444:
    stm fp, {r6, r7}
MobiClip_Code_020B3448:
    add fp, fp, #0x100
MobiClip_Code_020B344C:
    stm fp, {r6, r7}
MobiClip_Code_020B3450:
    add fp, fp, #0x100
MobiClip_Code_020B3454:
    stm fp, {r6, r7}
MobiClip_Code_020B3458:
    sub fp, fp, #0x700
MobiClip_Code_020B345C:
    mov pc, lr
MobiClip_Code_020B3460:
    mov r6, #0
MobiClip_Code_020B3464:
    sub fp, fp, #1
MobiClip_Code_020B3468:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B346C:
    add r6, r6, r4
MobiClip_Code_020B3470:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B3474:
    add r6, r6, r4
MobiClip_Code_020B3478:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B347C:
    add r6, r6, r4
MobiClip_Code_020B3480:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B3484:
    add r6, r6, r4
MobiClip_Code_020B3488:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B348C:
    add r6, r6, r4
MobiClip_Code_020B3490:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B3494:
    add r6, r6, r4
MobiClip_Code_020B3498:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B349C:
    add r6, r6, r4
MobiClip_Code_020B34A0:
    ldrb r4, [fp], #1
MobiClip_Code_020B34A4:
    add r6, r6, r4
MobiClip_Code_020B34A8:
    add r6, r6, #4
MobiClip_Code_020B34AC:
    asr r6, r6, #3
MobiClip_Code_020B34B0:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020B34B4:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B34B8:
    mov r7, r6
MobiClip_Code_020B34BC:
    sub fp, fp, #0x700
MobiClip_Code_020B34C0:
    stm fp, {r6, r7}
MobiClip_Code_020B34C4:
    add fp, fp, #0x100
MobiClip_Code_020B34C8:
    stm fp, {r6, r7}
MobiClip_Code_020B34CC:
    add fp, fp, #0x100
MobiClip_Code_020B34D0:
    stm fp, {r6, r7}
MobiClip_Code_020B34D4:
    add fp, fp, #0x100
MobiClip_Code_020B34D8:
    stm fp, {r6, r7}
MobiClip_Code_020B34DC:
    add fp, fp, #0x100
MobiClip_Code_020B34E0:
    stm fp, {r6, r7}
MobiClip_Code_020B34E4:
    add fp, fp, #0x100
MobiClip_Code_020B34E8:
    stm fp, {r6, r7}
MobiClip_Code_020B34EC:
    add fp, fp, #0x100
MobiClip_Code_020B34F0:
    stm fp, {r6, r7}
MobiClip_Code_020B34F4:
    add fp, fp, #0x100
MobiClip_Code_020B34F8:
    stm fp, {r6, r7}
MobiClip_Code_020B34FC:
    sub fp, fp, #0x700
MobiClip_Code_020B3500:
    mov pc, lr
MobiClip_Code_020B3504:
    mov r6, #0
MobiClip_Code_020B3508:
    sub r7, fp, #0x100
MobiClip_Code_020B350C:
    ldm r7, {r4, r5}
MobiClip_Code_020B3510:
    add r6, r6, r4, lsr #24
MobiClip_Code_020B3514:
    lsl r4, r4, #8
MobiClip_Code_020B3518:
    add r6, r6, r4, lsr #24
MobiClip_Code_020B351C:
    lsl r4, r4, #8
MobiClip_Code_020B3520:
    add r6, r6, r4, lsr #24
MobiClip_Code_020B3524:
    lsl r4, r4, #8
MobiClip_Code_020B3528:
    add r6, r6, r4, lsr #24
MobiClip_Code_020B352C:
    add r6, r6, r5, lsr #24
MobiClip_Code_020B3530:
    lsl r5, r5, #8
MobiClip_Code_020B3534:
    add r6, r6, r5, lsr #24
MobiClip_Code_020B3538:
    lsl r5, r5, #8
MobiClip_Code_020B353C:
    add r6, r6, r5, lsr #24
MobiClip_Code_020B3540:
    lsl r5, r5, #8
MobiClip_Code_020B3544:
    add r6, r6, r5, lsr #24
MobiClip_Code_020B3548:
    add r6, r6, #4
MobiClip_Code_020B354C:
    asr r6, r6, #3
MobiClip_Code_020B3550:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020B3554:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B3558:
    mov r7, r6
MobiClip_Code_020B355C:
    stm fp, {r6, r7}
MobiClip_Code_020B3560:
    add fp, fp, #0x100
MobiClip_Code_020B3564:
    stm fp, {r6, r7}
MobiClip_Code_020B3568:
    add fp, fp, #0x100
MobiClip_Code_020B356C:
    stm fp, {r6, r7}
MobiClip_Code_020B3570:
    add fp, fp, #0x100
MobiClip_Code_020B3574:
    stm fp, {r6, r7}
MobiClip_Code_020B3578:
    add fp, fp, #0x100
MobiClip_Code_020B357C:
    stm fp, {r6, r7}
MobiClip_Code_020B3580:
    add fp, fp, #0x100
MobiClip_Code_020B3584:
    stm fp, {r6, r7}
MobiClip_Code_020B3588:
    add fp, fp, #0x100
MobiClip_Code_020B358C:
    stm fp, {r6, r7}
MobiClip_Code_020B3590:
    add fp, fp, #0x100
MobiClip_Code_020B3594:
    stm fp, {r6, r7}
MobiClip_Code_020B3598:
    sub fp, fp, #0x700
MobiClip_Code_020B359C:
    mov pc, lr
MobiClip_Code_020B35A0:
    mov r6, #0x80
MobiClip_Code_020B35A4:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020B35A8:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B35AC:
    mov r7, r6
MobiClip_Code_020B35B0:
    stm fp, {r6, r7}
MobiClip_Code_020B35B4:
    add fp, fp, #0x100
MobiClip_Code_020B35B8:
    stm fp, {r6, r7}
MobiClip_Code_020B35BC:
    add fp, fp, #0x100
MobiClip_Code_020B35C0:
    stm fp, {r6, r7}
MobiClip_Code_020B35C4:
    add fp, fp, #0x100
MobiClip_Code_020B35C8:
    stm fp, {r6, r7}
MobiClip_Code_020B35CC:
    add fp, fp, #0x100
MobiClip_Code_020B35D0:
    stm fp, {r6, r7}
MobiClip_Code_020B35D4:
    add fp, fp, #0x100
MobiClip_Code_020B35D8:
    stm fp, {r6, r7}
MobiClip_Code_020B35DC:
    add fp, fp, #0x100
MobiClip_Code_020B35E0:
    stm fp, {r6, r7}
MobiClip_Code_020B35E4:
    add fp, fp, #0x100
MobiClip_Code_020B35E8:
    stm fp, {r6, r7}
MobiClip_Code_020B35EC:
    sub fp, fp, #0x700
MobiClip_Code_020B35F0:
    mov pc, lr
    /* control metadata 0x0208f2f8..0x0208f308 */
    .global gMobiClip_intra8_neighbor_dispatch
    .type gMobiClip_intra8_neighbor_dispatch, %object
gMobiClip_intra8_neighbor_dispatch:
    /* intra8_neighbor */
    .global gMobiClip_intra8_neighbor
gMobiClip_intra8_neighbor:
    .word MobiClip_Code_020B35A0 - .
    .word MobiClip_Code_020B3504 - . + 0x4
    .word MobiClip_Code_020B3460 - . + 0x8
    .word MobiClip_Code_020B337C - . + 0xc
MobiClip_Code_020B3604:
    sub r5, pc, #0x18
MobiClip_Code_020B3608:
    mov r8, #0
MobiClip_Code_020B360C:
    sub r6, fp, sl
MobiClip_Code_020B3610:
    lsls r7, r6, #0x18
MobiClip_Code_020B3614:
    addne r8, r8, #8
MobiClip_Code_020B3618:
    cmp r6, #0x100
MobiClip_Code_020B361C:
    addge r8, r8, #4
MobiClip_Code_020B3620:
    ldr r6, [r5, r8]
MobiClip_Code_020B3624:
    add pc, r5, r6
MobiClip_Code_020B3628:
    push {r3, ip, lr}
MobiClip_Code_020B362C:
    ldrb r3, [fp, #-1]!
MobiClip_Code_020B3630:
    ldrb ip, [fp, #0x100]!
MobiClip_Code_020B3634:
    ldrb sb, [fp, #0x100]!
MobiClip_Code_020B3638:
    ldrb r6, [fp, #0x100]!
MobiClip_Code_020B363C:
    add r8, r3, ip
MobiClip_Code_020B3640:
    add r3, sb, r3
MobiClip_Code_020B3644:
    add r3, r3, ip, lsl #1
MobiClip_Code_020B3648:
    add r3, r3, #2
MobiClip_Code_020B364C:
    asr lr, r3, #2
MobiClip_Code_020B3650:
    add r3, ip, sb
MobiClip_Code_020B3654:
    add ip, r6, ip
MobiClip_Code_020B3658:
    add r8, r8, #1
MobiClip_Code_020B365C:
    asr r8, r8, #1
MobiClip_Code_020B3660:
    add ip, ip, sb, lsl #1
MobiClip_Code_020B3664:
    add r3, r3, #1
MobiClip_Code_020B3668:
    asr r3, r3, #1
MobiClip_Code_020B366C:
    add ip, ip, #2
MobiClip_Code_020B3670:
    orr r8, r8, lr, lsl #8
MobiClip_Code_020B3674:
    orr r8, r8, r3, lsl #16
MobiClip_Code_020B3678:
    asr ip, ip, #2
MobiClip_Code_020B367C:
    orr r8, r8, ip, lsl #24
MobiClip_Code_020B3680:
    sub lr, fp, #0x300
MobiClip_Code_020B3684:
    str r8, [lr, #1]
MobiClip_Code_020B3688:
    add r8, sb, r6
MobiClip_Code_020B368C:
    add r8, r8, #1
MobiClip_Code_020B3690:
    asr lr, r8, #1
MobiClip_Code_020B3694:
    ldrb r8, [fp, #0x100]!
MobiClip_Code_020B3698:
    orr r3, r3, ip, lsl #8
MobiClip_Code_020B369C:
    orr r3, r3, lr, lsl #16
MobiClip_Code_020B36A0:
    add sb, r8, sb
MobiClip_Code_020B36A4:
    add sb, sb, r6, lsl #1
MobiClip_Code_020B36A8:
    add sb, sb, #2
MobiClip_Code_020B36AC:
    asr r4, sb, #2
MobiClip_Code_020B36B0:
    add sb, r6, r8
MobiClip_Code_020B36B4:
    add sb, sb, #1
MobiClip_Code_020B36B8:
    asr r5, sb, #1
MobiClip_Code_020B36BC:
    ldrb sb, [fp, #0x100]!
MobiClip_Code_020B36C0:
    orr r3, r3, r4, lsl #24
MobiClip_Code_020B36C4:
    sub r7, fp, #0x400
MobiClip_Code_020B36C8:
    str r3, [r7, #1]
MobiClip_Code_020B36CC:
    add r6, sb, r6
MobiClip_Code_020B36D0:
    add r6, r6, r8, lsl #1
MobiClip_Code_020B36D4:
    add r6, r6, #2
MobiClip_Code_020B36D8:
    orr r7, lr, r4, lsl #8
MobiClip_Code_020B36DC:
    asr r6, r6, #2
MobiClip_Code_020B36E0:
    orr r7, r7, r5, lsl #16
MobiClip_Code_020B36E4:
    add r3, r8, sb
MobiClip_Code_020B36E8:
    add r3, r3, #1
MobiClip_Code_020B36EC:
    orr r7, r7, r6, lsl #24
MobiClip_Code_020B36F0:
    sub ip, fp, #0x500
MobiClip_Code_020B36F4:
    str r7, [ip, #5]
MobiClip_Code_020B36F8:
    asr ip, r3, #1
MobiClip_Code_020B36FC:
    ldrb r3, [fp, #0x100]!
MobiClip_Code_020B3700:
    orr lr, r5, r6, lsl #8
MobiClip_Code_020B3704:
    orr lr, lr, ip, lsl #16
MobiClip_Code_020B3708:
    add r8, r3, r8
MobiClip_Code_020B370C:
    add r8, r8, sb, lsl #1
MobiClip_Code_020B3710:
    add r8, r8, #2
MobiClip_Code_020B3714:
    asr r8, r8, #2
MobiClip_Code_020B3718:
    add r4, sb, r3
MobiClip_Code_020B371C:
    add r4, r4, #1
MobiClip_Code_020B3720:
    orr lr, lr, r8, lsl #24
MobiClip_Code_020B3724:
    sub r5, fp, #0x400
MobiClip_Code_020B3728:
    str r7, [r5, #1]
MobiClip_Code_020B372C:
    str lr, [r5, #-0xfb]
MobiClip_Code_020B3730:
    asr r5, r4, #1
MobiClip_Code_020B3734:
    ldrb r4, [fp, #0x100]
MobiClip_Code_020B3738:
    orr r8, ip, r8, lsl #8
MobiClip_Code_020B373C:
    orr r8, r8, r5, lsl #16
MobiClip_Code_020B3740:
    add sb, r4, sb
MobiClip_Code_020B3744:
    add sb, sb, r3, lsl #1
MobiClip_Code_020B3748:
    add ip, r3, r4
MobiClip_Code_020B374C:
    add sb, sb, #2
MobiClip_Code_020B3750:
    asr sb, sb, #2
MobiClip_Code_020B3754:
    orr r8, r8, sb, lsl #24
MobiClip_Code_020B3758:
    add r3, r4, r3
MobiClip_Code_020B375C:
    add r3, r3, r4, lsl #1
MobiClip_Code_020B3760:
    add ip, ip, #1
MobiClip_Code_020B3764:
    asr ip, ip, #1
MobiClip_Code_020B3768:
    add r3, r3, #2
MobiClip_Code_020B376C:
    orr sb, r5, sb, lsl #8
MobiClip_Code_020B3770:
    orr sb, sb, ip, lsl #16
MobiClip_Code_020B3774:
    asr r3, r3, #2
MobiClip_Code_020B3778:
    orr sb, sb, r3, lsl #24
MobiClip_Code_020B377C:
    sub r7, fp, #0x200
MobiClip_Code_020B3780:
    str r8, [r7, #-0x1fb]
MobiClip_Code_020B3784:
    str sb, [r7, #-0xfb]
MobiClip_Code_020B3788:
    str lr, [r7, #-0xff]
MobiClip_Code_020B378C:
    str r8, [r7, #1]
MobiClip_Code_020B3790:
    orr r8, ip, r3, lsl #8
MobiClip_Code_020B3794:
    str sb, [fp, #-0xff]
MobiClip_Code_020B3798:
    orr sb, r4, r4, lsl #8
MobiClip_Code_020B379C:
    orr r8, r8, r4, lsl #16
MobiClip_Code_020B37A0:
    orr r8, r8, r4, lsl #24
MobiClip_Code_020B37A4:
    orr sb, sb, r4, lsl #16
MobiClip_Code_020B37A8:
    orr sb, sb, r4, lsl #24
MobiClip_Code_020B37AC:
    str r8, [fp, #-0x1fb]
MobiClip_Code_020B37B0:
    str sb, [fp, #-0xfb]
MobiClip_Code_020B37B4:
    add fp, fp, #1
MobiClip_Code_020B37B8:
    stm fp, {r8, sb}
MobiClip_Code_020B37BC:
    str sb, [fp, #0x100]
MobiClip_Code_020B37C0:
    str sb, [fp, #0x104]
MobiClip_Code_020B37C4:
    sub fp, fp, #0x600
MobiClip_Code_020B37C8:
    pop {r3, ip, pc}
MobiClip_Code_020B37CC:
    push {r0, r1, r2, r3, sl, ip, lr}
MobiClip_Code_020B37D0:
    sub r0, fp, #0x100
MobiClip_Code_020B37D4:
    ldm r0, {r3, ip}
MobiClip_Code_020B37D8:
    add r0, r0, #0x100
MobiClip_Code_020B37DC:
    ldrb r1, [r0, #-1]
MobiClip_Code_020B37E0:
    ldrb r2, [r0, #-0x101]
MobiClip_Code_020B37E4:
    add r4, r1, r2
MobiClip_Code_020B37E8:
    add r4, r4, #1
MobiClip_Code_020B37EC:
    asr lr, r4, #1
MobiClip_Code_020B37F0:
    and r7, r3, #0xff
MobiClip_Code_020B37F4:
    add r4, r7, r1
MobiClip_Code_020B37F8:
    add r4, r4, r2, lsl #1
MobiClip_Code_020B37FC:
    add r4, r4, #2
MobiClip_Code_020B3800:
    asr r5, r4, #2
MobiClip_Code_020B3804:
    lsl r4, r3, #0x10
MobiClip_Code_020B3808:
    lsr r4, r4, #0x18
MobiClip_Code_020B380C:
    add r6, r2, r4
MobiClip_Code_020B3810:
    lsl r8, r3, #8
MobiClip_Code_020B3814:
    add r6, r6, r7, lsl #1
MobiClip_Code_020B3818:
    lsr sb, r8, #0x18
MobiClip_Code_020B381C:
    add r7, r7, sb
MobiClip_Code_020B3820:
    add r7, r7, r4, lsl #1
MobiClip_Code_020B3824:
    add r6, r6, #2
MobiClip_Code_020B3828:
    lsr r3, r3, #0x18
MobiClip_Code_020B382C:
    add r4, r4, r3
MobiClip_Code_020B3830:
    asr r6, r6, #2
MobiClip_Code_020B3834:
    add r7, r7, #2
MobiClip_Code_020B3838:
    orr r8, lr, r5, lsl #8
MobiClip_Code_020B383C:
    orr r8, r8, r6, lsl #16
MobiClip_Code_020B3840:
    asr r7, r7, #2
MobiClip_Code_020B3844:
    add r4, r4, sb, lsl #1
MobiClip_Code_020B3848:
    add r4, r4, #2
MobiClip_Code_020B384C:
    orr fp, r8, r7, lsl #24
MobiClip_Code_020B3850:
    asr r8, r4, #2
MobiClip_Code_020B3854:
    and r4, ip, #0xff
MobiClip_Code_020B3858:
    lsl sl, ip, #0x10
MobiClip_Code_020B385C:
    lsr sl, sl, #0x18
MobiClip_Code_020B3860:
    add sb, sb, r4
MobiClip_Code_020B3864:
    add sb, sb, r3, lsl #1
MobiClip_Code_020B3868:
    lsl ip, ip, #8
MobiClip_Code_020B386C:
    add ip, r4, ip, lsr #24
MobiClip_Code_020B3870:
    add r3, r3, sl
MobiClip_Code_020B3874:
    add r3, r3, r4, lsl #1
MobiClip_Code_020B3878:
    add sb, sb, #2
MobiClip_Code_020B387C:
    asr sb, sb, #2
MobiClip_Code_020B3880:
    add r3, r3, #2
MobiClip_Code_020B3884:
    add ip, ip, sl, lsl #1
MobiClip_Code_020B3888:
    add ip, ip, #2
MobiClip_Code_020B388C:
    asr r3, r3, #2
MobiClip_Code_020B3890:
    orr r4, r8, sb, lsl #8
MobiClip_Code_020B3894:
    orr r3, r4, r3, lsl #16
MobiClip_Code_020B3898:
    asr ip, ip, #2
MobiClip_Code_020B389C:
    orr ip, r3, ip, lsl #24
MobiClip_Code_020B38A0:
    stm r0, {fp, ip}
MobiClip_Code_020B38A4:
    ldrb ip, [r0, #0xff]
MobiClip_Code_020B38A8:
    add r2, r2, ip
MobiClip_Code_020B38AC:
    add r2, r2, r1, lsl #1
MobiClip_Code_020B38B0:
    add r3, ip, r1
MobiClip_Code_020B38B4:
    add r3, r3, #1
MobiClip_Code_020B38B8:
    add r2, r2, #2
MobiClip_Code_020B38BC:
    asr r2, r2, #2
MobiClip_Code_020B38C0:
    asr r3, r3, #1
MobiClip_Code_020B38C4:
    orr r4, r3, r2, lsl #8
MobiClip_Code_020B38C8:
    orr r4, r4, lr, lsl #16
MobiClip_Code_020B38CC:
    orr lr, r6, r7, lsl #8
MobiClip_Code_020B38D0:
    orr lr, lr, r8, lsl #16
MobiClip_Code_020B38D4:
    orr lr, lr, sb, lsl #24
MobiClip_Code_020B38D8:
    orr r4, r4, r5, lsl #24
MobiClip_Code_020B38DC:
    add r0, r0, #0x100
MobiClip_Code_020B38E0:
    stm r0, {r4, lr}
MobiClip_Code_020B38E4:
    ldrb lr, [r0, #0xff]
MobiClip_Code_020B38E8:
    add r1, r1, lr
MobiClip_Code_020B38EC:
    add r1, r1, ip, lsl #1
MobiClip_Code_020B38F0:
    add r5, lr, ip
MobiClip_Code_020B38F4:
    add r5, r5, #1
MobiClip_Code_020B38F8:
    add r1, r1, #2
MobiClip_Code_020B38FC:
    asr r1, r1, #2
MobiClip_Code_020B3900:
    asr r5, r5, #1
MobiClip_Code_020B3904:
    orr r6, r5, r1, lsl #8
MobiClip_Code_020B3908:
    orr r3, r6, r3, lsl #16
MobiClip_Code_020B390C:
    orr r2, r3, r2, lsl #24
MobiClip_Code_020B3910:
    add r6, r0, #0x100
MobiClip_Code_020B3914:
    stm r6, {r2, fp}
MobiClip_Code_020B3918:
    ldrb r3, [r0, #0x1ff]
MobiClip_Code_020B391C:
    add ip, ip, r3
MobiClip_Code_020B3920:
    add ip, ip, lr, lsl #1
MobiClip_Code_020B3924:
    add r6, r3, lr
MobiClip_Code_020B3928:
    add r6, r6, #1
MobiClip_Code_020B392C:
    add ip, ip, #2
MobiClip_Code_020B3930:
    asr ip, ip, #2
MobiClip_Code_020B3934:
    asr r6, r6, #1
MobiClip_Code_020B3938:
    orr r7, r6, ip, lsl #8
MobiClip_Code_020B393C:
    orr r5, r7, r5, lsl #16
MobiClip_Code_020B3940:
    orr r1, r5, r1, lsl #24
MobiClip_Code_020B3944:
    add r0, r0, #0x200
MobiClip_Code_020B3948:
    stm r0, {r1, r4}
MobiClip_Code_020B394C:
    ldrb r4, [r0, #0xff]
MobiClip_Code_020B3950:
    str r2, [r0, #0x104]
MobiClip_Code_020B3954:
    add lr, lr, r4
MobiClip_Code_020B3958:
    add lr, lr, r3, lsl #1
MobiClip_Code_020B395C:
    add r5, r4, r3
MobiClip_Code_020B3960:
    add r5, r5, #1
MobiClip_Code_020B3964:
    add lr, lr, #2
MobiClip_Code_020B3968:
    asr lr, lr, #2
MobiClip_Code_020B396C:
    asr r5, r5, #1
MobiClip_Code_020B3970:
    orr r7, r5, lr, lsl #8
MobiClip_Code_020B3974:
    orr r6, r7, r6, lsl #16
MobiClip_Code_020B3978:
    orr ip, r6, ip, lsl #24
MobiClip_Code_020B397C:
    str ip, [r0, #0x100]!
MobiClip_Code_020B3980:
    ldrb r2, [r0, #0xff]
MobiClip_Code_020B3984:
    str r1, [r0, #0x104]
MobiClip_Code_020B3988:
    add r3, r3, r2
MobiClip_Code_020B398C:
    add r3, r3, r4, lsl #1
MobiClip_Code_020B3990:
    add r6, r2, r4
MobiClip_Code_020B3994:
    add r6, r6, #1
MobiClip_Code_020B3998:
    add r3, r3, #2
MobiClip_Code_020B399C:
    asr r3, r3, #2
MobiClip_Code_020B39A0:
    asr r6, r6, #1
MobiClip_Code_020B39A4:
    orr r7, r6, r3, lsl #8
MobiClip_Code_020B39A8:
    orr r5, r7, r5, lsl #16
MobiClip_Code_020B39AC:
    orr lr, r5, lr, lsl #24
MobiClip_Code_020B39B0:
    str lr, [r0, #0x100]!
MobiClip_Code_020B39B4:
    ldrb r1, [r0, #0xff]
MobiClip_Code_020B39B8:
    str ip, [r0, #0x104]
MobiClip_Code_020B39BC:
    add r4, r4, r1
MobiClip_Code_020B39C0:
    add r4, r4, r2, lsl #1
MobiClip_Code_020B39C4:
    add r5, r1, r2
MobiClip_Code_020B39C8:
    add r5, r5, #1
MobiClip_Code_020B39CC:
    add r4, r4, #2
MobiClip_Code_020B39D0:
    asr r4, r4, #2
MobiClip_Code_020B39D4:
    asr r5, r5, #1
MobiClip_Code_020B39D8:
    orr r7, r5, r4, lsl #8
MobiClip_Code_020B39DC:
    orr r6, r7, r6, lsl #16
MobiClip_Code_020B39E0:
    orr r3, r6, r3, lsl #24
MobiClip_Code_020B39E4:
    str r3, [r0, #0x100]
MobiClip_Code_020B39E8:
    ldrb ip, [r0, #0x1ff]
MobiClip_Code_020B39EC:
    add r3, ip, r1
MobiClip_Code_020B39F0:
    add r2, r2, ip
MobiClip_Code_020B39F4:
    add r1, r2, r1, lsl #1
MobiClip_Code_020B39F8:
    add r1, r1, #2
MobiClip_Code_020B39FC:
    add r3, r3, #1
MobiClip_Code_020B3A00:
    asr r3, r3, #1
MobiClip_Code_020B3A04:
    asr r1, r1, #2
MobiClip_Code_020B3A08:
    orr r1, r3, r1, lsl #8
MobiClip_Code_020B3A0C:
    orr r1, r1, r5, lsl #16
MobiClip_Code_020B3A10:
    orr r1, r1, r4, lsl #24
MobiClip_Code_020B3A14:
    add r2, r0, #0x200
MobiClip_Code_020B3A18:
    stm r2, {r1, lr}
MobiClip_Code_020B3A1C:
    sub fp, r0, #0x500
MobiClip_Code_020B3A20:
    pop {r0, r1, r2, r3, sl, ip, pc}
MobiClip_Code_020B3A24:
    push {r0, r1, r2, r3, sl, ip, lr}
MobiClip_Code_020B3A28:
    sub r0, fp, #0x100
MobiClip_Code_020B3A2C:
    ldm r0, {r2, r7}
MobiClip_Code_020B3A30:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B3A34:
    and sb, r2, #0xff
MobiClip_Code_020B3A38:
    sub sp, sp, #0x34
MobiClip_Code_020B3A3C:
    add r1, r3, sb
MobiClip_Code_020B3A40:
    add r1, r1, #1
MobiClip_Code_020B3A44:
    str r3, [sp, #0x30]
MobiClip_Code_020B3A48:
    asr r3, r1, #1
MobiClip_Code_020B3A4C:
    lsl r1, r2, #0x10
MobiClip_Code_020B3A50:
    lsr sl, r1, #0x18
MobiClip_Code_020B3A54:
    add r1, sb, sl
MobiClip_Code_020B3A58:
    add r1, r1, #1
MobiClip_Code_020B3A5C:
    str r3, [sp, #0x2c]
MobiClip_Code_020B3A60:
    asr r3, r1, #1
MobiClip_Code_020B3A64:
    lsl r1, r2, #8
MobiClip_Code_020B3A68:
    str r3, [sp, #0x28]
MobiClip_Code_020B3A6C:
    lsr r1, r1, #0x18
MobiClip_Code_020B3A70:
    add r3, sl, r1
MobiClip_Code_020B3A74:
    add r3, r3, #1
MobiClip_Code_020B3A78:
    asr lr, r3, #1
MobiClip_Code_020B3A7C:
    lsr r2, r2, #0x18
MobiClip_Code_020B3A80:
    add r3, r1, r2
MobiClip_Code_020B3A84:
    add r3, r3, #1
MobiClip_Code_020B3A88:
    asr r4, r3, #1
MobiClip_Code_020B3A8C:
    ldr r3, [sp, #0x2c]
MobiClip_Code_020B3A90:
    ldr fp, [sp, #0x28]
MobiClip_Code_020B3A94:
    orr r3, r3, fp, lsl #8
MobiClip_Code_020B3A98:
    orr r3, r3, lr, lsl #16
MobiClip_Code_020B3A9C:
    orr r3, r3, r4, lsl #24
MobiClip_Code_020B3AA0:
    str r3, [r0, #0x100]!
MobiClip_Code_020B3AA4:
    and r3, r7, #0xff
MobiClip_Code_020B3AA8:
    add ip, r2, r3
MobiClip_Code_020B3AAC:
    add ip, ip, #1
MobiClip_Code_020B3AB0:
    asr r5, ip, #1
MobiClip_Code_020B3AB4:
    lsl ip, r7, #0x10
MobiClip_Code_020B3AB8:
    lsr ip, ip, #0x18
MobiClip_Code_020B3ABC:
    add r6, r3, ip
MobiClip_Code_020B3AC0:
    add r6, r6, #1
MobiClip_Code_020B3AC4:
    asr r8, r6, #1
MobiClip_Code_020B3AC8:
    lsl r6, r7, #8
MobiClip_Code_020B3ACC:
    lsr r6, r6, #0x18
MobiClip_Code_020B3AD0:
    str r8, [sp, #0x24]
MobiClip_Code_020B3AD4:
    add r8, ip, r6
MobiClip_Code_020B3AD8:
    add r8, r8, #1
MobiClip_Code_020B3ADC:
    asr fp, r8, #1
MobiClip_Code_020B3AE0:
    add r8, sp, #0x1c
MobiClip_Code_020B3AE4:
    lsr r7, r7, #0x18
MobiClip_Code_020B3AE8:
    stm r8, {r7, fp}
MobiClip_Code_020B3AEC:
    ldr r8, [sp, #0x24]
MobiClip_Code_020B3AF0:
    add r7, r6, r7
MobiClip_Code_020B3AF4:
    add r7, r7, #1
MobiClip_Code_020B3AF8:
    orr r8, r5, r8, lsl #8
MobiClip_Code_020B3AFC:
    orr r8, r8, fp, lsl #16
MobiClip_Code_020B3B00:
    asr r7, r7, #1
MobiClip_Code_020B3B04:
    orr r7, r8, r7, lsl #24
MobiClip_Code_020B3B08:
    str r7, [r0, #4]
MobiClip_Code_020B3B0C:
    ldrb r7, [r0, #-1]
MobiClip_Code_020B3B10:
    ldr r8, [sp, #0x30]
MobiClip_Code_020B3B14:
    str r7, [sp, #0x18]
MobiClip_Code_020B3B18:
    add r7, r7, sb
MobiClip_Code_020B3B1C:
    add r7, r7, r8, lsl #1
MobiClip_Code_020B3B20:
    add r8, r8, sl
MobiClip_Code_020B3B24:
    add r8, r8, sb, lsl #1
MobiClip_Code_020B3B28:
    add sb, sb, r1
MobiClip_Code_020B3B2C:
    add sb, sb, sl, lsl #1
MobiClip_Code_020B3B30:
    add sl, sl, r2
MobiClip_Code_020B3B34:
    add sl, sl, r1, lsl #1
MobiClip_Code_020B3B38:
    add r1, r1, r3
MobiClip_Code_020B3B3C:
    add r8, r8, #2
MobiClip_Code_020B3B40:
    add r7, r7, #2
MobiClip_Code_020B3B44:
    asr r7, r7, #2
MobiClip_Code_020B3B48:
    asr r8, r8, #2
MobiClip_Code_020B3B4C:
    add r1, r1, r2, lsl #1
MobiClip_Code_020B3B50:
    add sb, sb, #2
MobiClip_Code_020B3B54:
    asr sb, sb, #2
MobiClip_Code_020B3B58:
    add r2, r2, ip
MobiClip_Code_020B3B5C:
    orr fp, r7, r8, lsl #8
MobiClip_Code_020B3B60:
    add sl, sl, #2
MobiClip_Code_020B3B64:
    asr sl, sl, #2
MobiClip_Code_020B3B68:
    orr fp, fp, sb, lsl #16
MobiClip_Code_020B3B6C:
    add r2, r2, r3, lsl #1
MobiClip_Code_020B3B70:
    add r2, r2, #2
MobiClip_Code_020B3B74:
    orr fp, fp, sl, lsl #24
MobiClip_Code_020B3B78:
    str fp, [r0, #0x100]!
MobiClip_Code_020B3B7C:
    asr r2, r2, #2
MobiClip_Code_020B3B80:
    str r2, [sp, #0x14]
MobiClip_Code_020B3B84:
    add r2, r3, r6
MobiClip_Code_020B3B88:
    add r2, r2, ip, lsl #1
MobiClip_Code_020B3B8C:
    add r2, r2, #2
MobiClip_Code_020B3B90:
    asr r2, r2, #2
MobiClip_Code_020B3B94:
    str r2, [sp, #0x10]
MobiClip_Code_020B3B98:
    ldr r2, [sp, #0x1c]
MobiClip_Code_020B3B9C:
    add r1, r1, #2
MobiClip_Code_020B3BA0:
    add r2, ip, r2
MobiClip_Code_020B3BA4:
    add r2, r2, r6, lsl #1
MobiClip_Code_020B3BA8:
    add r2, r2, #2
MobiClip_Code_020B3BAC:
    asr r3, r2, #2
MobiClip_Code_020B3BB0:
    ldr r2, [sp, #0x14]
MobiClip_Code_020B3BB4:
    asr r1, r1, #2
MobiClip_Code_020B3BB8:
    orr ip, r1, r2, lsl #8
MobiClip_Code_020B3BBC:
    ldr r2, [sp, #0x10]
MobiClip_Code_020B3BC0:
    orr r6, sl, r1, lsl #8
MobiClip_Code_020B3BC4:
    orr r2, ip, r2, lsl #16
MobiClip_Code_020B3BC8:
    orr r2, r2, r3, lsl #24
MobiClip_Code_020B3BCC:
    str r2, [r0, #4]
MobiClip_Code_020B3BD0:
    ldrb r2, [r0, #-1]
MobiClip_Code_020B3BD4:
    ldr r3, [sp, #0x30]
MobiClip_Code_020B3BD8:
    str r2, [sp, #0xc]
MobiClip_Code_020B3BDC:
    add r2, r2, r3
MobiClip_Code_020B3BE0:
    ldr r3, [sp, #0x18]
MobiClip_Code_020B3BE4:
    add r2, r2, r3, lsl #1
MobiClip_Code_020B3BE8:
    add r2, r2, #2
MobiClip_Code_020B3BEC:
    asr r2, r2, #2
MobiClip_Code_020B3BF0:
    ldr r3, [sp, #0x2c]
MobiClip_Code_020B3BF4:
    str r2, [sp, #8]
MobiClip_Code_020B3BF8:
    orr r2, r2, r3, lsl #8
MobiClip_Code_020B3BFC:
    ldr r3, [sp, #0x28]
MobiClip_Code_020B3C00:
    orr r2, r2, r3, lsl #16
MobiClip_Code_020B3C04:
    orr r2, r2, lr, lsl #24
MobiClip_Code_020B3C08:
    str r2, [r0, #0x100]!
MobiClip_Code_020B3C0C:
    ldr r3, [sp, #0x24]
MobiClip_Code_020B3C10:
    orr r2, r4, r5, lsl #8
MobiClip_Code_020B3C14:
    ldr fp, [sp, #0x20]
MobiClip_Code_020B3C18:
    orr r2, r2, r3, lsl #16
MobiClip_Code_020B3C1C:
    orr r2, r2, fp, lsl #24
MobiClip_Code_020B3C20:
    str r2, [r0, #4]
MobiClip_Code_020B3C24:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B3C28:
    ldr r2, [sp, #0x18]
MobiClip_Code_020B3C2C:
    add ip, r3, r2
MobiClip_Code_020B3C30:
    ldr r2, [sp, #0xc]
MobiClip_Code_020B3C34:
    add r2, ip, r2, lsl #1
MobiClip_Code_020B3C38:
    add r2, r2, #2
MobiClip_Code_020B3C3C:
    asr ip, r2, #2
MobiClip_Code_020B3C40:
    orr r2, ip, r7, lsl #8
MobiClip_Code_020B3C44:
    orr r2, r2, r8, lsl #16
MobiClip_Code_020B3C48:
    orr r2, r2, sb, lsl #24
MobiClip_Code_020B3C4C:
    str r2, [r0, #0x100]!
MobiClip_Code_020B3C50:
    ldr r2, [sp, #0x14]
MobiClip_Code_020B3C54:
    orr r6, r6, r2, lsl #16
MobiClip_Code_020B3C58:
    ldr r2, [sp, #0x10]
MobiClip_Code_020B3C5C:
    orr r2, r6, r2, lsl #24
MobiClip_Code_020B3C60:
    str r2, [r0, #4]
MobiClip_Code_020B3C64:
    ldrb r6, [r0, #-1]
MobiClip_Code_020B3C68:
    ldr r2, [sp, #0xc]
MobiClip_Code_020B3C6C:
    ldr fp, [sp, #8]
MobiClip_Code_020B3C70:
    add r2, r6, r2
MobiClip_Code_020B3C74:
    add r2, r2, r3, lsl #1
MobiClip_Code_020B3C78:
    add r2, r2, #2
MobiClip_Code_020B3C7C:
    asr r2, r2, #2
MobiClip_Code_020B3C80:
    str r2, [sp, #4]
MobiClip_Code_020B3C84:
    orr r2, r2, fp, lsl #8
MobiClip_Code_020B3C88:
    ldr fp, [sp, #0x2c]
MobiClip_Code_020B3C8C:
    orr r2, r2, fp, lsl #16
MobiClip_Code_020B3C90:
    ldr fp, [sp, #0x28]
MobiClip_Code_020B3C94:
    orr r2, r2, fp, lsl #24
MobiClip_Code_020B3C98:
    str r2, [r0, #0x100]!
MobiClip_Code_020B3C9C:
    orr r2, lr, r4, lsl #8
MobiClip_Code_020B3CA0:
    ldr fp, [sp, #0x24]
MobiClip_Code_020B3CA4:
    orr r2, r2, r5, lsl #16
MobiClip_Code_020B3CA8:
    orr r2, r2, fp, lsl #24
MobiClip_Code_020B3CAC:
    str r2, [r0, #4]
MobiClip_Code_020B3CB0:
    ldrb fp, [r0, #-1]
MobiClip_Code_020B3CB4:
    add r2, fp, r3
MobiClip_Code_020B3CB8:
    add r2, r2, r6, lsl #1
MobiClip_Code_020B3CBC:
    add r2, r2, #2
MobiClip_Code_020B3CC0:
    asr r2, r2, #2
MobiClip_Code_020B3CC4:
    str r2, [sp]
MobiClip_Code_020B3CC8:
    orr r2, r2, ip, lsl #8
MobiClip_Code_020B3CCC:
    orr r2, r2, r7, lsl #16
MobiClip_Code_020B3CD0:
    orr r2, r2, r8, lsl #24
MobiClip_Code_020B3CD4:
    str r2, [r0, #0x100]!
MobiClip_Code_020B3CD8:
    orr r2, sb, sl, lsl #8
MobiClip_Code_020B3CDC:
    orr r3, r2, r1, lsl #16
MobiClip_Code_020B3CE0:
    ldr r2, [sp, #0x14]
MobiClip_Code_020B3CE4:
    orr r2, r3, r2, lsl #24
MobiClip_Code_020B3CE8:
    str r2, [r0, #4]
MobiClip_Code_020B3CEC:
    ldrb r2, [r0, #-1]
MobiClip_Code_020B3CF0:
    add r3, r2, r6
MobiClip_Code_020B3CF4:
    add r3, r3, fp, lsl #1
MobiClip_Code_020B3CF8:
    add r3, r3, #2
MobiClip_Code_020B3CFC:
    ldr r6, [sp, #4]
MobiClip_Code_020B3D00:
    asr r3, r3, #2
MobiClip_Code_020B3D04:
    orr r3, r3, r6, lsl #8
MobiClip_Code_020B3D08:
    ldr r6, [sp, #8]
MobiClip_Code_020B3D0C:
    orr r3, r3, r6, lsl #16
MobiClip_Code_020B3D10:
    ldr r6, [sp, #0x2c]
MobiClip_Code_020B3D14:
    orr r3, r3, r6, lsl #24
MobiClip_Code_020B3D18:
    str r3, [r0, #0x100]!
MobiClip_Code_020B3D1C:
    ldr r3, [sp, #0x28]
MobiClip_Code_020B3D20:
    orr r3, r3, lr, lsl #8
MobiClip_Code_020B3D24:
    orr r3, r3, r4, lsl #16
MobiClip_Code_020B3D28:
    orr r3, r3, r5, lsl #24
MobiClip_Code_020B3D2C:
    str r3, [r0, #4]
MobiClip_Code_020B3D30:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B3D34:
    add r3, r3, fp
MobiClip_Code_020B3D38:
    add r2, r3, r2, lsl #1
MobiClip_Code_020B3D3C:
    add r2, r2, #2
MobiClip_Code_020B3D40:
    asr r2, r2, #2
MobiClip_Code_020B3D44:
    ldr r3, [sp]
MobiClip_Code_020B3D48:
    orr r2, r2, r3, lsl #8
MobiClip_Code_020B3D4C:
    orr r2, r2, ip, lsl #16
MobiClip_Code_020B3D50:
    orr r2, r2, r7, lsl #24
MobiClip_Code_020B3D54:
    add r0, r0, #0x100
MobiClip_Code_020B3D58:
    str r2, [r0]
MobiClip_Code_020B3D5C:
    orr r2, r8, sb, lsl #8
MobiClip_Code_020B3D60:
    orr r2, r2, sl, lsl #16
MobiClip_Code_020B3D64:
    orr r1, r2, r1, lsl #24
MobiClip_Code_020B3D68:
    str r1, [r0, #4]
MobiClip_Code_020B3D6C:
    add sp, sp, #0x34
MobiClip_Code_020B3D70:
    sub fp, r0, #0x700
MobiClip_Code_020B3D74:
    pop {r0, r1, r2, r3, sl, ip, pc}
MobiClip_Code_020B3D78:
    push {r0, r1, r2, r3, sl, ip, lr}
MobiClip_Code_020B3D7C:
    sub sp, sp, #4
MobiClip_Code_020B3D80:
    ldr r6, [fp, #-0x100]
MobiClip_Code_020B3D84:
    ldrb r5, [fp, #-1]
MobiClip_Code_020B3D88:
    ldrb r4, [fp, #-0x101]
MobiClip_Code_020B3D8C:
    and r3, r6, #0xff
MobiClip_Code_020B3D90:
    lsl r2, r6, #0x10
MobiClip_Code_020B3D94:
    lsr ip, r2, #0x18
MobiClip_Code_020B3D98:
    add r2, r4, ip
MobiClip_Code_020B3D9C:
    add r1, r5, r3
MobiClip_Code_020B3DA0:
    add r2, r2, r3, lsl #1
MobiClip_Code_020B3DA4:
    lsl lr, r6, #8
MobiClip_Code_020B3DA8:
    lsr lr, lr, #0x18
MobiClip_Code_020B3DAC:
    add r3, r3, lr
MobiClip_Code_020B3DB0:
    add r3, r3, ip, lsl #1
MobiClip_Code_020B3DB4:
    lsr r6, r6, #0x18
MobiClip_Code_020B3DB8:
    add r1, r1, r4, lsl #1
MobiClip_Code_020B3DBC:
    add r1, r1, #2
MobiClip_Code_020B3DC0:
    add ip, ip, r6
MobiClip_Code_020B3DC4:
    add r2, r2, #2
MobiClip_Code_020B3DC8:
    asr r2, r2, #2
MobiClip_Code_020B3DCC:
    add ip, ip, lr, lsl #1
MobiClip_Code_020B3DD0:
    asr r1, r1, #2
MobiClip_Code_020B3DD4:
    add r3, r3, #2
MobiClip_Code_020B3DD8:
    asr r3, r3, #2
MobiClip_Code_020B3DDC:
    orr r8, r1, r2, lsl #8
MobiClip_Code_020B3DE0:
    add ip, ip, #2
MobiClip_Code_020B3DE4:
    asr ip, ip, #2
MobiClip_Code_020B3DE8:
    orr r8, r8, r3, lsl #16
MobiClip_Code_020B3DEC:
    orr r8, r8, ip, lsl #24
MobiClip_Code_020B3DF0:
    str r8, [sp]
MobiClip_Code_020B3DF4:
    str r8, [fp]
MobiClip_Code_020B3DF8:
    sub r7, fp, #0x100
MobiClip_Code_020B3DFC:
    ldr r7, [r7, #4]
MobiClip_Code_020B3E00:
    orr r0, r3, ip, lsl #8
MobiClip_Code_020B3E04:
    and r8, r7, #0xff
MobiClip_Code_020B3E08:
    lsl sb, r7, #0x10
MobiClip_Code_020B3E0C:
    lsr sb, sb, #0x18
MobiClip_Code_020B3E10:
    add lr, lr, r8
MobiClip_Code_020B3E14:
    add lr, lr, r6, lsl #1
MobiClip_Code_020B3E18:
    lsl sl, r7, #8
MobiClip_Code_020B3E1C:
    lsr sl, sl, #0x18
MobiClip_Code_020B3E20:
    add r6, r6, sb
MobiClip_Code_020B3E24:
    add r6, r6, r8, lsl #1
MobiClip_Code_020B3E28:
    add r8, r8, sl
MobiClip_Code_020B3E2C:
    add r7, sb, r7, lsr #24
MobiClip_Code_020B3E30:
    add lr, lr, #2
MobiClip_Code_020B3E34:
    asr lr, lr, #2
MobiClip_Code_020B3E38:
    add r7, r7, sl, lsl #1
MobiClip_Code_020B3E3C:
    add r8, r8, sb, lsl #1
MobiClip_Code_020B3E40:
    add r6, r6, #2
MobiClip_Code_020B3E44:
    asr r6, r6, #2
MobiClip_Code_020B3E48:
    add r8, r8, #2
MobiClip_Code_020B3E4C:
    asr r8, r8, #2
MobiClip_Code_020B3E50:
    orr sb, lr, r6, lsl #8
MobiClip_Code_020B3E54:
    add r7, r7, #2
MobiClip_Code_020B3E58:
    asr r7, r7, #2
MobiClip_Code_020B3E5C:
    orr sb, sb, r8, lsl #16
MobiClip_Code_020B3E60:
    orr r7, sb, r7, lsl #24
MobiClip_Code_020B3E64:
    str r7, [fp, #4]
MobiClip_Code_020B3E68:
    ldrb r7, [fp, #0xff]
MobiClip_Code_020B3E6C:
    orr sl, ip, lr, lsl #8
MobiClip_Code_020B3E70:
    orr sl, sl, r6, lsl #16
MobiClip_Code_020B3E74:
    add r4, r7, r4
MobiClip_Code_020B3E78:
    add r4, r4, r5, lsl #1
MobiClip_Code_020B3E7C:
    add r4, r4, #2
MobiClip_Code_020B3E80:
    asr r4, r4, #2
MobiClip_Code_020B3E84:
    orr sb, r4, r1, lsl #8
MobiClip_Code_020B3E88:
    orr sb, sb, r2, lsl #16
MobiClip_Code_020B3E8C:
    orr r8, sl, r8, lsl #24
MobiClip_Code_020B3E90:
    str r8, [fp, #0x104]
MobiClip_Code_020B3E94:
    orr sb, sb, r3, lsl #24
MobiClip_Code_020B3E98:
    str sb, [fp, #0x100]!
MobiClip_Code_020B3E9C:
    ldrb r8, [fp, #0xff]
MobiClip_Code_020B3EA0:
    orr r0, r0, lr, lsl #16
MobiClip_Code_020B3EA4:
    orr r6, r0, r6, lsl #24
MobiClip_Code_020B3EA8:
    add r5, r8, r5
MobiClip_Code_020B3EAC:
    add r5, r5, r7, lsl #1
MobiClip_Code_020B3EB0:
    add r5, r5, #2
MobiClip_Code_020B3EB4:
    asr r5, r5, #2
MobiClip_Code_020B3EB8:
    orr sl, r5, r4, lsl #8
MobiClip_Code_020B3EBC:
    orr sl, sl, r1, lsl #16
MobiClip_Code_020B3EC0:
    orr sl, sl, r2, lsl #24
MobiClip_Code_020B3EC4:
    str r6, [fp, #0x104]
MobiClip_Code_020B3EC8:
    str sl, [fp, #0x100]!
MobiClip_Code_020B3ECC:
    ldrb r6, [fp, #0xff]
MobiClip_Code_020B3ED0:
    orr r2, r2, r3, lsl #8
MobiClip_Code_020B3ED4:
    orr r2, r2, ip, lsl #16
MobiClip_Code_020B3ED8:
    add r7, r6, r7
MobiClip_Code_020B3EDC:
    add r7, r7, r8, lsl #1
MobiClip_Code_020B3EE0:
    add r7, r7, #2
MobiClip_Code_020B3EE4:
    asr r7, r7, #2
MobiClip_Code_020B3EE8:
    orr r0, r7, r5, lsl #8
MobiClip_Code_020B3EEC:
    orr r0, r0, r4, lsl #16
MobiClip_Code_020B3EF0:
    orr r1, r0, r1, lsl #24
MobiClip_Code_020B3EF4:
    orr r2, r2, lr, lsl #24
MobiClip_Code_020B3EF8:
    add fp, fp, #0x100
MobiClip_Code_020B3EFC:
    stm fp, {r1, r2}
MobiClip_Code_020B3F00:
    ldrb r2, [fp, #0xff]
MobiClip_Code_020B3F04:
    add r3, r2, r8
MobiClip_Code_020B3F08:
    add r3, r3, r6, lsl #1
MobiClip_Code_020B3F0C:
    add r3, r3, #2
MobiClip_Code_020B3F10:
    asr r3, r3, #2
MobiClip_Code_020B3F14:
    orr ip, r3, r7, lsl #8
MobiClip_Code_020B3F18:
    orr ip, ip, r5, lsl #16
MobiClip_Code_020B3F1C:
    orr ip, ip, r4, lsl #24
MobiClip_Code_020B3F20:
    str ip, [fp, #0x100]!
MobiClip_Code_020B3F24:
    ldr r8, [sp]
MobiClip_Code_020B3F28:
    str r8, [fp, #4]
MobiClip_Code_020B3F2C:
    ldrb ip, [fp, #0xff]
MobiClip_Code_020B3F30:
    add lr, ip, r6
MobiClip_Code_020B3F34:
    add lr, lr, r2, lsl #1
MobiClip_Code_020B3F38:
    add lr, lr, #2
MobiClip_Code_020B3F3C:
    asr lr, lr, #2
MobiClip_Code_020B3F40:
    orr r4, lr, r3, lsl #8
MobiClip_Code_020B3F44:
    orr r4, r4, r7, lsl #16
MobiClip_Code_020B3F48:
    orr r4, r4, r5, lsl #24
MobiClip_Code_020B3F4C:
    add fp, fp, #0x100
MobiClip_Code_020B3F50:
    stm fp, {r4, sb}
MobiClip_Code_020B3F54:
    ldrb r4, [fp, #0xff]
MobiClip_Code_020B3F58:
    add fp, fp, #0x100
MobiClip_Code_020B3F5C:
    add r2, r4, r2
MobiClip_Code_020B3F60:
    add r2, r2, ip, lsl #1
MobiClip_Code_020B3F64:
    add r2, r2, #2
MobiClip_Code_020B3F68:
    asr r2, r2, #2
MobiClip_Code_020B3F6C:
    orr r5, r2, lr, lsl #8
MobiClip_Code_020B3F70:
    orr r5, r5, r3, lsl #16
MobiClip_Code_020B3F74:
    orr r5, r5, r7, lsl #24
MobiClip_Code_020B3F78:
    stm fp, {r5, sl}
MobiClip_Code_020B3F7C:
    ldrb r5, [fp, #0xff]
MobiClip_Code_020B3F80:
    add ip, r5, ip
MobiClip_Code_020B3F84:
    add ip, ip, r4, lsl #1
MobiClip_Code_020B3F88:
    add ip, ip, #2
MobiClip_Code_020B3F8C:
    asr ip, ip, #2
MobiClip_Code_020B3F90:
    orr r2, ip, r2, lsl #8
MobiClip_Code_020B3F94:
    orr r2, r2, lr, lsl #16
MobiClip_Code_020B3F98:
    orr r2, r2, r3, lsl #24
MobiClip_Code_020B3F9C:
    str r2, [fp, #0x100]
MobiClip_Code_020B3FA0:
    str r1, [fp, #0x104]
MobiClip_Code_020B3FA4:
    sub fp, fp, #0x600
MobiClip_Code_020B3FA8:
    add sp, sp, #4
MobiClip_Code_020B3FAC:
    pop {r0, r1, r2, r3, sl, ip, pc}
MobiClip_Code_020B3FB0:
    push {r0, r1, r2, r3, sl, ip, lr}
MobiClip_Code_020B3FB4:
    mov r0, fp
MobiClip_Code_020B3FB8:
    ldr r2, [r0, #-0x100]
MobiClip_Code_020B3FBC:
    sub sp, sp, #0x30
MobiClip_Code_020B3FC0:
    lsl r1, r2, #0x10
MobiClip_Code_020B3FC4:
    lsr fp, r1, #0x18
MobiClip_Code_020B3FC8:
    and sl, r2, #0xff
MobiClip_Code_020B3FCC:
    add r1, sl, fp
MobiClip_Code_020B3FD0:
    add r1, r1, #1
MobiClip_Code_020B3FD4:
    asr ip, r1, #1
MobiClip_Code_020B3FD8:
    lsl r1, r2, #8
MobiClip_Code_020B3FDC:
    lsr r1, r1, #0x18
MobiClip_Code_020B3FE0:
    add lr, fp, r1
MobiClip_Code_020B3FE4:
    add lr, lr, #1
MobiClip_Code_020B3FE8:
    str sl, [sp, #0x2c]
MobiClip_Code_020B3FEC:
    asr sl, lr, #1
MobiClip_Code_020B3FF0:
    lsr r2, r2, #0x18
MobiClip_Code_020B3FF4:
    add lr, r1, r2
MobiClip_Code_020B3FF8:
    add lr, lr, #1
MobiClip_Code_020B3FFC:
    str fp, [sp, #0x28]
MobiClip_Code_020B4000:
    asr fp, lr, #1
MobiClip_Code_020B4004:
    sub sb, r0, #0x100
MobiClip_Code_020B4008:
    str fp, [sp, #0x20]
MobiClip_Code_020B400C:
    str sl, [sp, #0x24]
MobiClip_Code_020B4010:
    ldr r4, [sb, #4]
MobiClip_Code_020B4014:
    and r3, r4, #0xff
MobiClip_Code_020B4018:
    add lr, r2, r3
MobiClip_Code_020B401C:
    ldr sl, [sp, #0x24]
MobiClip_Code_020B4020:
    add lr, lr, #1
MobiClip_Code_020B4024:
    asr r5, lr, #1
MobiClip_Code_020B4028:
    orr ip, ip, sl, lsl #8
MobiClip_Code_020B402C:
    orr ip, ip, fp, lsl #16
MobiClip_Code_020B4030:
    orr ip, ip, r5, lsl #24
MobiClip_Code_020B4034:
    str r5, [sp, #0x1c]
MobiClip_Code_020B4038:
    str ip, [r0]
MobiClip_Code_020B403C:
    lsl ip, r4, #0x10
MobiClip_Code_020B4040:
    lsr ip, ip, #0x18
MobiClip_Code_020B4044:
    add lr, r3, ip
MobiClip_Code_020B4048:
    add lr, lr, #1
MobiClip_Code_020B404C:
    asr r8, lr, #1
MobiClip_Code_020B4050:
    lsl lr, r4, #8
MobiClip_Code_020B4054:
    lsr lr, lr, #0x18
MobiClip_Code_020B4058:
    add r5, ip, lr
MobiClip_Code_020B405C:
    add r5, r5, #1
MobiClip_Code_020B4060:
    asr r6, r5, #1
MobiClip_Code_020B4064:
    lsr r4, r4, #0x18
MobiClip_Code_020B4068:
    str r8, [sp, #0x18]
MobiClip_Code_020B406C:
    ldr r8, [sb, #8]
MobiClip_Code_020B4070:
    add r5, lr, r4
MobiClip_Code_020B4074:
    add r5, r5, #1
MobiClip_Code_020B4078:
    asr r7, r5, #1
MobiClip_Code_020B407C:
    and r5, r8, #0xff
MobiClip_Code_020B4080:
    ldr sl, [sp, #0x18]
MobiClip_Code_020B4084:
    add sb, r4, r5
MobiClip_Code_020B4088:
    add sb, sb, #1
MobiClip_Code_020B408C:
    orr sl, sl, r6, lsl #8
MobiClip_Code_020B4090:
    orr sl, sl, r7, lsl #16
MobiClip_Code_020B4094:
    asr sb, sb, #1
MobiClip_Code_020B4098:
    orr sl, sl, sb, lsl #24
MobiClip_Code_020B409C:
    str sl, [r0, #4]
MobiClip_Code_020B40A0:
    ldr sl, [sp, #0x2c]
MobiClip_Code_020B40A4:
    ldr fp, [sp, #0x28]
MobiClip_Code_020B40A8:
    add sl, sl, r1
MobiClip_Code_020B40AC:
    add sl, sl, fp, lsl #1
MobiClip_Code_020B40B0:
    add sl, sl, #2
MobiClip_Code_020B40B4:
    asr sl, sl, #2
MobiClip_Code_020B40B8:
    str sl, [sp, #0x14]
MobiClip_Code_020B40BC:
    add sl, fp, r2
MobiClip_Code_020B40C0:
    add sl, sl, r1, lsl #1
MobiClip_Code_020B40C4:
    add r1, r1, r3
MobiClip_Code_020B40C8:
    add r1, r1, r2, lsl #1
MobiClip_Code_020B40CC:
    add r1, r1, #2
MobiClip_Code_020B40D0:
    add sl, sl, #2
MobiClip_Code_020B40D4:
    asr sl, sl, #2
MobiClip_Code_020B40D8:
    asr r1, r1, #2
MobiClip_Code_020B40DC:
    add fp, sp, #0xc
MobiClip_Code_020B40E0:
    stm fp, {r1, sl}
MobiClip_Code_020B40E4:
    add r1, r2, ip
MobiClip_Code_020B40E8:
    add sl, sp, #0x10
MobiClip_Code_020B40EC:
    ldm sl, {r2, sl}
MobiClip_Code_020B40F0:
    add r1, r1, r3, lsl #1
MobiClip_Code_020B40F4:
    orr r2, sl, r2, lsl #8
MobiClip_Code_020B40F8:
    ldr sl, [sp, #0xc]
MobiClip_Code_020B40FC:
    add r1, r1, #2
MobiClip_Code_020B4100:
    asr r1, r1, #2
MobiClip_Code_020B4104:
    orr r2, r2, sl, lsl #16
MobiClip_Code_020B4108:
    orr r2, r2, r1, lsl #24
MobiClip_Code_020B410C:
    str r2, [r0, #0x100]!
MobiClip_Code_020B4110:
    add r2, r3, lr
MobiClip_Code_020B4114:
    add r3, ip, r4
MobiClip_Code_020B4118:
    add r2, r2, ip, lsl #1
MobiClip_Code_020B411C:
    add r3, r3, lr, lsl #1
MobiClip_Code_020B4120:
    add ip, lr, r5
MobiClip_Code_020B4124:
    add ip, ip, r4, lsl #1
MobiClip_Code_020B4128:
    add ip, ip, #2
MobiClip_Code_020B412C:
    asr lr, ip, #2
MobiClip_Code_020B4130:
    lsl ip, r8, #0x10
MobiClip_Code_020B4134:
    lsr ip, ip, #0x18
MobiClip_Code_020B4138:
    add r4, r4, ip
MobiClip_Code_020B413C:
    add r3, r3, #2
MobiClip_Code_020B4140:
    add r2, r2, #2
MobiClip_Code_020B4144:
    asr r2, r2, #2
MobiClip_Code_020B4148:
    asr r3, r3, #2
MobiClip_Code_020B414C:
    add r4, r4, r5, lsl #1
MobiClip_Code_020B4150:
    add r4, r4, #2
MobiClip_Code_020B4154:
    orr sl, r2, r3, lsl #8
MobiClip_Code_020B4158:
    orr sl, sl, lr, lsl #16
MobiClip_Code_020B415C:
    asr r4, r4, #2
MobiClip_Code_020B4160:
    orr sl, sl, r4, lsl #24
MobiClip_Code_020B4164:
    str sl, [r0, #4]
MobiClip_Code_020B4168:
    ldr sl, [sp, #0x24]
MobiClip_Code_020B416C:
    ldr fp, [sp, #0x20]
MobiClip_Code_020B4170:
    orr sl, sl, fp, lsl #8
MobiClip_Code_020B4174:
    ldr fp, [sp, #0x1c]
MobiClip_Code_020B4178:
    orr sl, sl, fp, lsl #16
MobiClip_Code_020B417C:
    ldr fp, [sp, #0x18]
MobiClip_Code_020B4180:
    orr sl, sl, fp, lsl #24
MobiClip_Code_020B4184:
    str sl, [r0, #0x100]!
MobiClip_Code_020B4188:
    add sl, r5, ip
MobiClip_Code_020B418C:
    add sl, sl, #1
MobiClip_Code_020B4190:
    asr fp, sl, #1
MobiClip_Code_020B4194:
    orr sl, r6, r7, lsl #8
MobiClip_Code_020B4198:
    orr sl, sl, sb, lsl #16
MobiClip_Code_020B419C:
    orr sl, sl, fp, lsl #24
MobiClip_Code_020B41A0:
    str fp, [sp, #8]
MobiClip_Code_020B41A4:
    str sl, [r0, #4]
MobiClip_Code_020B41A8:
    ldr sl, [sp, #0x10]
MobiClip_Code_020B41AC:
    ldr fp, [sp, #0xc]
MobiClip_Code_020B41B0:
    orr sl, sl, fp, lsl #8
MobiClip_Code_020B41B4:
    orr sl, sl, r1, lsl #16
MobiClip_Code_020B41B8:
    orr sl, sl, r2, lsl #24
MobiClip_Code_020B41BC:
    str sl, [r0, #0x100]!
MobiClip_Code_020B41C0:
    lsl sl, r8, #8
MobiClip_Code_020B41C4:
    lsr sl, sl, #0x18
MobiClip_Code_020B41C8:
    add r5, r5, sl
MobiClip_Code_020B41CC:
    add r5, r5, ip, lsl #1
MobiClip_Code_020B41D0:
    add r5, r5, #2
MobiClip_Code_020B41D4:
    asr fp, r5, #2
MobiClip_Code_020B41D8:
    orr r5, r3, lr, lsl #8
MobiClip_Code_020B41DC:
    orr r5, r5, r4, lsl #16
MobiClip_Code_020B41E0:
    orr r5, r5, fp, lsl #24
MobiClip_Code_020B41E4:
    str fp, [sp, #4]
MobiClip_Code_020B41E8:
    str r5, [r0, #4]
MobiClip_Code_020B41EC:
    add fp, sp, #0x1c
MobiClip_Code_020B41F0:
    ldm fp, {r5, fp}
MobiClip_Code_020B41F4:
    orr r5, fp, r5, lsl #8
MobiClip_Code_020B41F8:
    ldr fp, [sp, #0x18]
MobiClip_Code_020B41FC:
    orr r5, r5, fp, lsl #16
MobiClip_Code_020B4200:
    orr r5, r5, r6, lsl #24
MobiClip_Code_020B4204:
    str r5, [r0, #0x100]!
MobiClip_Code_020B4208:
    add r5, ip, sl
MobiClip_Code_020B420C:
    add r5, r5, #1
MobiClip_Code_020B4210:
    asr fp, r5, #1
MobiClip_Code_020B4214:
    str fp, [sp]
MobiClip_Code_020B4218:
    ldr fp, [sp, #8]
MobiClip_Code_020B421C:
    orr r5, r7, sb, lsl #8
MobiClip_Code_020B4220:
    orr r5, r5, fp, lsl #16
MobiClip_Code_020B4224:
    ldr fp, [sp]
MobiClip_Code_020B4228:
    orr r5, r5, fp, lsl #24
MobiClip_Code_020B422C:
    str r5, [r0, #4]
MobiClip_Code_020B4230:
    ldr fp, [sp, #0xc]
MobiClip_Code_020B4234:
    orr r5, fp, r1, lsl #8
MobiClip_Code_020B4238:
    orr r5, r5, r2, lsl #16
MobiClip_Code_020B423C:
    orr r5, r5, r3, lsl #24
MobiClip_Code_020B4240:
    str r5, [r0, #0x100]!
MobiClip_Code_020B4244:
    lsr r5, r8, #0x18
MobiClip_Code_020B4248:
    add ip, ip, r5
MobiClip_Code_020B424C:
    ldr fp, [sp, #4]
MobiClip_Code_020B4250:
    add ip, ip, sl, lsl #1
MobiClip_Code_020B4254:
    orr r8, lr, r4, lsl #8
MobiClip_Code_020B4258:
    orr r8, r8, fp, lsl #16
MobiClip_Code_020B425C:
    add ip, ip, #2
MobiClip_Code_020B4260:
    asr ip, ip, #2
MobiClip_Code_020B4264:
    orr r8, r8, ip, lsl #24
MobiClip_Code_020B4268:
    str r8, [r0, #4]
MobiClip_Code_020B426C:
    add fp, sp, #0x18
MobiClip_Code_020B4270:
    ldm fp, {r8, fp}
MobiClip_Code_020B4274:
    orr r1, r1, r2, lsl #8
MobiClip_Code_020B4278:
    orr r8, fp, r8, lsl #8
MobiClip_Code_020B427C:
    orr r6, r8, r6, lsl #16
MobiClip_Code_020B4280:
    orr r6, r6, r7, lsl #24
MobiClip_Code_020B4284:
    str r6, [r0, #0x100]!
MobiClip_Code_020B4288:
    ldr fp, [sp, #8]
MobiClip_Code_020B428C:
    add r6, sl, r5
MobiClip_Code_020B4290:
    orr r7, sb, fp, lsl #8
MobiClip_Code_020B4294:
    ldr fp, [sp]
MobiClip_Code_020B4298:
    add r6, r6, #1
MobiClip_Code_020B429C:
    orr r1, r1, r3, lsl #16
MobiClip_Code_020B42A0:
    orr r1, r1, lr, lsl #24
MobiClip_Code_020B42A4:
    asr r6, r6, #1
MobiClip_Code_020B42A8:
    orr r7, r7, fp, lsl #16
MobiClip_Code_020B42AC:
    orr r6, r7, r6, lsl #24
MobiClip_Code_020B42B0:
    str r1, [r0, #0x100]
MobiClip_Code_020B42B4:
    str r6, [r0, #4]
MobiClip_Code_020B42B8:
    sub fp, r0, #0x700
MobiClip_Code_020B42BC:
    ldrb r1, [fp, #0xc]
MobiClip_Code_020B42C0:
    ldr fp, [sp, #4]
MobiClip_Code_020B42C4:
    add r1, sl, r1
MobiClip_Code_020B42C8:
    add r1, r1, r5, lsl #1
MobiClip_Code_020B42CC:
    add r1, r1, #2
MobiClip_Code_020B42D0:
    asr r1, r1, #2
MobiClip_Code_020B42D4:
    orr r2, r4, fp, lsl #8
MobiClip_Code_020B42D8:
    orr r2, r2, ip, lsl #16
MobiClip_Code_020B42DC:
    orr r1, r2, r1, lsl #24
MobiClip_Code_020B42E0:
    str r1, [r0, #0x104]
MobiClip_Code_020B42E4:
    add sp, sp, #0x30
MobiClip_Code_020B42E8:
    sub fp, r0, #0x600
MobiClip_Code_020B42EC:
    pop {r0, r1, r2, r3, sl, ip, pc}
MobiClip_Code_020B42F0:
    ldr r4, [fp, #-0x100]
MobiClip_Code_020B42F4:
    str r4, [fp], #0x100
MobiClip_Code_020B42F8:
    str r4, [fp], #0x100
MobiClip_Code_020b42fc:
    str r4, [fp], #0x100
MobiClip_Code_020b4300:
    str r4, [fp], #0x100
MobiClip_Code_020b4304:
    sub fp, fp, #0x400
MobiClip_Code_020B4308:
    mov pc, lr
MobiClip_Code_020b430c:
    ldrb r6, [fp, #-1]
MobiClip_Code_020b4310:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020b4314:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B4318:
    str r6, [fp], #0x100
MobiClip_Code_020b431c:
    ldrb r6, [fp, #-1]
MobiClip_Code_020b4320:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020b4324:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B4328:
    str r6, [fp], #0x100
MobiClip_Code_020b432c:
    ldrb r6, [fp, #-1]
MobiClip_Code_020b4330:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020b4334:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B4338:
    str r6, [fp], #0x100
MobiClip_Code_020b433c:
    ldrb r6, [fp, #-1]
MobiClip_Code_020b4340:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020b4344:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B4348:
    str r6, [fp], #0x100
MobiClip_Code_020b434c:
    sub fp, fp, #0x400
MobiClip_Code_020b4350:
    mov pc, lr
MobiClip_Code_020b4354:
    push {sl, lr}
MobiClip_Code_020B4358:
    bl MobiClip_Code_020B2C38
MobiClip_Code_020b435c:
    push {r0, r1, r2, r3}
MobiClip_Code_020b4360:
    ldr r0, [fp, #-0x100]
MobiClip_Code_020b4364:
    add lr, fp, #0x300
MobiClip_Code_020B4368:
    ldrb r4, [lr, #-1]
MobiClip_Code_020b436c:
    lsr sl, r0, #0x18
MobiClip_Code_020b4370:
    add r5, r4, sl
MobiClip_Code_020b4374:
    add r5, r5, #1
MobiClip_Code_020B4378:
    asr r5, r5, #1
MobiClip_Code_020b437c:
    add r5, r5, r6, lsl #1
MobiClip_Code_020b4380:
    sub r6, r5, r4
MobiClip_Code_020b4384:
    lsl r4, r4, #2
MobiClip_Code_020B4388:
    sub sp, sp, #0x20
MobiClip_Code_020b438c:
    mov lr, sp
MobiClip_Code_020b4390:
    mov r2, #0xff
MobiClip_Code_020b4394:
    add r4, r4, r6
MobiClip_Code_020B4398:
    and r7, r2, r0
MobiClip_Code_020B439C:
    sub r8, r4, r7, lsl #2
MobiClip_Code_020B43A0:
    lsl r7, r7, #4
MobiClip_Code_020B43A4:
    add r4, r4, r6
MobiClip_Code_020B43A8:
    and sb, r2, r0, lsr #8
MobiClip_Code_020B43AC:
    sub ip, r4, sb, lsl #2
MobiClip_Code_020B43B0:
    lsl sb, sb, #4
MobiClip_Code_020B43B4:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020B43B8:
    add r4, r4, r6
MobiClip_Code_020B43BC:
    and r7, r2, r0, lsr #16
MobiClip_Code_020B43C0:
    sub r8, r4, r7, lsl #2
MobiClip_Code_020B43C4:
    lsl r7, r7, #4
MobiClip_Code_020B43C8:
    add r4, r4, r6
MobiClip_Code_020B43CC:
    and sb, r2, r0, lsr #24
MobiClip_Code_020B43D0:
    sub ip, r4, sb, lsl #2
MobiClip_Code_020B43D4:
    lsl sb, sb, #4
MobiClip_Code_020B43D8:
    stm lr!, {r7, r8, sb, ip}
MobiClip_Code_020B43DC:
    sub sb, r5, sl
MobiClip_Code_020B43E0:
    lsl sl, sl, #2
MobiClip_Code_020B43E4:
    mov lr, #4
MobiClip_Code_020B43E8:
    add sl, sl, sb
MobiClip_Code_020B43EC:
    ldrb r8, [fp, #-1]
MobiClip_Code_020B43F0:
    sub r7, sl, r8, lsl #2
MobiClip_Code_020B43F4:
    lsl r8, r8, #4
MobiClip_Code_020B43F8:
    ldm sp, {r0, r1, r2, r3, r4, r5, r6, ip}
MobiClip_Code_020b43fc:
    add r0, r0, r1
MobiClip_Code_020b4400:
    add r2, r2, r3
MobiClip_Code_020b4404:
    add r4, r4, r5
MobiClip_Code_020B4408:
    add r6, r6, ip
MobiClip_Code_020b440c:
    str r0, [sp]
MobiClip_Code_020b4410:
    str r2, [sp, #8]
MobiClip_Code_020b4414:
    str r4, [sp, #0x10]
MobiClip_Code_020B4418:
    str r6, [sp, #0x18]
MobiClip_Code_020b441c:
    add r8, r8, r7
MobiClip_Code_020b4420:
    add r5, r0, r8
MobiClip_Code_020b4424:
    add r5, r5, #0x10
MobiClip_Code_020B4428:
    asr r5, r5, #5
MobiClip_Code_020b442c:
    add r8, r8, r7
MobiClip_Code_020b4430:
    add ip, r2, r8
MobiClip_Code_020b4434:
    add ip, ip, #0x10
MobiClip_Code_020B4438:
    asr ip, ip, #5
MobiClip_Code_020b443c:
    orr r5, r5, ip, lsl #8
MobiClip_Code_020b4440:
    add r8, r8, r7
MobiClip_Code_020b4444:
    add ip, r4, r8
MobiClip_Code_020B4448:
    add ip, ip, #0x10
MobiClip_Code_020b444c:
    asr ip, ip, #5
MobiClip_Code_020b4450:
    orr r5, r5, ip, lsl #16
MobiClip_Code_020b4454:
    add r8, r8, r7
MobiClip_Code_020B4458:
    add ip, r6, r8
MobiClip_Code_020b445c:
    add ip, ip, #0x10
MobiClip_Code_020b4460:
    asr ip, ip, #5
MobiClip_Code_020b4464:
    orr r5, r5, ip, lsl #24
MobiClip_Code_020B4468:
    str r5, [fp], #0x100
MobiClip_Code_020b446c:
    subs lr, lr, #1
MobiClip_Code_020b4470:
    bne MobiClip_Code_020B43E8
MobiClip_Code_020b4474:
    add sp, sp, #0x20
MobiClip_Code_020B4478:
    sub fp, fp, #0x400
MobiClip_Code_020b447c:
    pop {r0, r1, r2, r3, sl, pc}
MobiClip_Code_020b4480:
    mov r6, #0
MobiClip_Code_020b4484:
    ldr r4, [fp, #-0x100]
MobiClip_Code_020B4488:
    add r6, r6, r4, lsr #24
MobiClip_Code_020b448c:
    lsl r4, r4, #8
MobiClip_Code_020b4490:
    add r6, r6, r4, lsr #24
MobiClip_Code_020b4494:
    lsl r4, r4, #8
MobiClip_Code_020B4498:
    add r6, r6, r4, lsr #24
MobiClip_Code_020B449C:
    lsl r4, r4, #8
MobiClip_Code_020B44A0:
    add r6, r6, r4, lsr #24
MobiClip_Code_020B44A4:
    sub fp, fp, #1
MobiClip_Code_020B44A8:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B44AC:
    add r6, r6, r4
MobiClip_Code_020B44B0:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B44B4:
    add r6, r6, r4
MobiClip_Code_020B44B8:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B44BC:
    add r6, r6, r4
MobiClip_Code_020B44C0:
    ldrb r4, [fp], #1
MobiClip_Code_020B44C4:
    add r6, r6, r4
MobiClip_Code_020B44C8:
    add r6, r6, #4
MobiClip_Code_020B44CC:
    asr r6, r6, #3
MobiClip_Code_020B44D0:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020B44D4:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020B44D8:
    str r6, [fp], #-0x100
MobiClip_Code_020B44DC:
    str r6, [fp], #-0x100
MobiClip_Code_020B44E0:
    str r6, [fp], #-0x100
MobiClip_Code_020B44E4:
    str r6, [fp]
MobiClip_Code_020B44E8:
    mov pc, lr
MobiClip_Code_020B44EC:
    mov r6, #0
MobiClip_Code_020B44F0:
    sub fp, fp, #1
MobiClip_Code_020B44F4:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B44F8:
    add r6, r6, r4
MobiClip_Code_020b44fc:
    ldrb r4, [fp], #0x100
MobiClip_Code_020b4500:
    add r6, r6, r4
MobiClip_Code_020b4504:
    ldrb r4, [fp], #0x100
MobiClip_Code_020B4508:
    add r6, r6, r4
MobiClip_Code_020b450c:
    ldrb r4, [fp], #1
MobiClip_Code_020b4510:
    add r6, r6, r4
MobiClip_Code_020b4514:
    add r6, r6, #2
MobiClip_Code_020B4518:
    asr r6, r6, #2
MobiClip_Code_020b451c:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020b4520:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020b4524:
    str r6, [fp], #-0x100
MobiClip_Code_020B4528:
    str r6, [fp], #-0x100
MobiClip_Code_020b452c:
    str r6, [fp], #-0x100
MobiClip_Code_020b4530:
    str r6, [fp]
MobiClip_Code_020b4534:
    mov pc, lr
MobiClip_Code_020B4538:
    mov r6, #0
MobiClip_Code_020b453c:
    ldr r4, [fp, #-0x100]
MobiClip_Code_020b4540:
    add r6, r6, r4, lsr #24
MobiClip_Code_020b4544:
    lsl r4, r4, #8
MobiClip_Code_020B4548:
    add r6, r6, r4, lsr #24
MobiClip_Code_020b454c:
    lsl r4, r4, #8
MobiClip_Code_020b4550:
    add r6, r6, r4, lsr #24
MobiClip_Code_020b4554:
    lsl r4, r4, #8
MobiClip_Code_020B4558:
    add r6, r6, r4, lsr #24
MobiClip_Code_020b455c:
    add r6, r6, #2
MobiClip_Code_020b4560:
    asr r6, r6, #2
MobiClip_Code_020b4564:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020B4568:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020b456c:
    str r6, [fp], #0x100
MobiClip_Code_020b4570:
    str r6, [fp], #0x100
MobiClip_Code_020b4574:
    str r6, [fp], #0x100
MobiClip_Code_020B4578:
    str r6, [fp], #0x100
MobiClip_Code_020b457c:
    sub fp, fp, #0x400
MobiClip_Code_020b4580:
    mov pc, lr
MobiClip_Code_020b4584:
    mov r6, #0x80
MobiClip_Code_020B4588:
    orr r6, r6, r6, lsl #8
MobiClip_Code_020b458c:
    orr r6, r6, r6, lsl #16
MobiClip_Code_020b4590:
    str r6, [fp], #0x100
MobiClip_Code_020b4594:
    str r6, [fp], #0x100
MobiClip_Code_020B4598:
    str r6, [fp], #0x100
MobiClip_Code_020B459C:
    str r6, [fp], #0x100
MobiClip_Code_020B45A0:
    sub fp, fp, #0x400
MobiClip_Code_020B45A4:
    mov pc, lr
    /* control metadata 0x020902ac..0x020902bc */
    .global gMobiClip_intra4_neighbor_dispatch
    .type gMobiClip_intra4_neighbor_dispatch, %object
gMobiClip_intra4_neighbor_dispatch:
    /* intra4_neighbor */
    .global gMobiClip_intra4_neighbor
gMobiClip_intra4_neighbor:
    .word MobiClip_Code_020b4584 - .
    .word MobiClip_Code_020B4538 - . + 0x4
    .word MobiClip_Code_020B44EC - . + 0x8
    .word MobiClip_Code_020b4480 - . + 0xc
MobiClip_Code_020B45B8:
    sub r5, pc, #0x18
MobiClip_Code_020B45BC:
    mov r8, #0
MobiClip_Code_020B45C0:
    sub r6, fp, sl
MobiClip_Code_020B45C4:
    lsls r7, r6, #0x18
MobiClip_Code_020B45C8:
    addne r8, r8, #8
MobiClip_Code_020B45CC:
    cmp r6, #0x100
MobiClip_Code_020B45D0:
    addge r8, r8, #4
MobiClip_Code_020B45D4:
    ldr r6, [r5, r8]
MobiClip_Code_020B45D8:
    add pc, r5, r6
MobiClip_Code_020B45DC:
    ldrb r5, [fp, #-1]
MobiClip_Code_020B45E0:
    ldrb r6, [fp, #0xff]
MobiClip_Code_020B45E4:
    add r4, r5, r6
MobiClip_Code_020B45E8:
    add r4, r4, #1
MobiClip_Code_020B45EC:
    asr r4, r4, #1
MobiClip_Code_020B45F0:
    ldrb r7, [fp, #0x1ff]!
MobiClip_Code_020B45F4:
    add r5, r5, r6, lsl #1
MobiClip_Code_020B45F8:
    add r5, r5, r7
MobiClip_Code_020b45fc:
    add r5, r5, #2
MobiClip_Code_020b4600:
    asr r5, r5, #2
MobiClip_Code_020b4604:
    orr r4, r4, r5, lsl #8
MobiClip_Code_020B4608:
    add r5, r6, r7
MobiClip_Code_020b460c:
    add r5, r5, #1
MobiClip_Code_020b4610:
    asr r5, r5, #1
MobiClip_Code_020b4614:
    orr r4, r4, r5, lsl #16
MobiClip_Code_020B4618:
    ldrb r8, [fp, #0x100]!
MobiClip_Code_020b461c:
    add r6, r6, r7, lsl #1
MobiClip_Code_020b4620:
    add r6, r6, r8
MobiClip_Code_020b4624:
    add r6, r6, #2
MobiClip_Code_020B4628:
    asr r6, r6, #2
MobiClip_Code_020b462c:
    orr r4, r4, r6, lsl #24
MobiClip_Code_020b4630:
    orr r5, r5, r6, lsl #8
MobiClip_Code_020b4634:
    add r6, r7, r8
MobiClip_Code_020B4638:
    add r6, r6, #1
MobiClip_Code_020b463c:
    asr r6, r6, #1
MobiClip_Code_020b4640:
    orr r5, r5, r6, lsl #16
MobiClip_Code_020b4644:
    add r7, r7, r8, lsl #1
MobiClip_Code_020B4648:
    add r7, r7, r8
MobiClip_Code_020b464c:
    add r7, r7, #2
MobiClip_Code_020b4650:
    asr r7, r7, #2
MobiClip_Code_020b4654:
    orr r5, r5, r7, lsl #24
MobiClip_Code_020B4658:
    orr r6, r6, r7, lsl #8
MobiClip_Code_020b465c:
    orr r8, r8, r8, lsl #8
MobiClip_Code_020b4660:
    orr r6, r6, r8, lsl #16
MobiClip_Code_020b4664:
    orr r8, r8, r8, lsl #16
MobiClip_Code_020B4668:
    str r8, [fp, #1]!
MobiClip_Code_020b466c:
    str r6, [fp, #-0x100]!
MobiClip_Code_020b4670:
    str r5, [fp, #-0x100]!
MobiClip_Code_020b4674:
    str r4, [fp, #-0x100]!
MobiClip_Code_020B4678:
    mov pc, lr
MobiClip_Code_020b467c:
    push {ip, lr}
MobiClip_Code_020b4680:
    ldrb r8, [fp, #-0x101]
MobiClip_Code_020b4684:
    ldrb r7, [fp, #-1]
MobiClip_Code_020B4688:
    ldr sb, [fp, #-0x100]
MobiClip_Code_020b468c:
    add ip, r8, r7
MobiClip_Code_020b4690:
    add ip, ip, #1
MobiClip_Code_020b4694:
    asr lr, ip, #1
MobiClip_Code_020B4698:
    and ip, sb, #0xff
MobiClip_Code_020B469C:
    lsl r5, sb, #0x10
MobiClip_Code_020B46A0:
    lsr r5, r5, #0x18
MobiClip_Code_020B46A4:
    add r6, r8, ip, lsl #1
MobiClip_Code_020B46A8:
    add r4, r7, r8, lsl #1
MobiClip_Code_020B46AC:
    add r4, r4, ip
MobiClip_Code_020B46B0:
    add ip, ip, r5, lsl #1
MobiClip_Code_020B46B4:
    lsl sb, sb, #8
MobiClip_Code_020B46B8:
    add sb, ip, sb, lsr #24
MobiClip_Code_020B46BC:
    add r4, r4, #2
MobiClip_Code_020B46C0:
    add r6, r6, r5
MobiClip_Code_020B46C4:
    add r6, r6, #2
MobiClip_Code_020B46C8:
    asr r4, r4, #2
MobiClip_Code_020B46CC:
    orr ip, lr, r4, lsl #8
MobiClip_Code_020B46D0:
    asr r6, r6, #2
MobiClip_Code_020B46D4:
    add sb, sb, #2
MobiClip_Code_020B46D8:
    asr sb, sb, #2
MobiClip_Code_020B46DC:
    orr ip, ip, r6, lsl #16
MobiClip_Code_020B46E0:
    orr sb, ip, sb, lsl #24
MobiClip_Code_020B46E4:
    str sb, [fp]
MobiClip_Code_020B46E8:
    ldrb sb, [fp, #0xff]
MobiClip_Code_020B46EC:
    add r8, r8, r7, lsl #1
MobiClip_Code_020B46F0:
    add r8, r8, sb
MobiClip_Code_020B46F4:
    add ip, r7, sb
MobiClip_Code_020B46F8:
    add ip, ip, #1
MobiClip_Code_020b46fc:
    add r8, r8, #2
MobiClip_Code_020b4700:
    asr r8, r8, #2
MobiClip_Code_020b4704:
    asr ip, ip, #1
MobiClip_Code_020B4708:
    orr r5, ip, r8, lsl #8
MobiClip_Code_020b470c:
    orr lr, r5, lr, lsl #16
MobiClip_Code_020b4710:
    orr lr, lr, r4, lsl #24
MobiClip_Code_020b4714:
    str lr, [fp, #0x100]!
MobiClip_Code_020B4718:
    ldrb lr, [fp, #0xff]
MobiClip_Code_020b471c:
    add r7, r7, sb, lsl #1
MobiClip_Code_020b4720:
    add r7, r7, lr
MobiClip_Code_020b4724:
    add r4, sb, lr
MobiClip_Code_020B4728:
    add r4, r4, #1
MobiClip_Code_020b472c:
    add r7, r7, #2
MobiClip_Code_020b4730:
    asr r7, r7, #2
MobiClip_Code_020b4734:
    asr r4, r4, #1
MobiClip_Code_020B4738:
    orr r5, r4, r7, lsl #8
MobiClip_Code_020b473c:
    orr ip, r5, ip, lsl #16
MobiClip_Code_020b4740:
    orr r8, ip, r8, lsl #24
MobiClip_Code_020b4744:
    str r8, [fp, #0x100]!
MobiClip_Code_020B4748:
    ldrb r8, [fp, #0xff]
MobiClip_Code_020b474c:
    add sb, sb, lr, lsl #1
MobiClip_Code_020b4750:
    add ip, lr, r8
MobiClip_Code_020b4754:
    add r8, sb, r8
MobiClip_Code_020B4758:
    add r8, r8, #2
MobiClip_Code_020b475c:
    add ip, ip, #1
MobiClip_Code_020b4760:
    asr ip, ip, #1
MobiClip_Code_020b4764:
    asr r8, r8, #2
MobiClip_Code_020B4768:
    orr r8, ip, r8, lsl #8
MobiClip_Code_020b476c:
    orr r8, r8, r4, lsl #16
MobiClip_Code_020b4770:
    orr r7, r8, r7, lsl #24
MobiClip_Code_020b4774:
    str r7, [fp, #0x100]
MobiClip_Code_020B4778:
    sub fp, fp, #0x200
MobiClip_Code_020b477c:
    pop {ip, pc}
MobiClip_Code_020b4780:
    push {r1, r2, r3, ip, lr}
MobiClip_Code_020b4784:
    ldr lr, [fp, #-0x100]
MobiClip_Code_020B4788:
    ldrb r3, [fp, #-0x101]
MobiClip_Code_020b478c:
    and r1, lr, #0xff
MobiClip_Code_020b4790:
    lsr r7, lr, #0x18
MobiClip_Code_020b4794:
    add r2, r3, r1
MobiClip_Code_020B4798:
    add r2, r2, #1
MobiClip_Code_020B479C:
    asr r4, r2, #1
MobiClip_Code_020B47A0:
    lsl r2, lr, #0x10
MobiClip_Code_020B47A4:
    lsr r2, r2, #0x18
MobiClip_Code_020B47A8:
    add ip, r1, r2
MobiClip_Code_020B47AC:
    add ip, ip, #1
MobiClip_Code_020B47B0:
    asr r5, ip, #1
MobiClip_Code_020B47B4:
    lsl ip, lr, #8
MobiClip_Code_020B47B8:
    lsr ip, ip, #0x18
MobiClip_Code_020B47BC:
    add r6, r2, ip
MobiClip_Code_020B47C0:
    add r6, r6, #1
MobiClip_Code_020B47C4:
    add lr, ip, r7
MobiClip_Code_020B47C8:
    add lr, lr, #1
MobiClip_Code_020B47CC:
    asr r6, r6, #1
MobiClip_Code_020B47D0:
    orr r8, r4, r5, lsl #8
MobiClip_Code_020B47D4:
    orr r8, r8, r6, lsl #16
MobiClip_Code_020B47D8:
    asr lr, lr, #1
MobiClip_Code_020B47DC:
    orr lr, r8, lr, lsl #24
MobiClip_Code_020B47E0:
    str lr, [fp]
MobiClip_Code_020B47E4:
    ldrb lr, [fp, #-1]
MobiClip_Code_020B47E8:
    add sb, r3, r1, lsl #1
MobiClip_Code_020B47EC:
    add sb, sb, r2
MobiClip_Code_020B47F0:
    add r8, lr, r3, lsl #1
MobiClip_Code_020B47F4:
    add r8, r8, r1
MobiClip_Code_020B47F8:
    add r1, r1, r2, lsl #1
MobiClip_Code_020b47fc:
    add r2, r2, ip, lsl #1
MobiClip_Code_020b4800:
    add r1, r1, ip
MobiClip_Code_020b4804:
    add r8, r8, #2
MobiClip_Code_020B4808:
    add sb, sb, #2
MobiClip_Code_020b480c:
    asr sb, sb, #2
MobiClip_Code_020b4810:
    asr r8, r8, #2
MobiClip_Code_020b4814:
    add r1, r1, #2
MobiClip_Code_020B4818:
    add r2, r2, r7
MobiClip_Code_020b481c:
    add r2, r2, #2
MobiClip_Code_020b4820:
    asr r1, r1, #2
MobiClip_Code_020b4824:
    orr ip, r8, sb, lsl #8
MobiClip_Code_020B4828:
    orr ip, ip, r1, lsl #16
MobiClip_Code_020b482c:
    asr r2, r2, #2
MobiClip_Code_020b4830:
    orr r2, ip, r2, lsl #24
MobiClip_Code_020b4834:
    str r2, [fp, #0x100]!
MobiClip_Code_020B4838:
    ldrb r2, [fp, #-1]
MobiClip_Code_020b483c:
    add r3, r3, lr, lsl #1
MobiClip_Code_020b4840:
    add r3, r3, r2
MobiClip_Code_020b4844:
    add r3, r3, #2
MobiClip_Code_020B4848:
    asr r3, r3, #2
MobiClip_Code_020b484c:
    orr r3, r3, r4, lsl #8
MobiClip_Code_020b4850:
    orr r3, r3, r5, lsl #16
MobiClip_Code_020b4854:
    orr r3, r3, r6, lsl #24
MobiClip_Code_020B4858:
    str r3, [fp, #0x100]!
MobiClip_Code_020b485c:
    ldrb r3, [fp, #-1]
MobiClip_Code_020b4860:
    add r2, lr, r2, lsl #1
MobiClip_Code_020b4864:
    add r2, r2, r3
MobiClip_Code_020B4868:
    add r2, r2, #2
MobiClip_Code_020b486c:
    asr r2, r2, #2
MobiClip_Code_020b4870:
    orr r2, r2, r8, lsl #8
MobiClip_Code_020b4874:
    orr r2, r2, sb, lsl #16
MobiClip_Code_020B4878:
    orr r1, r2, r1, lsl #24
MobiClip_Code_020b487c:
    str r1, [fp, #0x100]
MobiClip_Code_020b4880:
    sub fp, fp, #0x200
MobiClip_Code_020b4884:
    pop {r1, r2, r3, ip, pc}
MobiClip_Code_020B4888:
    push {ip, lr}
MobiClip_Code_020b488c:
    ldr r7, [fp, #-0x100]
MobiClip_Code_020b4890:
    ldrb ip, [fp, #-0x101]
MobiClip_Code_020b4894:
    and lr, r7, #0xff
MobiClip_Code_020B4898:
    ldrb sb, [fp, #-1]
MobiClip_Code_020B489C:
    lsl r4, r7, #0x10
MobiClip_Code_020B48A0:
    lsr r4, r4, #0x18
MobiClip_Code_020B48A4:
    add r5, ip, lr, lsl #1
MobiClip_Code_020B48A8:
    add r8, sb, ip, lsl #1
MobiClip_Code_020B48AC:
    add r8, r8, lr
MobiClip_Code_020B48B0:
    lsl r6, r7, #8
MobiClip_Code_020B48B4:
    lsr r6, r6, #0x18
MobiClip_Code_020B48B8:
    add lr, lr, r4, lsl #1
MobiClip_Code_020B48BC:
    add r5, r5, r4
MobiClip_Code_020B48C0:
    add r4, r4, r6, lsl #1
MobiClip_Code_020B48C4:
    add r7, r4, r7, lsr #24
MobiClip_Code_020B48C8:
    add r5, r5, #2
MobiClip_Code_020B48CC:
    add lr, lr, r6
MobiClip_Code_020B48D0:
    add r8, r8, #2
MobiClip_Code_020B48D4:
    asr r8, r8, #2
MobiClip_Code_020B48D8:
    add lr, lr, #2
MobiClip_Code_020B48DC:
    asr r5, r5, #2
MobiClip_Code_020B48E0:
    orr r4, r8, r5, lsl #8
MobiClip_Code_020B48E4:
    asr lr, lr, #2
MobiClip_Code_020B48E8:
    add r7, r7, #2
MobiClip_Code_020B48EC:
    asr r7, r7, #2
MobiClip_Code_020B48F0:
    orr r4, r4, lr, lsl #16
MobiClip_Code_020B48F4:
    orr r7, r4, r7, lsl #24
MobiClip_Code_020B48F8:
    str r7, [fp]
MobiClip_Code_020b48fc:
    ldrb r7, [fp, #0xff]
MobiClip_Code_020b4900:
    add r4, r7, sb, lsl #1
MobiClip_Code_020b4904:
    add ip, r4, ip
MobiClip_Code_020B4908:
    add ip, ip, #2
MobiClip_Code_020b490c:
    asr ip, ip, #2
MobiClip_Code_020b4910:
    orr r4, ip, r8, lsl #8
MobiClip_Code_020b4914:
    orr r4, r4, r5, lsl #16
MobiClip_Code_020B4918:
    orr lr, r4, lr, lsl #24
MobiClip_Code_020b491c:
    str lr, [fp, #0x100]!
MobiClip_Code_020b4920:
    ldrb lr, [fp, #0xff]
MobiClip_Code_020b4924:
    add r4, lr, r7, lsl #1
MobiClip_Code_020B4928:
    add sb, r4, sb
MobiClip_Code_020b492c:
    add sb, sb, #2
MobiClip_Code_020b4930:
    asr sb, sb, #2
MobiClip_Code_020b4934:
    orr r4, sb, ip, lsl #8
MobiClip_Code_020B4938:
    orr r4, r4, r8, lsl #16
MobiClip_Code_020b493c:
    orr r4, r4, r5, lsl #24
MobiClip_Code_020b4940:
    str r4, [fp, #0x100]!
MobiClip_Code_020b4944:
    ldrb r4, [fp, #0xff]
MobiClip_Code_020B4948:
    add lr, r4, lr, lsl #1
MobiClip_Code_020b494c:
    add r7, lr, r7
MobiClip_Code_020b4950:
    add r7, r7, #2
MobiClip_Code_020b4954:
    asr r7, r7, #2
MobiClip_Code_020B4958:
    orr r7, r7, sb, lsl #8
MobiClip_Code_020b495c:
    orr r7, r7, ip, lsl #16
MobiClip_Code_020b4960:
    orr r7, r7, r8, lsl #24
MobiClip_Code_020b4964:
    str r7, [fp, #0x100]
MobiClip_Code_020B4968:
    sub fp, fp, #0x200
MobiClip_Code_020b496c:
    pop {ip, pc}
MobiClip_Code_020b4970:
    push {r2, r3, sl, lr}
MobiClip_Code_020b4974:
    ldr sb, [fp, #-0x100]
MobiClip_Code_020B4978:
    sub r2, fp, #0x100
MobiClip_Code_020b497c:
    lsl r3, sb, #0x10
MobiClip_Code_020b4980:
    lsr r6, r3, #0x18
MobiClip_Code_020b4984:
    and r7, sb, #0xff
MobiClip_Code_020B4988:
    add r3, r7, r6
MobiClip_Code_020b498c:
    add r3, r3, #1
MobiClip_Code_020b4990:
    asr r8, r3, #1
MobiClip_Code_020b4994:
    lsl r3, sb, #8
MobiClip_Code_020B4998:
    lsr ip, r3, #0x18
MobiClip_Code_020B499C:
    add r3, r6, ip
MobiClip_Code_020B49A0:
    lsr sb, sb, #0x18
MobiClip_Code_020B49A4:
    add r3, r3, #1
MobiClip_Code_020B49A8:
    asr lr, r3, #1
MobiClip_Code_020B49AC:
    add r3, ip, sb
MobiClip_Code_020B49B0:
    add r3, r3, #1
MobiClip_Code_020B49B4:
    asr r4, r3, #1
MobiClip_Code_020B49B8:
    ldr r3, [r2, #4]
MobiClip_Code_020B49BC:
    add r7, r7, r6, lsl #1
MobiClip_Code_020B49C0:
    and r2, r3, #0xff
MobiClip_Code_020B49C4:
    add r5, sb, r2
MobiClip_Code_020B49C8:
    add r6, r6, ip, lsl #1
MobiClip_Code_020B49CC:
    add r7, r7, ip
MobiClip_Code_020B49D0:
    orr r8, r8, lr, lsl #8
MobiClip_Code_020B49D4:
    add r5, r5, #1
MobiClip_Code_020B49D8:
    asr r5, r5, #1
MobiClip_Code_020B49DC:
    orr r8, r8, r4, lsl #16
MobiClip_Code_020B49E0:
    orr r8, r8, r5, lsl #24
MobiClip_Code_020B49E4:
    add ip, ip, sb, lsl #1
MobiClip_Code_020B49E8:
    str r8, [fp]
MobiClip_Code_020B49EC:
    add r7, r7, #2
MobiClip_Code_020B49F0:
    asr r8, r7, #2
MobiClip_Code_020B49F4:
    add ip, ip, r2
MobiClip_Code_020B49F8:
    add ip, ip, #2
MobiClip_Code_020b49fc:
    add r6, r6, sb
MobiClip_Code_020b4a00:
    asr r7, ip, #2
MobiClip_Code_020b4a04:
    lsl ip, r3, #0x10
MobiClip_Code_020B4A08:
    lsr ip, ip, #0x18
MobiClip_Code_020b4a0c:
    add r6, r6, #2
MobiClip_Code_020b4a10:
    add sb, sb, r2, lsl #1
MobiClip_Code_020b4a14:
    add sb, sb, ip
MobiClip_Code_020B4A18:
    asr r6, r6, #2
MobiClip_Code_020b4a1c:
    orr r8, r8, r6, lsl #8
MobiClip_Code_020b4a20:
    add sb, sb, #2
MobiClip_Code_020b4a24:
    asr sb, sb, #2
MobiClip_Code_020B4A28:
    orr r8, r8, r7, lsl #16
MobiClip_Code_020b4a2c:
    orr r8, r8, sb, lsl #24
MobiClip_Code_020b4a30:
    str r8, [fp, #0x100]!
MobiClip_Code_020b4a34:
    add r8, r2, ip
MobiClip_Code_020B4A38:
    add r2, r2, ip, lsl #1
MobiClip_Code_020b4a3c:
    lsl r3, r3, #8
MobiClip_Code_020b4a40:
    add r2, r2, r3, lsr #24
MobiClip_Code_020b4a44:
    add r8, r8, #1
MobiClip_Code_020B4A48:
    orr lr, lr, r4, lsl #8
MobiClip_Code_020b4a4c:
    orr lr, lr, r5, lsl #16
MobiClip_Code_020b4a50:
    asr r8, r8, #1
MobiClip_Code_020b4a54:
    add r2, r2, #2
MobiClip_Code_020B4A58:
    orr r3, r6, r7, lsl #8
MobiClip_Code_020b4a5c:
    orr sb, r3, sb, lsl #16
MobiClip_Code_020b4a60:
    asr r2, r2, #2
MobiClip_Code_020b4a64:
    orr lr, lr, r8, lsl #24
MobiClip_Code_020B4A68:
    str lr, [fp, #0x100]!
MobiClip_Code_020b4a6c:
    orr sb, sb, r2, lsl #24
MobiClip_Code_020b4a70:
    str sb, [fp, #0x100]
MobiClip_Code_020b4a74:
    sub fp, fp, #0x200
MobiClip_Code_020B4A78:
    pop {r2, r3, sl, pc}
MobiClip_Code_020b4a7c:
    lsls r3, r3, #8
MobiClip_Code_020b4a80:
    bhs MobiClip_Code_020B4AD0
MobiClip_Code_020b4a84:
    subs r2, r2, #8
MobiClip_Code_020B4A88:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020b4a8c:
    lsr r4, r3, #0x14
MobiClip_Code_020b4a90:
    add r4, fp, r4, lsl #1
MobiClip_Code_020b4a94:
    ldrh r4, [r4]
MobiClip_Code_020B4A98:
    add r7, fp, #0x2000
MobiClip_Code_020B4A9C:
    ldrb r7, [r7, r4, lsr #9]
MobiClip_Code_020B4AA0:
    and r5, r4, #0xf
MobiClip_Code_020B4AA4:
    lsr r4, r4, #4
MobiClip_Code_020B4AA8:
    and r6, r4, #0x1f
MobiClip_Code_020B4AAC:
    add r6, r6, r7
MobiClip_Code_020B4AB0:
    lsr r4, r4, #5
MobiClip_Code_020B4AB4:
    lsls r3, r3, r5
MobiClip_Code_020B4AB8:
    rsbhs r6, r6, #0
MobiClip_Code_020B4ABC:
    subs r2, r2, r5
MobiClip_Code_020B4AC0:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B4AC4:
    and r5, r4, #0x3f
MobiClip_Code_020B4AC8:
    lsr r4, r4, #6
MobiClip_Code_020B4ACC:
    b MobiClip_Code_020B4BA4
MobiClip_Code_020B4AD0:
    adds r3, r3, r3
MobiClip_Code_020B4AD4:
    bhs MobiClip_Code_020B4B28
MobiClip_Code_020B4AD8:
    subs r2, r2, #9
MobiClip_Code_020B4ADC:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B4AE0:
    lsr r4, r3, #0x14
MobiClip_Code_020B4AE4:
    add r4, fp, r4, lsl #1
MobiClip_Code_020B4AE8:
    ldrh r4, [r4]
MobiClip_Code_020B4AEC:
    and r5, r4, #0xf
MobiClip_Code_020B4AF0:
    lsr r4, r4, #4
MobiClip_Code_020B4AF4:
    and r6, r4, #0x1f
MobiClip_Code_020B4AF8:
    lsr r4, r4, #5
MobiClip_Code_020b4afc:
    and r8, r4, #0x3f
MobiClip_Code_020b4b00:
    lsr r4, r4, #6
MobiClip_Code_020b4b04:
    add r7, fp, #0x2080
MobiClip_Code_020B4B08:
    add r7, r7, r6
MobiClip_Code_020b4b0c:
    ldrb r7, [r7, r4, lsl #6]
MobiClip_Code_020b4b10:
    lsls r3, r3, r5
MobiClip_Code_020b4b14:
    rsbhs r6, r6, #0
MobiClip_Code_020B4B18:
    subs r2, r2, r5
MobiClip_Code_020b4b1c:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020b4b20:
    add r5, r8, r7
MobiClip_Code_020b4b24:
    b MobiClip_Code_020B4BA4
MobiClip_Code_020B4B28:
    subs r2, r2, #9
MobiClip_Code_020b4b2c:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020b4b30:
    lsr r4, r3, #0x1f
MobiClip_Code_020b4b34:
    lsl r3, r3, #1
MobiClip_Code_020B4B38:
    lsr r5, r3, #0x1a
MobiClip_Code_020b4b3c:
    lsl r3, r3, #6
MobiClip_Code_020b4b40:
    subs r2, r2, #7
MobiClip_Code_020b4b44:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B4B48:
    asr r6, r3, #0x14
MobiClip_Code_020b4b4c:
    lsl r3, r3, #0xc
MobiClip_Code_020b4b50:
    subs r2, r2, #0xc
MobiClip_Code_020b4b54:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B4B58:
    b MobiClip_Code_020B4BA4
MobiClip_Code_020b4b5c:
    str lr, [sp, #-4]!
MobiClip_Code_020b4b60:
    ldr fp, [r0, #0x3b8]
MobiClip_Code_020b4b64:
    lsr r4, r3, #0x19
MobiClip_Code_020B4B68:
    cmp r4, #3
MobiClip_Code_020b4b6c:
    beq MobiClip_Code_020b4a7c
MobiClip_Code_020b4b70:
    lsr r4, r3, #0x14
MobiClip_Code_020b4b74:
    add r4, fp, r4, lsl #1
MobiClip_Code_020B4B78:
    ldrh r4, [r4]
MobiClip_Code_020b4b7c:
    and r5, r4, #0xf
MobiClip_Code_020b4b80:
    lsr r4, r4, #4
MobiClip_Code_020b4b84:
    and r6, r4, #0x1f
MobiClip_Code_020B4B88:
    lsr r4, r4, #5
MobiClip_Code_020b4b8c:
    lsls r3, r3, r5
MobiClip_Code_020b4b90:
    rsbhs r6, r6, #0
MobiClip_Code_020b4b94:
    subs r2, r2, r5
MobiClip_Code_020B4B98:
    bllt MobiClip_Code_020B2C24
MobiClip_Code_020B4B9C:
    and r5, r4, #0x3f
MobiClip_Code_020B4BA0:
    lsr r4, r4, #6
MobiClip_Code_020B4BA4:
    add ip, ip, r5, lsl #2
MobiClip_Code_020B4BA8:
    ldr r8, [ip], #4
MobiClip_Code_020B4BAC:
    and r5, r8, #0xff
MobiClip_Code_020B4BB0:
    lsr r7, r8, #8
MobiClip_Code_020B4BB4:
    smulbb r7, r6, r7
MobiClip_Code_020B4BB8:
    add r8, r0, #0x1b4
MobiClip_Code_020B4BBC:
    str r7, [r8, r5, lsl #2]
MobiClip_Code_020B4BC0:
    tst r4, #1
MobiClip_Code_020B4BC4:
    beq MobiClip_Code_020b4b64
MobiClip_Code_020B4BC8:
    pop {pc}
MobiClip_Code_020B4BCC:
    push {r0, r1, r2, r3}
MobiClip_Code_020B4BD0:
    add lr, r0, #0x1b4
MobiClip_Code_020B4BD4:
    add fp, lr, #0x100
MobiClip_Code_020B4BD8:
    ldm lr!, {r0, r1, r2, r3, r4, r5, r6, r7}
MobiClip_Code_020B4BDC:
    add r0, r0, #0x20
MobiClip_Code_020B4BE0:
    mov ip, #8
MobiClip_Code_020B4BE4:
    add r8, r0, r4
MobiClip_Code_020B4BE8:
    sub sb, r0, r4
MobiClip_Code_020B4BEC:
    add r0, r2, r6, asr #1
MobiClip_Code_020B4BF0:
    rsb r4, r6, r2, asr #1
MobiClip_Code_020B4BF4:
    add r2, sb, r4
MobiClip_Code_020B4BF8:
    sub r4, sb, r4
MobiClip_Code_020b4bfc:
    sub r6, r8, r0
MobiClip_Code_020b4c00:
    add r0, r8, r0
MobiClip_Code_020b4c04:
    add r8, r1, r7
MobiClip_Code_020B4C08:
    sub r8, r8, r3
MobiClip_Code_020b4c0c:
    sub r8, r8, r3, asr #1
MobiClip_Code_020b4c10:
    sub sb, r7, r1
MobiClip_Code_020b4c14:
    add sb, sb, r5
MobiClip_Code_020B4C18:
    add sb, sb, r5, asr #1
MobiClip_Code_020b4c1c:
    add r7, r7, r7, asr #1
MobiClip_Code_020b4c20:
    sub r7, r5, r7
MobiClip_Code_020b4c24:
    sub r7, r7, r3
MobiClip_Code_020B4C28:
    add r3, r3, r5
MobiClip_Code_020b4c2c:
    add r3, r3, r1
MobiClip_Code_020b4c30:
    add r3, r3, r1, asr #1
MobiClip_Code_020b4c34:
    add r1, r7, r3, asr #2
MobiClip_Code_020B4C38:
    sub r7, r3, r7, asr #2
MobiClip_Code_020b4c3c:
    add r3, r8, sb, asr #2
MobiClip_Code_020b4c40:
    rsb r5, sb, r8, asr #2
MobiClip_Code_020b4c44:
    add r0, r0, r7
MobiClip_Code_020B4C48:
    sub r7, r0, r7, lsl #1
MobiClip_Code_020b4c4c:
    add r8, r2, r5
MobiClip_Code_020b4c50:
    sub sb, r2, r5
MobiClip_Code_020b4c54:
    add r2, r4, r3
MobiClip_Code_020B4C58:
    sub r5, r4, r3
MobiClip_Code_020b4c5c:
    add r3, r6, r1
MobiClip_Code_020b4c60:
    sub r4, r6, r1
MobiClip_Code_020b4c64:
    mov r1, r8
MobiClip_Code_020B4C68:
    mov r6, sb
MobiClip_Code_020b4c6c:
    str r7, [fp, #0xe0]
MobiClip_Code_020b4c70:
    str r6, [fp, #0xc0]
MobiClip_Code_020b4c74:
    str r5, [fp, #0xa0]
MobiClip_Code_020B4C78:
    str r4, [fp, #0x80]
MobiClip_Code_020b4c7c:
    str r3, [fp, #0x60]
MobiClip_Code_020b4c80:
    str r2, [fp, #0x40]
MobiClip_Code_020b4c84:
    str r1, [fp, #0x20]
MobiClip_Code_020B4C88:
    str r0, [fp], #4
MobiClip_Code_020b4c8c:
    subs ip, ip, #1
MobiClip_Code_020b4c90:
    ldmne lr!, {r0, r1, r2, r3, r4, r5, r6, r7}
MobiClip_Code_020b4c94:
    bne MobiClip_Code_020B4BE4
MobiClip_Code_020B4C98:
    sub fp, fp, #0x20
MobiClip_Code_020B4C9C:
    ldr lr, [sp, #0x14]
MobiClip_Code_020B4CA0:
    mov ip, #8
MobiClip_Code_020B4CA4:
    ldr r8, [fp, #-0x270]
MobiClip_Code_020B4CA8:
    ldm fp!, {r0, r1, r2, r3, r4, r5, r6, r7}
MobiClip_Code_020B4CAC:
    add sb, r0, r4
MobiClip_Code_020B4CB0:
    sub sl, r0, r4
MobiClip_Code_020B4CB4:
    add r0, r2, r6, asr #1
MobiClip_Code_020B4CB8:
    rsb r4, r6, r2, asr #1
MobiClip_Code_020B4CBC:
    add r2, sl, r4
MobiClip_Code_020B4CC0:
    sub r4, sl, r4
MobiClip_Code_020B4CC4:
    sub r6, sb, r0
MobiClip_Code_020B4CC8:
    add r0, sb, r0
MobiClip_Code_020B4CCC:
    add sb, r1, r7
MobiClip_Code_020B4CD0:
    sub sb, sb, r3
MobiClip_Code_020B4CD4:
    sub sb, sb, r3, asr #1
MobiClip_Code_020B4CD8:
    sub sl, r7, r1
MobiClip_Code_020B4CDC:
    add sl, sl, r5
MobiClip_Code_020B4CE0:
    add sl, sl, r5, asr #1
MobiClip_Code_020B4CE4:
    add r7, r7, r7, asr #1
MobiClip_Code_020B4CE8:
    sub r7, r5, r7
MobiClip_Code_020B4CEC:
    sub r7, r7, r3
MobiClip_Code_020B4CF0:
    add r3, r3, r5
MobiClip_Code_020B4CF4:
    add r3, r3, r1
MobiClip_Code_020B4CF8:
    add r3, r3, r1, asr #1
MobiClip_Code_020B4CFC:
    add r1, r7, r3, asr #2
MobiClip_Code_020B4D00:
    sub r7, r3, r7, asr #2
MobiClip_Code_020B4D04:
    add r3, sb, sl, asr #2
MobiClip_Code_020B4D08:
    rsb r5, sl, sb, asr #2
MobiClip_Code_020B4D0C:
    add r0, r0, r7
MobiClip_Code_020B4D10:
    sub r7, r0, r7, lsl #1
MobiClip_Code_020B4D14:
    add sb, r2, r5
MobiClip_Code_020B4D18:
    sub sl, r2, r5
MobiClip_Code_020B4D1C:
    add r2, r4, r3
MobiClip_Code_020B4D20:
    sub r5, r4, r3
MobiClip_Code_020B4D24:
    add r3, r6, r1
MobiClip_Code_020B4D28:
    sub r4, r6, r1
MobiClip_Code_020B4D2C:
    mov r1, sb
MobiClip_Code_020B4D30:
    mov r6, sl
MobiClip_Code_020B4D34:
    ldrb sb, [lr]
MobiClip_Code_020B4D38:
    ldrb sl, [lr, #1]
MobiClip_Code_020B4D3C:
    add sb, sb, r0, asr #6
MobiClip_Code_020B4D40:
    ldrb sb, [r8, sb]
MobiClip_Code_020B4D44:
    ldrb r0, [lr, #2]
MobiClip_Code_020B4D48:
    add sl, sl, r1, asr #6
MobiClip_Code_020B4D4C:
    ldrb sl, [r8, sl]
MobiClip_Code_020B4D50:
    strb sb, [lr]
MobiClip_Code_020B4D54:
    ldrb r1, [lr, #3]
MobiClip_Code_020B4D58:
    add r0, r0, r2, asr #6
MobiClip_Code_020B4D5C:
    ldrb r0, [r8, r0]
MobiClip_Code_020B4D60:
    strb sl, [lr, #1]
MobiClip_Code_020B4D64:
    ldrb r2, [lr, #4]
MobiClip_Code_020B4D68:
    add r1, r1, r3, asr #6
MobiClip_Code_020B4D6C:
    ldrb r1, [r8, r1]
MobiClip_Code_020B4D70:
    strb r0, [lr, #2]
MobiClip_Code_020B4D74:
    ldrb r3, [lr, #5]
MobiClip_Code_020B4D78:
    add r2, r2, r4, asr #6
MobiClip_Code_020B4D7C:
    ldrb r2, [r8, r2]
MobiClip_Code_020B4D80:
    strb r1, [lr, #3]
MobiClip_Code_020B4D84:
    ldrb r4, [lr, #6]
MobiClip_Code_020B4D88:
    add r3, r3, r5, asr #6
MobiClip_Code_020B4D8C:
    ldrb r3, [r8, r3]
MobiClip_Code_020B4D90:
    strb r2, [lr, #4]
MobiClip_Code_020B4D94:
    ldrb r5, [lr, #7]
MobiClip_Code_020B4D98:
    add r4, r4, r6, asr #6
MobiClip_Code_020B4D9C:
    ldrb r4, [r8, r4]
MobiClip_Code_020B4DA0:
    strb r3, [lr, #5]
MobiClip_Code_020B4DA4:
    add r5, r5, r7, asr #6
MobiClip_Code_020B4DA8:
    ldrb r5, [r8, r5]
MobiClip_Code_020B4DAC:
    strb r4, [lr, #6]
MobiClip_Code_020B4DB0:
    subs ip, ip, #1
MobiClip_Code_020B4DB4:
    strb r5, [lr, #7]
MobiClip_Code_020B4DB8:
    add lr, lr, #0x100
MobiClip_Code_020B4DBC:
    bne MobiClip_Code_020B4CA8
MobiClip_Code_020B4DC0:
    pop {r0, r1, r2, r3, sl, fp, ip, pc}
MobiClip_Code_020B4DC4:
    push {r0, r1, r2, r3}
MobiClip_Code_020B4DC8:
    add lr, r0, #0x1b4
MobiClip_Code_020B4DCC:
    add fp, lr, #0x100
MobiClip_Code_020B4DD0:
    ldm lr!, {r0, r1, r2, r3}
MobiClip_Code_020B4DD4:
    add r0, r0, #0x20
MobiClip_Code_020B4DD8:
    mov ip, #4
MobiClip_Code_020B4DDC:
    add lr, lr, #0x10
MobiClip_Code_020B4DE0:
    sub r4, r0, r2, asr #1
MobiClip_Code_020B4DE4:
    sub r6, r0, r2
MobiClip_Code_020B4DE8:
    add sb, r0, r2, asr #1
MobiClip_Code_020B4DEC:
    add r0, r0, r2
MobiClip_Code_020B4DF0:
    sub r8, r1, r3
MobiClip_Code_020B4DF4:
    sub r8, r8, r3, asr #1
MobiClip_Code_020B4DF8:
    add r7, r3, r1
MobiClip_Code_020B4DFC:
    add r7, r7, r1, asr #1
MobiClip_Code_020B4E00:
    rsb r2, r3, #0
MobiClip_Code_020B4E04:
    add r5, r1, r8, asr #2
MobiClip_Code_020B4E08:
    rsb r3, r1, #0
MobiClip_Code_020B4E0C:
    add r3, r8, r3, asr #2
MobiClip_Code_020B4E10:
    add r1, r2, r7, asr #2
MobiClip_Code_020B4E14:
    sub r7, r7, r2, asr #2
MobiClip_Code_020B4E18:
    add r0, r0, r7
MobiClip_Code_020B4E1C:
    sub r7, r0, r7, lsl #1
MobiClip_Code_020B4E20:
    add r8, sb, r5
MobiClip_Code_020B4E24:
    sub sb, sb, r5
MobiClip_Code_020B4E28:
    add r2, r4, r3
MobiClip_Code_020B4E2C:
    sub r5, r4, r3
MobiClip_Code_020B4E30:
    add r3, r6, r1
MobiClip_Code_020B4E34:
    sub r4, r6, r1
MobiClip_Code_020B4E38:
    mov r1, r8
MobiClip_Code_020B4E3C:
    mov r6, sb
MobiClip_Code_020B4E40:
    str r7, [fp, #0x70]
MobiClip_Code_020B4E44:
    str r6, [fp, #0x60]
MobiClip_Code_020B4E48:
    str r5, [fp, #0x50]
MobiClip_Code_020B4E4C:
    str r4, [fp, #0x40]
MobiClip_Code_020B4E50:
    str r3, [fp, #0x30]
MobiClip_Code_020B4E54:
    str r2, [fp, #0x20]
MobiClip_Code_020B4E58:
    str r1, [fp, #0x10]
MobiClip_Code_020B4E5C:
    str r0, [fp], #4
MobiClip_Code_020B4E60:
    subs ip, ip, #1
MobiClip_Code_020B4E64:
    ldmne lr!, {r0, r1, r2, r3}
MobiClip_Code_020B4E68:
    bne MobiClip_Code_020B4DDC
MobiClip_Code_020B4E6C:
    sub fp, fp, #0x10
MobiClip_Code_020B4E70:
    ldr lr, [sp, #0x14]
MobiClip_Code_020B4E74:
    mov ip, #8
MobiClip_Code_020B4E78:
    ldr r8, [fp, #-0x270]
MobiClip_Code_020B4E7C:
    ldm fp!, {r0, r1, r2, r3}
MobiClip_Code_020B4E80:
    sub r4, r0, r2, asr #1
MobiClip_Code_020B4E84:
    sub r6, r0, r2
MobiClip_Code_020B4E88:
    add sl, r0, r2, asr #1
MobiClip_Code_020B4E8C:
    add r0, r0, r2
MobiClip_Code_020B4E90:
    sub sb, r1, r3
MobiClip_Code_020B4E94:
    sub sb, sb, r3, asr #1
MobiClip_Code_020B4E98:
    add r7, r3, r1
MobiClip_Code_020B4E9C:
    add r7, r7, r1, asr #1
MobiClip_Code_020B4EA0:
    rsb r2, r3, #0
MobiClip_Code_020B4EA4:
    add r5, r1, sb, asr #2
MobiClip_Code_020B4EA8:
    rsb r3, r1, #0
MobiClip_Code_020B4EAC:
    add r3, sb, r3, asr #2
MobiClip_Code_020B4EB0:
    add r1, r2, r7, asr #2
MobiClip_Code_020B4EB4:
    sub r7, r7, r2, asr #2
MobiClip_Code_020B4EB8:
    add r0, r0, r7
MobiClip_Code_020B4EBC:
    sub r7, r0, r7, lsl #1
MobiClip_Code_020B4EC0:
    add sb, sl, r5
MobiClip_Code_020B4EC4:
    sub sl, sl, r5
MobiClip_Code_020B4EC8:
    add r2, r4, r3
MobiClip_Code_020B4ECC:
    sub r5, r4, r3
MobiClip_Code_020B4ED0:
    add r3, r6, r1
MobiClip_Code_020B4ED4:
    sub r4, r6, r1
MobiClip_Code_020B4ED8:
    mov r1, sb
MobiClip_Code_020B4EDC:
    mov r6, sl
MobiClip_Code_020B4EE0:
    ldrb sb, [lr]
MobiClip_Code_020B4EE4:
    ldrb sl, [lr, #1]
MobiClip_Code_020B4EE8:
    add sb, sb, r0, asr #6
MobiClip_Code_020B4EEC:
    ldrb sb, [r8, sb]
MobiClip_Code_020B4EF0:
    ldrb r0, [lr, #2]
MobiClip_Code_020B4EF4:
    add sl, sl, r1, asr #6
MobiClip_Code_020B4EF8:
    ldrb sl, [r8, sl]
MobiClip_Code_020B4EFC:
    strb sb, [lr]
MobiClip_Code_020B4F00:
    ldrb r1, [lr, #3]
MobiClip_Code_020B4F04:
    add r0, r0, r2, asr #6
MobiClip_Code_020B4F08:
    ldrb r0, [r8, r0]
MobiClip_Code_020B4F0C:
    strb sl, [lr, #1]
MobiClip_Code_020B4F10:
    ldrb r2, [lr, #4]
MobiClip_Code_020B4F14:
    add r1, r1, r3, asr #6
MobiClip_Code_020B4F18:
    ldrb r1, [r8, r1]
MobiClip_Code_020B4F1C:
    strb r0, [lr, #2]
MobiClip_Code_020B4F20:
    ldrb r3, [lr, #5]
MobiClip_Code_020B4F24:
    add r2, r2, r4, asr #6
MobiClip_Code_020B4F28:
    ldrb r2, [r8, r2]
MobiClip_Code_020B4F2C:
    strb r1, [lr, #3]
MobiClip_Code_020B4F30:
    ldrb r4, [lr, #6]
MobiClip_Code_020B4F34:
    add r3, r3, r5, asr #6
MobiClip_Code_020B4F38:
    ldrb r3, [r8, r3]
MobiClip_Code_020B4F3C:
    strb r2, [lr, #4]
MobiClip_Code_020B4F40:
    ldrb r5, [lr, #7]
MobiClip_Code_020B4F44:
    add r4, r4, r6, asr #6
MobiClip_Code_020B4F48:
    ldrb r4, [r8, r4]
MobiClip_Code_020B4F4C:
    strb r3, [lr, #5]
MobiClip_Code_020B4F50:
    add r5, r5, r7, asr #6
MobiClip_Code_020B4F54:
    ldrb r5, [r8, r5]
MobiClip_Code_020B4F58:
    strb r4, [lr, #6]
MobiClip_Code_020B4F5C:
    subs ip, ip, #1
MobiClip_Code_020B4F60:
    strb r5, [lr, #7]
MobiClip_Code_020B4F64:
    add lr, lr, #0x100
MobiClip_Code_020B4F68:
    bne MobiClip_Code_020B4E7C
MobiClip_Code_020B4F6C:
    pop {r0, r1, r2, r3, sl, fp, ip, pc}
MobiClip_Code_020B4F70:
    push {r0, r1, r2, r3}
MobiClip_Code_020B4F74:
    add lr, r0, #0x1b4
MobiClip_Code_020B4F78:
    ldm lr, {r8, sb}
MobiClip_Code_020B4F7C:
    ldr sl, [lr, #0x20]
MobiClip_Code_020B4F80:
    add r8, r8, #0x20
MobiClip_Code_020B4F84:
    add r7, sb, sb, asr #1
MobiClip_Code_020B4F88:
    asr fp, r7, #2
MobiClip_Code_020B4F8C:
    rsb r3, sb, #0
MobiClip_Code_020B4F90:
    add r3, sb, r3, asr #2
MobiClip_Code_020B4F94:
    add r5, sb, sb, asr #2
MobiClip_Code_020B4F98:
    add r0, r8, r7
MobiClip_Code_020B4F9C:
    sub r7, r8, r7
MobiClip_Code_020B4FA0:
    add r1, r8, r5
MobiClip_Code_020B4FA4:
    sub r6, r8, r5
MobiClip_Code_020B4FA8:
    add r2, r8, r3
MobiClip_Code_020B4FAC:
    sub r5, r8, r3
MobiClip_Code_020B4FB0:
    add r3, r8, fp
MobiClip_Code_020B4FB4:
    sub r4, r8, fp
MobiClip_Code_020B4FB8:
    stm lr, {r0, r1, r2, r3, r4, r5, r6, r7}
MobiClip_Code_020B4FBC:
    add r7, sl, sl, asr #1
MobiClip_Code_020B4FC0:
    asr r1, r7, #2
MobiClip_Code_020B4FC4:
    rsb r3, sl, #0
MobiClip_Code_020B4FC8:
    add r3, sl, r3, asr #2
MobiClip_Code_020B4FCC:
    add r5, sl, sl, asr #2
MobiClip_Code_020B4FD0:
    ldr fp, [sp, #0x14]
MobiClip_Code_020B4FD4:
    mov ip, #8
MobiClip_Code_020B4FD8:
    ldr r8, [lr, #-0x170]
MobiClip_Code_020B4FDC:
    ldr r0, [lr], #4
MobiClip_Code_020B4FE0:
    ldrb sb, [fp]
MobiClip_Code_020B4FE4:
    ldrb sl, [fp, #1]
MobiClip_Code_020B4FE8:
    add r2, r0, r7
MobiClip_Code_020B4FEC:
    add sb, sb, r2, asr #6
MobiClip_Code_020B4FF0:
    ldrb sb, [r8, sb]
MobiClip_Code_020B4FF4:
    ldrb r4, [fp, #2]
MobiClip_Code_020B4FF8:
    add r2, r0, r5
MobiClip_Code_020B4FFC:
    add sl, sl, r2, asr #6
MobiClip_Code_020B5000:
    ldrb sl, [r8, sl]
MobiClip_Code_020B5004:
    strb sb, [fp]
MobiClip_Code_020B5008:
    ldrb r6, [fp, #3]
MobiClip_Code_020B500C:
    add r2, r0, r3
MobiClip_Code_020B5010:
    add r4, r4, r2, asr #6
MobiClip_Code_020B5014:
    ldrb r4, [r8, r4]
MobiClip_Code_020B5018:
    strb sl, [fp, #1]
MobiClip_Code_020B501C:
    ldrb sb, [fp, #4]
MobiClip_Code_020B5020:
    add r2, r0, r1
MobiClip_Code_020B5024:
    add r6, r6, r2, asr #6
MobiClip_Code_020B5028:
    ldrb r6, [r8, r6]
MobiClip_Code_020B502C:
    strb r4, [fp, #2]
MobiClip_Code_020B5030:
    ldrb sl, [fp, #5]
MobiClip_Code_020B5034:
    sub r2, r0, r1
MobiClip_Code_020B5038:
    add sb, sb, r2, asr #6
MobiClip_Code_020B503C:
    ldrb sb, [r8, sb]
MobiClip_Code_020B5040:
    strb r6, [fp, #3]
MobiClip_Code_020B5044:
    ldrb r4, [fp, #6]
MobiClip_Code_020B5048:
    sub r2, r0, r3
MobiClip_Code_020B504C:
    add sl, sl, r2, asr #6
MobiClip_Code_020B5050:
    ldrb sl, [r8, sl]
MobiClip_Code_020B5054:
    strb sb, [fp, #4]
MobiClip_Code_020B5058:
    ldrb r6, [fp, #7]
MobiClip_Code_020B505C:
    sub r2, r0, r5
MobiClip_Code_020B5060:
    add r4, r4, r2, asr #6
MobiClip_Code_020B5064:
    ldrb r4, [r8, r4]
MobiClip_Code_020B5068:
    strb sl, [fp, #5]
MobiClip_Code_020B506C:
    sub r2, r0, r7
MobiClip_Code_020B5070:
    add r6, r6, r2, asr #6
MobiClip_Code_020B5074:
    ldrb r6, [r8, r6]
MobiClip_Code_020B5078:
    strb r4, [fp, #6]
MobiClip_Code_020B507C:
    subs ip, ip, #1
MobiClip_Code_020B5080:
    strb r6, [fp, #7]
MobiClip_Code_020B5084:
    add fp, fp, #0x100
MobiClip_Code_020B5088:
    bne MobiClip_Code_020B4FDC
MobiClip_Code_020B508C:
    pop {r0, r1, r2, r3, sl, fp, ip, pc}
MobiClip_Code_020B5090:
    push {r0, r1, r2, r3}
MobiClip_Code_020B5094:
    add lr, r0, #0x1b4
MobiClip_Code_020B5098:
    ldr sb, [lr]
MobiClip_Code_020B509C:
    add sb, sb, #0x20
MobiClip_Code_020B50A0:
    asr sb, sb, #6
MobiClip_Code_020B50A4:
    ldr lr, [sp, #0x14]
MobiClip_Code_020B50A8:
    mov ip, #8
MobiClip_Code_020B50AC:
    ldr r8, [r0, #0x44]
MobiClip_Code_020B50B0:
    ldrb r0, [lr]
MobiClip_Code_020B50B4:
    ldrb r1, [lr, #1]
MobiClip_Code_020B50B8:
    ldrb r2, [lr, #2]
MobiClip_Code_020B50BC:
    ldrb r3, [lr, #3]
MobiClip_Code_020B50C0:
    ldrb r4, [lr, #4]
MobiClip_Code_020B50C4:
    ldrb r5, [lr, #5]
MobiClip_Code_020B50C8:
    ldrb r6, [lr, #6]
MobiClip_Code_020B50CC:
    ldrb r7, [lr, #7]
MobiClip_Code_020B50D0:
    add r0, r0, sb
MobiClip_Code_020B50D4:
    add r1, r1, sb
MobiClip_Code_020B50D8:
    add r2, r2, sb
MobiClip_Code_020B50DC:
    add r3, r3, sb
MobiClip_Code_020B50E0:
    add r4, r4, sb
MobiClip_Code_020B50E4:
    add r5, r5, sb
MobiClip_Code_020B50E8:
    add r6, r6, sb
MobiClip_Code_020B50EC:
    add r7, r7, sb
MobiClip_Code_020B50F0:
    ldrb r0, [r8, r0]
MobiClip_Code_020B50F4:
    ldrb r1, [r8, r1]
MobiClip_Code_020B50F8:
    ldrb r2, [r8, r2]
MobiClip_Code_020B50FC:
    ldrb r3, [r8, r3]
MobiClip_Code_020B5100:
    ldrb r4, [r8, r4]
MobiClip_Code_020B5104:
    ldrb r5, [r8, r5]
MobiClip_Code_020B5108:
    ldrb r6, [r8, r6]
MobiClip_Code_020B510C:
    ldrb r7, [r8, r7]
MobiClip_Code_020B5110:
    strb r7, [lr, #7]
MobiClip_Code_020B5114:
    strb r6, [lr, #6]
MobiClip_Code_020B5118:
    strb r5, [lr, #5]
MobiClip_Code_020B511C:
    strb r4, [lr, #4]
MobiClip_Code_020B5120:
    strb r3, [lr, #3]
MobiClip_Code_020B5124:
    strb r2, [lr, #2]
MobiClip_Code_020B5128:
    strb r1, [lr, #1]
MobiClip_Code_020B512C:
    strb r0, [lr], #0x100
MobiClip_Code_020B5130:
    subs ip, ip, #1
MobiClip_Code_020B5134:
    bne MobiClip_Code_020B50B0
MobiClip_Code_020B5138:
    pop {r0, r1, r2, r3, sl, fp, ip, pc}
MobiClip_Code_020B513C:
    push {r0, r1, r2, r3}
MobiClip_Code_020B5140:
    add lr, r0, #0x1b4
MobiClip_Code_020B5144:
    add fp, lr, #0x40
MobiClip_Code_020B5148:
    ldm lr!, {r0, r1, r2, r3}
MobiClip_Code_020B514C:
    add r0, r0, #0x20
MobiClip_Code_020B5150:
    mov ip, #4
MobiClip_Code_020B5154:
    add r0, r0, r2
MobiClip_Code_020B5158:
    sub r2, r0, r2, lsl #1
MobiClip_Code_020B515C:
    rsb r8, r3, r1, asr #1
MobiClip_Code_020B5160:
    add sb, r1, r3, asr #1
MobiClip_Code_020B5164:
    sub r3, r0, sb
MobiClip_Code_020B5168:
    add r0, r0, sb
MobiClip_Code_020B516C:
    add r1, r2, r8
MobiClip_Code_020B5170:
    sub r2, r2, r8
MobiClip_Code_020B5174:
    str r3, [fp, #0x30]
MobiClip_Code_020B5178:
    str r2, [fp, #0x20]
MobiClip_Code_020B517C:
    str r1, [fp, #0x10]
MobiClip_Code_020B5180:
    str r0, [fp], #4
MobiClip_Code_020B5184:
    subs ip, ip, #1
MobiClip_Code_020B5188:
    ldmne lr!, {r0, r1, r2, r3}
MobiClip_Code_020B518C:
    bne MobiClip_Code_020B5154
MobiClip_Code_020B5190:
    sub fp, fp, #0x10
MobiClip_Code_020B5194:
    ldr lr, [sp, #0x14]
MobiClip_Code_020B5198:
    mov ip, #4
MobiClip_Code_020B519C:
    ldr r8, [fp, #-0x1b0]
MobiClip_Code_020B51A0:
    ldm fp!, {r0, r1, r2, r3}
MobiClip_Code_020B51A4:
    add r0, r0, r2
MobiClip_Code_020B51A8:
    sub r2, r0, r2, lsl #1
MobiClip_Code_020B51AC:
    rsb sb, r3, r1, asr #1
MobiClip_Code_020B51B0:
    add sl, r1, r3, asr #1
MobiClip_Code_020B51B4:
    sub r3, r0, sl
MobiClip_Code_020B51B8:
    add r0, r0, sl
MobiClip_Code_020B51BC:
    add r1, r2, sb
MobiClip_Code_020B51C0:
    sub r2, r2, sb
MobiClip_Code_020B51C4:
    ldrb r4, [lr]
MobiClip_Code_020B51C8:
    ldrb r5, [lr, #1]
MobiClip_Code_020B51CC:
    ldrb r6, [lr, #2]
MobiClip_Code_020B51D0:
    ldrb r7, [lr, #3]
MobiClip_Code_020B51D4:
    add r4, r4, r0, asr #6
MobiClip_Code_020B51D8:
    add r5, r5, r1, asr #6
MobiClip_Code_020B51DC:
    add r6, r6, r2, asr #6
MobiClip_Code_020B51E0:
    add r7, r7, r3, asr #6
MobiClip_Code_020B51E4:
    ldrb r4, [r8, r4]
MobiClip_Code_020B51E8:
    ldrb r5, [r8, r5]
MobiClip_Code_020B51EC:
    ldrb r6, [r8, r6]
MobiClip_Code_020B51F0:
    ldrb r7, [r8, r7]
MobiClip_Code_020B51F4:
    strb r7, [lr, #3]
MobiClip_Code_020B51F8:
    strb r6, [lr, #2]
MobiClip_Code_020B51FC:
    strb r5, [lr, #1]
MobiClip_Code_020B5200:
    strb r4, [lr], #0x100
MobiClip_Code_020B5204:
    subs ip, ip, #1
MobiClip_Code_020B5208:
    bne MobiClip_Code_020B51A0
MobiClip_Code_020B520C:
    pop {r0, r1, r2, r3, sl, fp, ip, pc}
MobiClip_Code_020B5210:
    add lr, r0, #0x1b4
MobiClip_Code_020B5214:
    ldr sb, [lr]
MobiClip_Code_020B5218:
    add sb, sb, #0x20
MobiClip_Code_020B521C:
    asr sb, sb, #6
MobiClip_Code_020B5220:
    ldr lr, [sp, #4]
MobiClip_Code_020B5224:
    mov ip, #4
MobiClip_Code_020B5228:
    ldr r8, [r0, #0x44]
MobiClip_Code_020B522C:
    ldrb r4, [lr]
MobiClip_Code_020B5230:
    ldrb r5, [lr, #1]
MobiClip_Code_020B5234:
    ldrb r6, [lr, #2]
MobiClip_Code_020B5238:
    ldrb r7, [lr, #3]
MobiClip_Code_020B523C:
    add r4, r4, sb
MobiClip_Code_020B5240:
    add r5, r5, sb
MobiClip_Code_020B5244:
    add r6, r6, sb
MobiClip_Code_020B5248:
    add r7, r7, sb
MobiClip_Code_020B524C:
    ldrb r4, [r8, r4]
MobiClip_Code_020B5250:
    ldrb r5, [r8, r5]
MobiClip_Code_020B5254:
    ldrb r6, [r8, r6]
MobiClip_Code_020B5258:
    ldrb r7, [r8, r7]
MobiClip_Code_020B525C:
    strb r7, [lr, #3]
MobiClip_Code_020B5260:
    strb r6, [lr, #2]
MobiClip_Code_020B5264:
    strb r5, [lr, #1]
MobiClip_Code_020B5268:
    strb r4, [lr], #0x100
MobiClip_Code_020B526C:
    subs ip, ip, #1
MobiClip_Code_020B5270:
    bne MobiClip_Code_020B522C
MobiClip_Code_020B5274:
    pop {sl, fp, ip, pc}
    /* semantic constants 0x02090f7c..0x020910fc */
    .global gMobiClipQuant8BaseMatrices
    .type gMobiClipQuant8BaseMatrices, %object
gMobiClipQuant8BaseMatrices:
    .byte 0x14, 0x13, 0x13, 0x19, 0x12, 0x19, 0x13, 0x18, 0x18, 0x13, 0x14, 0x12, 0x20, 0x12, 0x14, 0x13
    .byte 0x13, 0x18, 0x18, 0x13, 0x13, 0x19, 0x12, 0x19, 0x12, 0x19, 0x12, 0x19, 0x13, 0x18, 0x18, 0x13
    .byte 0x13, 0x18, 0x18, 0x13, 0x12, 0x20, 0x12, 0x14, 0x12, 0x20, 0x12, 0x18, 0x18, 0x13, 0x13, 0x18
    .byte 0x18, 0x12, 0x19, 0x12, 0x19, 0x12, 0x13, 0x18, 0x18, 0x13, 0x12, 0x20, 0x12, 0x18, 0x18, 0x12
    .byte 0x16, 0x15, 0x15, 0x1c, 0x13, 0x1c, 0x15, 0x1a, 0x1a, 0x15, 0x16, 0x13, 0x23, 0x13, 0x16, 0x15
    .byte 0x15, 0x1a, 0x1a, 0x15, 0x15, 0x1c, 0x13, 0x1c, 0x13, 0x1c, 0x13, 0x1c, 0x15, 0x1a, 0x1a, 0x15
    .byte 0x15, 0x1a, 0x1a, 0x15, 0x13, 0x23, 0x13, 0x16, 0x13, 0x23, 0x13, 0x1a, 0x1a, 0x15, 0x15, 0x1a
    .byte 0x1a, 0x13, 0x1c, 0x13, 0x1c, 0x13, 0x15, 0x1a, 0x1a, 0x15, 0x13, 0x23, 0x13, 0x1a, 0x1a, 0x13
    .byte 0x1a, 0x18, 0x18, 0x21, 0x17, 0x21, 0x18, 0x1f, 0x1f, 0x18, 0x1a, 0x17, 0x2a, 0x17, 0x1a, 0x18
    .byte 0x18, 0x1f, 0x1f, 0x18, 0x18, 0x21, 0x17, 0x21, 0x17, 0x21, 0x17, 0x21, 0x18, 0x1f, 0x1f, 0x18
    .byte 0x18, 0x1f, 0x1f, 0x18, 0x17, 0x2a, 0x17, 0x1a, 0x17, 0x2a, 0x17, 0x1f, 0x1f, 0x18, 0x18, 0x1f
    .byte 0x1f, 0x17, 0x21, 0x17, 0x21, 0x17, 0x18, 0x1f, 0x1f, 0x18, 0x17, 0x2a, 0x17, 0x1f, 0x1f, 0x17
    .byte 0x1c, 0x1a, 0x1a, 0x23, 0x19, 0x23, 0x1a, 0x21, 0x21, 0x1a, 0x1c, 0x19, 0x2d, 0x19, 0x1c, 0x1a
    .byte 0x1a, 0x21, 0x21, 0x1a, 0x1a, 0x23, 0x19, 0x23, 0x19, 0x23, 0x19, 0x23, 0x1a, 0x21, 0x21, 0x1a
    .byte 0x1a, 0x21, 0x21, 0x1a, 0x19, 0x2d, 0x19, 0x1c, 0x19, 0x2d, 0x19, 0x21, 0x21, 0x1a, 0x1a, 0x21
    .byte 0x21, 0x19, 0x23, 0x19, 0x23, 0x19, 0x1a, 0x21, 0x21, 0x1a, 0x19, 0x2d, 0x19, 0x21, 0x21, 0x19
    .byte 0x20, 0x1e, 0x1e, 0x28, 0x1c, 0x28, 0x1e, 0x26, 0x26, 0x1e, 0x20, 0x1c, 0x33, 0x1c, 0x20, 0x1e
    .byte 0x1e, 0x26, 0x26, 0x1e, 0x1e, 0x28, 0x1c, 0x28, 0x1c, 0x28, 0x1c, 0x28, 0x1e, 0x26, 0x26, 0x1e
    .byte 0x1e, 0x26, 0x26, 0x1e, 0x1c, 0x33, 0x1c, 0x20, 0x1c, 0x33, 0x1c, 0x26, 0x26, 0x1e, 0x1e, 0x26
    .byte 0x26, 0x1c, 0x28, 0x1c, 0x28, 0x1c, 0x1e, 0x26, 0x26, 0x1e, 0x1c, 0x33, 0x1c, 0x26, 0x26, 0x1c
    .byte 0x24, 0x22, 0x22, 0x2e, 0x20, 0x2e, 0x22, 0x2b, 0x2b, 0x22, 0x24, 0x20, 0x3a, 0x20, 0x24, 0x22
    .byte 0x22, 0x2b, 0x2b, 0x22, 0x22, 0x2e, 0x20, 0x2e, 0x20, 0x2e, 0x20, 0x2e, 0x22, 0x2b, 0x2b, 0x22
    .byte 0x22, 0x2b, 0x2b, 0x22, 0x20, 0x3a, 0x20, 0x24, 0x20, 0x3a, 0x20, 0x2b, 0x2b, 0x22, 0x22, 0x2b
    .byte 0x2b, 0x20, 0x2e, 0x20, 0x2e, 0x20, 0x22, 0x2b, 0x2b, 0x22, 0x20, 0x3a, 0x20, 0x2b, 0x2b, 0x20
    /* semantic constants 0x020910fc..0x0209113c */
    .global gMobiClipScan8
    .type gMobiClipScan8, %object
gMobiClipScan8:
    .byte 0x00, 0x01, 0x08, 0x10, 0x09, 0x02, 0x03, 0x0a, 0x11, 0x18, 0x20, 0x19, 0x12, 0x0b, 0x04, 0x05
    .byte 0x0c, 0x13, 0x1a, 0x21, 0x28, 0x30, 0x29, 0x22, 0x1b, 0x14, 0x0d, 0x06, 0x07, 0x0e, 0x15, 0x1c
    .byte 0x23, 0x2a, 0x31, 0x38, 0x39, 0x32, 0x2b, 0x24, 0x1d, 0x16, 0x0f, 0x17, 0x1e, 0x25, 0x2c, 0x33
    .byte 0x3a, 0x3b, 0x34, 0x2d, 0x26, 0x1f, 0x27, 0x2e, 0x35, 0x3c, 0x3d, 0x36, 0x2f, 0x37, 0x3e, 0x3f
    /* semantic constants 0x0209113c..0x0209119c */
    .global gMobiClipQuant4BaseMatrices
    .type gMobiClipQuant4BaseMatrices, %object
gMobiClipQuant4BaseMatrices:
    .byte 0x0a, 0x0d, 0x0d, 0x0a, 0x10, 0x0a, 0x0d, 0x0d, 0x0d, 0x0d, 0x10, 0x0a, 0x10, 0x0d, 0x0d, 0x10
    .byte 0x0b, 0x0e, 0x0e, 0x0b, 0x12, 0x0b, 0x0e, 0x0e, 0x0e, 0x0e, 0x12, 0x0b, 0x12, 0x0e, 0x0e, 0x12
    .byte 0x0d, 0x10, 0x10, 0x0d, 0x14, 0x0d, 0x10, 0x10, 0x10, 0x10, 0x14, 0x0d, 0x14, 0x10, 0x10, 0x14
    .byte 0x0e, 0x12, 0x12, 0x0e, 0x17, 0x0e, 0x12, 0x12, 0x12, 0x12, 0x17, 0x0e, 0x17, 0x12, 0x12, 0x17
    .byte 0x10, 0x14, 0x14, 0x10, 0x19, 0x10, 0x14, 0x14, 0x14, 0x14, 0x19, 0x10, 0x19, 0x14, 0x14, 0x19
    .byte 0x12, 0x17, 0x17, 0x12, 0x1d, 0x12, 0x17, 0x17, 0x17, 0x17, 0x1d, 0x12, 0x1d, 0x17, 0x17, 0x1d
    /* semantic constants 0x0209119c..0x020911ac */
    .global gMobiClipScan4
    .type gMobiClipScan4, %object
gMobiClipScan4:
    .byte 0x00, 0x04, 0x01, 0x02, 0x05, 0x08, 0x0c, 0x09, 0x06, 0x03, 0x07, 0x0a, 0x0d, 0x0e, 0x0b, 0x0f
    /* semantic constants 0x020911ac..0x020911e2 */
    .global gMobiClipQpShift
    .type gMobiClipQpShift, %object
gMobiClipQpShift:
    .byte 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02
    .byte 0x02, 0x02, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05
    .byte 0x05, 0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07
    .byte 0x08, 0x08, 0x08, 0x08, 0x08, 0x08
    /* semantic constants 0x020911e2..0x02091218 */
    .global gMobiClipQpMatrixSelector
    .type gMobiClipQpMatrixSelector, %object
gMobiClipQpMatrixSelector:
    .byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01, 0x02, 0x03
    .byte 0x04, 0x05, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01
    .byte 0x02, 0x03, 0x04, 0x05, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05
    .byte 0x00, 0x01, 0x02, 0x03, 0x04, 0x05
MobiClip_Code_020b5514:
    str r4, [r0, #0x3b4]
MobiClip_Code_020B5518:
    sub r5, pc, #0x78
MobiClip_Code_020b551c:
    ldrb r6, [r5, r4]
MobiClip_Code_020b5520:
    add r6, r6, #8
MobiClip_Code_020b5524:
    sub r5, pc, #0x4e
MobiClip_Code_020B5528:
    ldrb r5, [r5, r4]
MobiClip_Code_020b552c:
    sub r4, pc, #0xfc
MobiClip_Code_020b5530:
    add r4, r4, r5, lsl #4
MobiClip_Code_020b5534:
    sub r7, pc, #0xa4
MobiClip_Code_020B5538:
    add r8, r0, #0x174
MobiClip_Code_020b553c:
    mov sb, #0x10
MobiClip_Code_020b5540:
    ldrb sl, [r4], #1
MobiClip_Code_020b5544:
    ldrb fp, [r7], #1
MobiClip_Code_020B5548:
    orr fp, fp, sl, lsl r6
MobiClip_Code_020b554c:
    str fp, [r8], #4
MobiClip_Code_020b5550:
    subs sb, sb, #1
MobiClip_Code_020b5554:
    bne MobiClip_Code_020b5540
MobiClip_Code_020B5558:
    sub r6, r6, #2
MobiClip_Code_020b555c:
    sub r4, pc, #0x2ec
MobiClip_Code_020b5560:
    add r4, r4, r5, lsl #6
MobiClip_Code_020b5564:
    sub r7, pc, #0x174
MobiClip_Code_020B5568:
    add r8, r0, #0x74
MobiClip_Code_020b556c:
    mov sb, #0x40
MobiClip_Code_020b5570:
    ldrb sl, [r4], #1
MobiClip_Code_020b5574:
    ldrb fp, [r7], #1
MobiClip_Code_020B5578:
    orr fp, fp, sl, lsl r6
MobiClip_Code_020b557c:
    str fp, [r8], #4
MobiClip_Code_020b5580:
    subs sb, sb, #1
MobiClip_Code_020b5584:
    bne MobiClip_Code_020b5570
MobiClip_Code_020B5588:
    add r4, r0, #0x4c
MobiClip_Code_020b558c:
    mov r5, #9
MobiClip_Code_020b5590:
    strb r5, [r4, #1]
MobiClip_Code_020b5594:
    strb r5, [r4, #2]
MobiClip_Code_020B5598:
    strb r5, [r4, #3]
MobiClip_Code_020B559C:
    strb r5, [r4, #4]
MobiClip_Code_020B55A0:
    strb r5, [r4, #8]
MobiClip_Code_020B55A4:
    strb r5, [r4, #0x10]
MobiClip_Code_020B55A8:
    strb r5, [r4, #0x18]
MobiClip_Code_020B55AC:
    strb r5, [r4, #0x20]
MobiClip_Code_020B55B0:
    mov pc, lr
MobiClip_Code_020B55B4:
    ldm r0, {r3, r4, r7, r8}
MobiClip_Code_020B55B8:
    add r0, r0, #0x100
MobiClip_Code_020B55BC:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_020B55C0:
    add r1, r1, #0x100
MobiClip_Code_020B55C4:
    subs r2, r2, #1
MobiClip_Code_020B55C8:
    bne MobiClip_Code_020B55B4
MobiClip_Code_020B55CC:
    mov pc, lr
MobiClip_Code_020B55D0:
    push {r5, r6}
MobiClip_Code_020B55D4:
    ldr ip, [pc, #0xb6c]
MobiClip_Code_020B55D8:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_020B55DC:
    add r0, r0, #0x100
MobiClip_Code_020B55E0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B55E4:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B55E8:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B55EC:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B55F0:
    ldm r0, {r7, r8, sb, sl}
MobiClip_Code_020B55F4:
    add r0, r0, #0x100
MobiClip_Code_020B55F8:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b55fc:
    and r8, ip, r8, lsr #1
MobiClip_Code_020b5600:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b5604:
    and sl, ip, sl, lsr #1
MobiClip_Code_020B5608:
    add r3, r3, r7
MobiClip_Code_020b560c:
    add r4, r4, r8
MobiClip_Code_020b5610:
    add r5, r5, sb
MobiClip_Code_020b5614:
    add r6, r6, sl
MobiClip_Code_020B5618:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_020b561c:
    add r1, r1, #0x100
MobiClip_Code_020b5620:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_020b5624:
    add r0, r0, #0x100
MobiClip_Code_020B5628:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b562c:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b5630:
    and r5, ip, r5, lsr #1
MobiClip_Code_020b5634:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B5638:
    add r7, r7, r3
MobiClip_Code_020b563c:
    add r8, r8, r4
MobiClip_Code_020b5640:
    add sb, sb, r5
MobiClip_Code_020b5644:
    add sl, sl, r6
MobiClip_Code_020B5648:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_020b564c:
    add r1, r1, #0x100
MobiClip_Code_020b5650:
    subs r2, r2, #2
MobiClip_Code_020b5654:
    bne MobiClip_Code_020B55F0
MobiClip_Code_020B5658:
    pop {r5, r6}
MobiClip_Code_020b565c:
    mov pc, lr
MobiClip_Code_020b5660:
    ldr ip, [pc, #0xae0]
MobiClip_Code_020b5664:
    ldm r0, {r3, r4, r7, r8}
MobiClip_Code_020B5668:
    ldrb sb, [r0, #0x10]
MobiClip_Code_020b566c:
    add r0, r0, #0x100
MobiClip_Code_020b5670:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b5674:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B5678:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b567c:
    and r8, ip, r8, lsr #1
MobiClip_Code_020b5680:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b5684:
    add r3, r3, r3, lsr #8
MobiClip_Code_020B5688:
    add r3, r3, r4, lsl #24
MobiClip_Code_020b568c:
    add r4, r4, r4, lsr #8
MobiClip_Code_020b5690:
    add r4, r4, r7, lsl #24
MobiClip_Code_020b5694:
    add r7, r7, r7, lsr #8
MobiClip_Code_020B5698:
    add r7, r7, r8, lsl #24
MobiClip_Code_020B569C:
    add r8, r8, r8, lsr #8
MobiClip_Code_020B56A0:
    add r8, r8, sb, lsl #24
MobiClip_Code_020B56A4:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_020B56A8:
    add r1, r1, #0x100
MobiClip_Code_020B56AC:
    subs r2, r2, #1
MobiClip_Code_020B56B0:
    bne MobiClip_Code_020b5664
MobiClip_Code_020B56B4:
    mov pc, lr
MobiClip_Code_020B56B8:
    push {r5, r6, lr}
MobiClip_Code_020B56BC:
    ldr ip, [pc, #0xa84]
MobiClip_Code_020B56C0:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_020B56C4:
    ldrb lr, [r0, #0x10]
MobiClip_Code_020B56C8:
    add r0, r0, #0x100
MobiClip_Code_020B56CC:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B56D0:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B56D4:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B56D8:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B56DC:
    and lr, ip, lr, lsr #1
MobiClip_Code_020B56E0:
    add r3, r3, r3, lsr #8
MobiClip_Code_020B56E4:
    add r3, r3, r4, lsl #24
MobiClip_Code_020B56E8:
    add r4, r4, r4, lsr #8
MobiClip_Code_020B56EC:
    add r4, r4, r5, lsl #24
MobiClip_Code_020B56F0:
    add r5, r5, r5, lsr #8
MobiClip_Code_020B56F4:
    add r5, r5, r6, lsl #24
MobiClip_Code_020B56F8:
    add r6, r6, r6, lsr #8
MobiClip_Code_020b56fc:
    add r6, r6, lr, lsl #24
MobiClip_Code_020b5700:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b5704:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B5708:
    and r5, ip, r5, lsr #1
MobiClip_Code_020b570c:
    and r6, ip, r6, lsr #1
MobiClip_Code_020b5710:
    ldm r0, {r7, r8, sb, sl}
MobiClip_Code_020b5714:
    ldrb lr, [r0, #0x10]
MobiClip_Code_020B5718:
    add r0, r0, #0x100
MobiClip_Code_020b571c:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b5720:
    and r8, ip, r8, lsr #1
MobiClip_Code_020b5724:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B5728:
    and sl, ip, sl, lsr #1
MobiClip_Code_020b572c:
    and lr, ip, lr, lsr #1
MobiClip_Code_020b5730:
    add r7, r7, r7, lsr #8
MobiClip_Code_020b5734:
    add r7, r7, r8, lsl #24
MobiClip_Code_020B5738:
    add r8, r8, r8, lsr #8
MobiClip_Code_020b573c:
    add r8, r8, sb, lsl #24
MobiClip_Code_020b5740:
    add sb, sb, sb, lsr #8
MobiClip_Code_020b5744:
    add sb, sb, sl, lsl #24
MobiClip_Code_020B5748:
    add sl, sl, sl, lsr #8
MobiClip_Code_020b574c:
    add sl, sl, lr, lsl #24
MobiClip_Code_020b5750:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b5754:
    and r8, ip, r8, lsr #1
MobiClip_Code_020B5758:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b575c:
    and sl, ip, sl, lsr #1
MobiClip_Code_020b5760:
    add r3, r3, r7
MobiClip_Code_020b5764:
    add r4, r4, r8
MobiClip_Code_020B5768:
    add r5, r5, sb
MobiClip_Code_020b576c:
    add r6, r6, sl
MobiClip_Code_020b5770:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_020b5774:
    add r1, r1, #0x100
MobiClip_Code_020B5778:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_020b577c:
    ldrb lr, [r0, #0x10]
MobiClip_Code_020b5780:
    add r0, r0, #0x100
MobiClip_Code_020b5784:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B5788:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b578c:
    and r5, ip, r5, lsr #1
MobiClip_Code_020b5790:
    and r6, ip, r6, lsr #1
MobiClip_Code_020b5794:
    and lr, ip, lr, lsr #1
MobiClip_Code_020B5798:
    add r3, r3, r3, lsr #8
MobiClip_Code_020B579C:
    add r3, r3, r4, lsl #24
MobiClip_Code_020B57A0:
    add r4, r4, r4, lsr #8
MobiClip_Code_020B57A4:
    add r4, r4, r5, lsl #24
MobiClip_Code_020B57A8:
    add r5, r5, r5, lsr #8
MobiClip_Code_020B57AC:
    add r5, r5, r6, lsl #24
MobiClip_Code_020B57B0:
    add r6, r6, r6, lsr #8
MobiClip_Code_020B57B4:
    add r6, r6, lr, lsl #24
MobiClip_Code_020B57B8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B57BC:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B57C0:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B57C4:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B57C8:
    add r7, r7, r3
MobiClip_Code_020B57CC:
    add r8, r8, r4
MobiClip_Code_020B57D0:
    add sb, sb, r5
MobiClip_Code_020B57D4:
    add sl, sl, r6
MobiClip_Code_020B57D8:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_020B57DC:
    add r1, r1, #0x100
MobiClip_Code_020B57E0:
    subs r2, r2, #2
MobiClip_Code_020B57E4:
    bne MobiClip_Code_020b5710
MobiClip_Code_020B57E8:
    pop {r5, r6, pc}
MobiClip_Code_020B57EC:
    sub r0, r0, #1
MobiClip_Code_020B57F0:
    ldm r0, {r3, r4, r7, r8}
MobiClip_Code_020B57F4:
    ldrb sb, [r0, #0x10]
MobiClip_Code_020B57F8:
    add r0, r0, #0x100
MobiClip_Code_020b57fc:
    lsr r3, r3, #8
MobiClip_Code_020b5800:
    add r3, r3, r4, lsl #24
MobiClip_Code_020b5804:
    lsr r4, r4, #8
MobiClip_Code_020B5808:
    add r4, r4, r7, lsl #24
MobiClip_Code_020b580c:
    lsr r7, r7, #8
MobiClip_Code_020b5810:
    add r7, r7, r8, lsl #24
MobiClip_Code_020b5814:
    lsr r8, r8, #8
MobiClip_Code_020B5818:
    add r8, r8, sb, lsl #24
MobiClip_Code_020b581c:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_020b5820:
    add r1, r1, #0x100
MobiClip_Code_020b5824:
    subs r2, r2, #1
MobiClip_Code_020B5828:
    bne MobiClip_Code_020B57F0
MobiClip_Code_020b582c:
    mov pc, lr
MobiClip_Code_020b5830:
    push {r5, r6, lr}
MobiClip_Code_020b5834:
    sub r0, r0, #1
MobiClip_Code_020B5838:
    ldr ip, [pc, #0x908]
MobiClip_Code_020b583c:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_020b5840:
    ldrb lr, [r0, #0x10]
MobiClip_Code_020b5844:
    add r0, r0, #0x100
MobiClip_Code_020B5848:
    lsr r3, r3, #8
MobiClip_Code_020b584c:
    add r3, r3, r4, lsl #24
MobiClip_Code_020b5850:
    lsr r4, r4, #8
MobiClip_Code_020b5854:
    add r4, r4, r5, lsl #24
MobiClip_Code_020B5858:
    lsr r5, r5, #8
MobiClip_Code_020b585c:
    add r5, r5, r6, lsl #24
MobiClip_Code_020b5860:
    lsr r6, r6, #8
MobiClip_Code_020b5864:
    add r6, r6, lr, lsl #24
MobiClip_Code_020B5868:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b586c:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b5870:
    and r5, ip, r5, lsr #1
MobiClip_Code_020b5874:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B5878:
    ldm r0, {r7, r8, sb, sl}
MobiClip_Code_020b587c:
    ldrb lr, [r0, #0x10]
MobiClip_Code_020b5880:
    add r0, r0, #0x100
MobiClip_Code_020b5884:
    lsr r7, r7, #8
MobiClip_Code_020B5888:
    add r7, r7, r8, lsl #24
MobiClip_Code_020b588c:
    lsr r8, r8, #8
MobiClip_Code_020b5890:
    add r8, r8, sb, lsl #24
MobiClip_Code_020b5894:
    lsr sb, sb, #8
MobiClip_Code_020B5898:
    add sb, sb, sl, lsl #24
MobiClip_Code_020B589C:
    lsr sl, sl, #8
MobiClip_Code_020B58A0:
    add sl, sl, lr, lsl #24
MobiClip_Code_020B58A4:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B58A8:
    and r8, ip, r8, lsr #1
MobiClip_Code_020B58AC:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B58B0:
    and sl, ip, sl, lsr #1
MobiClip_Code_020B58B4:
    add r3, r3, r7
MobiClip_Code_020B58B8:
    add r4, r4, r8
MobiClip_Code_020B58BC:
    add r5, r5, sb
MobiClip_Code_020B58C0:
    add r6, r6, sl
MobiClip_Code_020B58C4:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_020B58C8:
    add r1, r1, #0x100
MobiClip_Code_020B58CC:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_020B58D0:
    ldrb lr, [r0, #0x10]
MobiClip_Code_020B58D4:
    add r0, r0, #0x100
MobiClip_Code_020B58D8:
    lsr r3, r3, #8
MobiClip_Code_020B58DC:
    add r3, r3, r4, lsl #24
MobiClip_Code_020B58E0:
    lsr r4, r4, #8
MobiClip_Code_020B58E4:
    add r4, r4, r5, lsl #24
MobiClip_Code_020B58E8:
    lsr r5, r5, #8
MobiClip_Code_020B58EC:
    add r5, r5, r6, lsl #24
MobiClip_Code_020B58F0:
    lsr r6, r6, #8
MobiClip_Code_020B58F4:
    add r6, r6, lr, lsl #24
MobiClip_Code_020B58F8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b58fc:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b5900:
    and r5, ip, r5, lsr #1
MobiClip_Code_020b5904:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B5908:
    add r7, r7, r3
MobiClip_Code_020b590c:
    add r8, r8, r4
MobiClip_Code_020b5910:
    add sb, sb, r5
MobiClip_Code_020b5914:
    add sl, sl, r6
MobiClip_Code_020B5918:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_020b591c:
    add r1, r1, #0x100
MobiClip_Code_020b5920:
    subs r2, r2, #2
MobiClip_Code_020b5924:
    bne MobiClip_Code_020B5878
MobiClip_Code_020B5928:
    pop {r5, r6, pc}
MobiClip_Code_020b592c:
    ldr ip, [pc, #0x814]
MobiClip_Code_020b5930:
    sub r0, r0, #1
MobiClip_Code_020b5934:
    ldm r0, {r3, r4, r7, r8}
MobiClip_Code_020B5938:
    ldrh sb, [r0, #0x10]
MobiClip_Code_020b593c:
    add r0, r0, #0x100
MobiClip_Code_020b5940:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b5944:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B5948:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b594c:
    and r8, ip, r8, lsr #1
MobiClip_Code_020b5950:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b5954:
    lsr sl, r3, #0x10
MobiClip_Code_020B5958:
    add sl, sl, r4, lsl #16
MobiClip_Code_020b595c:
    add sl, sl, r3, lsr #8
MobiClip_Code_020b5960:
    add r3, sl, r4, lsl #24
MobiClip_Code_020b5964:
    lsr sl, r4, #0x10
MobiClip_Code_020B5968:
    add sl, sl, r7, lsl #16
MobiClip_Code_020b596c:
    add sl, sl, r4, lsr #8
MobiClip_Code_020b5970:
    add r4, sl, r7, lsl #24
MobiClip_Code_020b5974:
    lsr sl, r7, #0x10
MobiClip_Code_020B5978:
    add sl, sl, r8, lsl #16
MobiClip_Code_020b597c:
    add sl, sl, r7, lsr #8
MobiClip_Code_020b5980:
    add r7, sl, r8, lsl #24
MobiClip_Code_020b5984:
    lsr sl, r8, #0x10
MobiClip_Code_020B5988:
    add sl, sl, sb, lsl #16
MobiClip_Code_020b598c:
    add sl, sl, r8, lsr #8
MobiClip_Code_020b5990:
    add r8, sl, sb, lsl #24
MobiClip_Code_020b5994:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_020B5998:
    add r1, r1, #0x100
MobiClip_Code_020B599C:
    subs r2, r2, #1
MobiClip_Code_020B59A0:
    bne MobiClip_Code_020b5934
MobiClip_Code_020B59A4:
    mov pc, lr
MobiClip_Code_020B59A8:
    push {r5, r6, fp, lr}
MobiClip_Code_020B59AC:
    ldr ip, [pc, #0x794]
MobiClip_Code_020B59B0:
    sub r0, r0, #1
MobiClip_Code_020B59B4:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_020B59B8:
    ldrh lr, [r0, #0x10]
MobiClip_Code_020B59BC:
    add r0, r0, #0x100
MobiClip_Code_020B59C0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B59C4:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B59C8:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B59CC:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B59D0:
    and lr, ip, lr, lsr #1
MobiClip_Code_020B59D4:
    lsr fp, r3, #0x10
MobiClip_Code_020B59D8:
    add fp, fp, r4, lsl #16
MobiClip_Code_020B59DC:
    add fp, fp, r3, lsr #8
MobiClip_Code_020B59E0:
    add r3, fp, r4, lsl #24
MobiClip_Code_020B59E4:
    lsr fp, r4, #0x10
MobiClip_Code_020B59E8:
    add fp, fp, r5, lsl #16
MobiClip_Code_020B59EC:
    add fp, fp, r4, lsr #8
MobiClip_Code_020B59F0:
    add r4, fp, r5, lsl #24
MobiClip_Code_020B59F4:
    lsr fp, r5, #0x10
MobiClip_Code_020B59F8:
    add fp, fp, r6, lsl #16
MobiClip_Code_020b59fc:
    add fp, fp, r5, lsr #8
MobiClip_Code_020b5a00:
    add r5, fp, r6, lsl #24
MobiClip_Code_020b5a04:
    lsr fp, r6, #0x10
MobiClip_Code_020B5A08:
    add fp, fp, lr, lsl #16
MobiClip_Code_020b5a0c:
    add fp, fp, r6, lsr #8
MobiClip_Code_020b5a10:
    add r6, fp, lr, lsl #24
MobiClip_Code_020b5a14:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B5A18:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b5a1c:
    and r5, ip, r5, lsr #1
MobiClip_Code_020b5a20:
    and r6, ip, r6, lsr #1
MobiClip_Code_020b5a24:
    ldm r0, {r7, r8, sb, sl}
MobiClip_Code_020B5A28:
    ldrh lr, [r0, #0x10]
MobiClip_Code_020b5a2c:
    add r0, r0, #0x100
MobiClip_Code_020b5a30:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b5a34:
    and r8, ip, r8, lsr #1
MobiClip_Code_020B5A38:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b5a3c:
    and sl, ip, sl, lsr #1
MobiClip_Code_020b5a40:
    and lr, ip, lr, lsr #1
MobiClip_Code_020b5a44:
    lsr fp, r7, #0x10
MobiClip_Code_020B5A48:
    add fp, fp, r8, lsl #16
MobiClip_Code_020b5a4c:
    add fp, fp, r7, lsr #8
MobiClip_Code_020b5a50:
    add r7, fp, r8, lsl #24
MobiClip_Code_020b5a54:
    lsr fp, r8, #0x10
MobiClip_Code_020B5A58:
    add fp, fp, sb, lsl #16
MobiClip_Code_020b5a5c:
    add fp, fp, r8, lsr #8
MobiClip_Code_020b5a60:
    add r8, fp, sb, lsl #24
MobiClip_Code_020b5a64:
    lsr fp, sb, #0x10
MobiClip_Code_020B5A68:
    add fp, fp, sl, lsl #16
MobiClip_Code_020b5a6c:
    add fp, fp, sb, lsr #8
MobiClip_Code_020b5a70:
    add sb, fp, sl, lsl #24
MobiClip_Code_020b5a74:
    lsr fp, sl, #0x10
MobiClip_Code_020B5A78:
    add fp, fp, lr, lsl #16
MobiClip_Code_020b5a7c:
    add fp, fp, sl, lsr #8
MobiClip_Code_020b5a80:
    add sl, fp, lr, lsl #24
MobiClip_Code_020b5a84:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B5A88:
    and r8, ip, r8, lsr #1
MobiClip_Code_020b5a8c:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b5a90:
    and sl, ip, sl, lsr #1
MobiClip_Code_020b5a94:
    add r3, r3, r7
MobiClip_Code_020B5A98:
    add r4, r4, r8
MobiClip_Code_020B5A9C:
    add r5, r5, sb
MobiClip_Code_020B5AA0:
    add r6, r6, sl
MobiClip_Code_020B5AA4:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_020B5AA8:
    add r1, r1, #0x100
MobiClip_Code_020B5AAC:
    ldm r0, {r3, r4, r5, r6}
MobiClip_Code_020B5AB0:
    ldrh lr, [r0, #0x10]
MobiClip_Code_020B5AB4:
    add r0, r0, #0x100
MobiClip_Code_020B5AB8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B5ABC:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B5AC0:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B5AC4:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B5AC8:
    and lr, ip, lr, lsr #1
MobiClip_Code_020B5ACC:
    lsr fp, r3, #0x10
MobiClip_Code_020B5AD0:
    add fp, fp, r4, lsl #16
MobiClip_Code_020B5AD4:
    add fp, fp, r3, lsr #8
MobiClip_Code_020B5AD8:
    add r3, fp, r4, lsl #24
MobiClip_Code_020B5ADC:
    lsr fp, r4, #0x10
MobiClip_Code_020B5AE0:
    add fp, fp, r5, lsl #16
MobiClip_Code_020B5AE4:
    add fp, fp, r4, lsr #8
MobiClip_Code_020B5AE8:
    add r4, fp, r5, lsl #24
MobiClip_Code_020B5AEC:
    lsr fp, r5, #0x10
MobiClip_Code_020B5AF0:
    add fp, fp, r6, lsl #16
MobiClip_Code_020B5AF4:
    add fp, fp, r5, lsr #8
MobiClip_Code_020B5AF8:
    add r5, fp, r6, lsl #24
MobiClip_Code_020b5afc:
    lsr fp, r6, #0x10
MobiClip_Code_020b5b00:
    add fp, fp, lr, lsl #16
MobiClip_Code_020b5b04:
    add fp, fp, r6, lsr #8
MobiClip_Code_020B5B08:
    add r6, fp, lr, lsl #24
MobiClip_Code_020b5b0c:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b5b10:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b5b14:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B5B18:
    and r6, ip, r6, lsr #1
MobiClip_Code_020b5b1c:
    add r7, r7, r3
MobiClip_Code_020b5b20:
    add r8, r8, r4
MobiClip_Code_020b5b24:
    add sb, sb, r5
MobiClip_Code_020B5B28:
    add sl, sl, r6
MobiClip_Code_020b5b2c:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_020b5b30:
    add r1, r1, #0x100
MobiClip_Code_020b5b34:
    subs r2, r2, #2
MobiClip_Code_020B5B38:
    bne MobiClip_Code_020b5a24
MobiClip_Code_020b5b3c:
    pop {r5, r6, fp, pc}
MobiClip_Code_020b5b40:
    add r0, r0, #2
MobiClip_Code_020b5b44:
    ldrh r3, [r0, #-2]
MobiClip_Code_020B5B48:
    ldm r0, {r4, r7, r8}
MobiClip_Code_020b5b4c:
    ldrh sb, [r0, #0xc]
MobiClip_Code_020b5b50:
    add r0, r0, #0x100
MobiClip_Code_020b5b54:
    add r3, r3, r4, lsl #16
MobiClip_Code_020B5B58:
    lsr r4, r4, #0x10
MobiClip_Code_020b5b5c:
    add r4, r4, r7, lsl #16
MobiClip_Code_020b5b60:
    lsr r7, r7, #0x10
MobiClip_Code_020b5b64:
    add r7, r7, r8, lsl #16
MobiClip_Code_020B5B68:
    lsr r8, r8, #0x10
MobiClip_Code_020b5b6c:
    add r8, r8, sb, lsl #16
MobiClip_Code_020b5b70:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_020b5b74:
    add r1, r1, #0x100
MobiClip_Code_020B5B78:
    subs r2, r2, #1
MobiClip_Code_020b5b7c:
    bne MobiClip_Code_020b5b44
MobiClip_Code_020b5b80:
    mov pc, lr
MobiClip_Code_020b5b84:
    push {r5, r6, lr}
MobiClip_Code_020B5B88:
    ldr ip, [pc, #0x5b8]
MobiClip_Code_020b5b8c:
    add r0, r0, #2
MobiClip_Code_020b5b90:
    ldrh r3, [r0, #-2]
MobiClip_Code_020b5b94:
    ldm r0, {r4, r5, r6}
MobiClip_Code_020B5B98:
    ldrh lr, [r0, #0xc]
MobiClip_Code_020B5B9C:
    add r0, r0, #0x100
MobiClip_Code_020B5BA0:
    add r3, r3, r4, lsl #16
MobiClip_Code_020B5BA4:
    lsr r4, r4, #0x10
MobiClip_Code_020B5BA8:
    add r4, r4, r5, lsl #16
MobiClip_Code_020B5BAC:
    lsr r5, r5, #0x10
MobiClip_Code_020B5BB0:
    add r5, r5, r6, lsl #16
MobiClip_Code_020B5BB4:
    lsr r6, r6, #0x10
MobiClip_Code_020B5BB8:
    add r6, r6, lr, lsl #16
MobiClip_Code_020B5BBC:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B5BC0:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B5BC4:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B5BC8:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B5BCC:
    ldrh r7, [r0, #-2]
MobiClip_Code_020B5BD0:
    ldm r0, {r8, sb, sl}
MobiClip_Code_020B5BD4:
    ldrh lr, [r0, #0xc]
MobiClip_Code_020B5BD8:
    add r0, r0, #0x100
MobiClip_Code_020B5BDC:
    add r7, r7, r8, lsl #16
MobiClip_Code_020B5BE0:
    lsr r8, r8, #0x10
MobiClip_Code_020B5BE4:
    add r8, r8, sb, lsl #16
MobiClip_Code_020B5BE8:
    lsr sb, sb, #0x10
MobiClip_Code_020B5BEC:
    add sb, sb, sl, lsl #16
MobiClip_Code_020B5BF0:
    lsr sl, sl, #0x10
MobiClip_Code_020B5BF4:
    add sl, sl, lr, lsl #16
MobiClip_Code_020B5BF8:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b5bfc:
    and r8, ip, r8, lsr #1
MobiClip_Code_020b5c00:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b5c04:
    and sl, ip, sl, lsr #1
MobiClip_Code_020B5C08:
    add r3, r3, r7
MobiClip_Code_020b5c0c:
    add r4, r4, r8
MobiClip_Code_020b5c10:
    add r5, r5, sb
MobiClip_Code_020b5c14:
    add r6, r6, sl
MobiClip_Code_020B5C18:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_020b5c1c:
    add r1, r1, #0x100
MobiClip_Code_020b5c20:
    ldrh r3, [r0, #-2]
MobiClip_Code_020b5c24:
    ldm r0, {r4, r5, r6}
MobiClip_Code_020B5C28:
    ldrh lr, [r0, #0xc]
MobiClip_Code_020b5c2c:
    add r0, r0, #0x100
MobiClip_Code_020b5c30:
    add r3, r3, r4, lsl #16
MobiClip_Code_020b5c34:
    lsr r4, r4, #0x10
MobiClip_Code_020B5C38:
    add r4, r4, r5, lsl #16
MobiClip_Code_020b5c3c:
    lsr r5, r5, #0x10
MobiClip_Code_020b5c40:
    add r5, r5, r6, lsl #16
MobiClip_Code_020b5c44:
    lsr r6, r6, #0x10
MobiClip_Code_020B5C48:
    add r6, r6, lr, lsl #16
MobiClip_Code_020b5c4c:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b5c50:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b5c54:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B5C58:
    and r6, ip, r6, lsr #1
MobiClip_Code_020b5c5c:
    add r7, r7, r3
MobiClip_Code_020b5c60:
    add r8, r8, r4
MobiClip_Code_020b5c64:
    add sb, sb, r5
MobiClip_Code_020B5C68:
    add sl, sl, r6
MobiClip_Code_020b5c6c:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_020b5c70:
    add r1, r1, #0x100
MobiClip_Code_020b5c74:
    subs r2, r2, #2
MobiClip_Code_020B5C78:
    bne MobiClip_Code_020B5BCC
MobiClip_Code_020b5c7c:
    pop {r5, r6, pc}
MobiClip_Code_020b5c80:
    ldr ip, [pc, #0x4c0]
MobiClip_Code_020b5c84:
    add r0, r0, #2
MobiClip_Code_020B5C88:
    ldrh r3, [r0, #-2]
MobiClip_Code_020b5c8c:
    ldm r0, {r4, r7, r8, sb}
MobiClip_Code_020b5c90:
    add r0, r0, #0x100
MobiClip_Code_020b5c94:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B5C98:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B5C9C:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B5CA0:
    and r8, ip, r8, lsr #1
MobiClip_Code_020B5CA4:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B5CA8:
    add sl, r3, r4, lsl #16
MobiClip_Code_020B5CAC:
    add sl, sl, r3, lsr #8
MobiClip_Code_020B5CB0:
    add r3, sl, r4, lsl #8
MobiClip_Code_020B5CB4:
    lsr r4, r4, #0x10
MobiClip_Code_020B5CB8:
    add sl, r4, r7, lsl #16
MobiClip_Code_020B5CBC:
    add sl, sl, r4, lsr #8
MobiClip_Code_020B5CC0:
    add r4, sl, r7, lsl #8
MobiClip_Code_020B5CC4:
    lsr r7, r7, #0x10
MobiClip_Code_020B5CC8:
    add sl, r7, r8, lsl #16
MobiClip_Code_020B5CCC:
    add sl, sl, r7, lsr #8
MobiClip_Code_020B5CD0:
    add r7, sl, r8, lsl #8
MobiClip_Code_020B5CD4:
    lsr r8, r8, #0x10
MobiClip_Code_020B5CD8:
    add sl, r8, sb, lsl #16
MobiClip_Code_020B5CDC:
    add sl, sl, r8, lsr #8
MobiClip_Code_020B5CE0:
    add r8, sl, sb, lsl #8
MobiClip_Code_020B5CE4:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_020B5CE8:
    add r1, r1, #0x100
MobiClip_Code_020B5CEC:
    subs r2, r2, #1
MobiClip_Code_020B5CF0:
    bne MobiClip_Code_020B5C88
MobiClip_Code_020B5CF4:
    mov pc, lr
MobiClip_Code_020B5CF8:
    push {r5, r6, fp, lr}
MobiClip_Code_020B5CFC:
    ldr ip, [pc, #0x444]
MobiClip_Code_020B5D00:
    add r0, r0, #2
MobiClip_Code_020B5D04:
    ldrh r3, [r0, #-2]
MobiClip_Code_020B5D08:
    ldm r0, {r4, r5, r6, lr}
MobiClip_Code_020B5D0C:
    add r0, r0, #0x100
MobiClip_Code_020B5D10:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B5D14:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B5D18:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B5D1C:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B5D20:
    and lr, ip, lr, lsr #1
MobiClip_Code_020B5D24:
    add fp, r3, r4, lsl #16
MobiClip_Code_020B5D28:
    add fp, fp, r3, lsr #8
MobiClip_Code_020B5D2C:
    add r3, fp, r4, lsl #8
MobiClip_Code_020B5D30:
    lsr r4, r4, #0x10
MobiClip_Code_020B5D34:
    add fp, r4, r5, lsl #16
MobiClip_Code_020B5D38:
    add fp, fp, r4, lsr #8
MobiClip_Code_020B5D3C:
    add r4, fp, r5, lsl #8
MobiClip_Code_020B5D40:
    lsr r5, r5, #0x10
MobiClip_Code_020B5D44:
    add fp, r5, r6, lsl #16
MobiClip_Code_020B5D48:
    add fp, fp, r5, lsr #8
MobiClip_Code_020B5D4C:
    add r5, fp, r6, lsl #8
MobiClip_Code_020B5D50:
    lsr r6, r6, #0x10
MobiClip_Code_020B5D54:
    add fp, r6, lr, lsl #16
MobiClip_Code_020B5D58:
    add fp, fp, r6, lsr #8
MobiClip_Code_020B5D5C:
    add r6, fp, lr, lsl #8
MobiClip_Code_020B5D60:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B5D64:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B5D68:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B5D6C:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B5D70:
    ldrh r7, [r0, #-2]
MobiClip_Code_020B5D74:
    ldm r0, {r8, sb, sl, lr}
MobiClip_Code_020B5D78:
    add r0, r0, #0x100
MobiClip_Code_020B5D7C:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B5D80:
    and r8, ip, r8, lsr #1
MobiClip_Code_020B5D84:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B5D88:
    and sl, ip, sl, lsr #1
MobiClip_Code_020B5D8C:
    and lr, ip, lr, lsr #1
MobiClip_Code_020B5D90:
    add fp, r7, r8, lsl #16
MobiClip_Code_020B5D94:
    add fp, fp, r7, lsr #8
MobiClip_Code_020B5D98:
    add r7, fp, r8, lsl #8
MobiClip_Code_020B5D9C:
    lsr r8, r8, #0x10
MobiClip_Code_020B5DA0:
    add fp, r8, sb, lsl #16
MobiClip_Code_020B5DA4:
    add fp, fp, r8, lsr #8
MobiClip_Code_020B5DA8:
    add r8, fp, sb, lsl #8
MobiClip_Code_020B5DAC:
    lsr sb, sb, #0x10
MobiClip_Code_020B5DB0:
    add fp, sb, sl, lsl #16
MobiClip_Code_020B5DB4:
    add fp, fp, sb, lsr #8
MobiClip_Code_020B5DB8:
    add sb, fp, sl, lsl #8
MobiClip_Code_020B5DBC:
    lsr sl, sl, #0x10
MobiClip_Code_020B5DC0:
    add fp, sl, lr, lsl #16
MobiClip_Code_020B5DC4:
    add fp, fp, sl, lsr #8
MobiClip_Code_020B5DC8:
    add sl, fp, lr, lsl #8
MobiClip_Code_020B5DCC:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B5DD0:
    and r8, ip, r8, lsr #1
MobiClip_Code_020B5DD4:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B5DD8:
    and sl, ip, sl, lsr #1
MobiClip_Code_020B5DDC:
    add r3, r3, r7
MobiClip_Code_020B5DE0:
    add r4, r4, r8
MobiClip_Code_020B5DE4:
    add r5, r5, sb
MobiClip_Code_020B5DE8:
    add r6, r6, sl
MobiClip_Code_020B5DEC:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_020B5DF0:
    add r1, r1, #0x100
MobiClip_Code_020B5DF4:
    ldrh r3, [r0, #-2]
MobiClip_Code_020B5DF8:
    ldm r0, {r4, r5, r6, lr}
MobiClip_Code_020B5DFC:
    add r0, r0, #0x100
MobiClip_Code_020B5E00:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B5E04:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B5E08:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B5E0C:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B5E10:
    and lr, ip, lr, lsr #1
MobiClip_Code_020B5E14:
    add fp, r3, r4, lsl #16
MobiClip_Code_020B5E18:
    add fp, fp, r3, lsr #8
MobiClip_Code_020B5E1C:
    add r3, fp, r4, lsl #8
MobiClip_Code_020B5E20:
    lsr r4, r4, #0x10
MobiClip_Code_020B5E24:
    add fp, r4, r5, lsl #16
MobiClip_Code_020B5E28:
    add fp, fp, r4, lsr #8
MobiClip_Code_020B5E2C:
    add r4, fp, r5, lsl #8
MobiClip_Code_020B5E30:
    lsr r5, r5, #0x10
MobiClip_Code_020B5E34:
    add fp, r5, r6, lsl #16
MobiClip_Code_020B5E38:
    add fp, fp, r5, lsr #8
MobiClip_Code_020B5E3C:
    add r5, fp, r6, lsl #8
MobiClip_Code_020B5E40:
    lsr r6, r6, #0x10
MobiClip_Code_020B5E44:
    add fp, r6, lr, lsl #16
MobiClip_Code_020B5E48:
    add fp, fp, r6, lsr #8
MobiClip_Code_020B5E4C:
    add r6, fp, lr, lsl #8
MobiClip_Code_020B5E50:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B5E54:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B5E58:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B5E5C:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B5E60:
    add r7, r7, r3
MobiClip_Code_020B5E64:
    add r8, r8, r4
MobiClip_Code_020B5E68:
    add sb, sb, r5
MobiClip_Code_020B5E6C:
    add sl, sl, r6
MobiClip_Code_020B5E70:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_020B5E74:
    add r1, r1, #0x100
MobiClip_Code_020B5E78:
    subs r2, r2, #2
MobiClip_Code_020B5E7C:
    bne MobiClip_Code_020B5D70
MobiClip_Code_020B5E80:
    pop {r5, r6, fp, pc}
MobiClip_Code_020B5E84:
    add r0, r0, #1
MobiClip_Code_020B5E88:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B5E8C:
    ldm r0, {r4, r7, r8, sb}
MobiClip_Code_020B5E90:
    add r0, r0, #0x100
MobiClip_Code_020B5E94:
    add r3, r3, r4, lsl #8
MobiClip_Code_020B5E98:
    lsr r4, r4, #0x18
MobiClip_Code_020B5E9C:
    add r4, r4, r7, lsl #8
MobiClip_Code_020B5EA0:
    lsr r7, r7, #0x18
MobiClip_Code_020B5EA4:
    add r7, r7, r8, lsl #8
MobiClip_Code_020B5EA8:
    lsr r8, r8, #0x18
MobiClip_Code_020B5EAC:
    add r8, r8, sb, lsl #8
MobiClip_Code_020B5EB0:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_020B5EB4:
    add r1, r1, #0x100
MobiClip_Code_020B5EB8:
    subs r2, r2, #1
MobiClip_Code_020B5EBC:
    bne MobiClip_Code_020B5E88
MobiClip_Code_020B5EC0:
    mov pc, lr
MobiClip_Code_020B5EC4:
    push {r5, r6, lr}
MobiClip_Code_020B5EC8:
    ldr ip, [pc, #0x278]
MobiClip_Code_020B5ECC:
    add r0, r0, #1
MobiClip_Code_020B5ED0:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B5ED4:
    ldm r0, {r4, r5, r6, lr}
MobiClip_Code_020B5ED8:
    add r0, r0, #0x100
MobiClip_Code_020B5EDC:
    add r3, r3, r4, lsl #8
MobiClip_Code_020B5EE0:
    lsr r4, r4, #0x18
MobiClip_Code_020B5EE4:
    add r4, r4, r5, lsl #8
MobiClip_Code_020B5EE8:
    lsr r5, r5, #0x18
MobiClip_Code_020B5EEC:
    add r5, r5, r6, lsl #8
MobiClip_Code_020B5EF0:
    lsr r6, r6, #0x18
MobiClip_Code_020B5EF4:
    add r6, r6, lr, lsl #8
MobiClip_Code_020B5EF8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B5EFC:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B5F00:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B5F04:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B5F08:
    ldrb r7, [r0, #-1]
MobiClip_Code_020B5F0C:
    ldm r0, {r8, sb, sl, lr}
MobiClip_Code_020B5F10:
    add r0, r0, #0x100
MobiClip_Code_020B5F14:
    add r7, r7, r8, lsl #8
MobiClip_Code_020B5F18:
    lsr r8, r8, #0x18
MobiClip_Code_020B5F1C:
    add r8, r8, sb, lsl #8
MobiClip_Code_020B5F20:
    lsr sb, sb, #0x18
MobiClip_Code_020B5F24:
    add sb, sb, sl, lsl #8
MobiClip_Code_020B5F28:
    lsr sl, sl, #0x18
MobiClip_Code_020B5F2C:
    add sl, sl, lr, lsl #8
MobiClip_Code_020B5F30:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B5F34:
    and r8, ip, r8, lsr #1
MobiClip_Code_020B5F38:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B5F3C:
    and sl, ip, sl, lsr #1
MobiClip_Code_020B5F40:
    add r3, r3, r7
MobiClip_Code_020B5F44:
    add r4, r4, r8
MobiClip_Code_020B5F48:
    add r5, r5, sb
MobiClip_Code_020B5F4C:
    add r6, r6, sl
MobiClip_Code_020B5F50:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_020B5F54:
    add r1, r1, #0x100
MobiClip_Code_020B5F58:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B5F5C:
    ldm r0, {r4, r5, r6, lr}
MobiClip_Code_020B5F60:
    add r0, r0, #0x100
MobiClip_Code_020B5F64:
    add r3, r3, r4, lsl #8
MobiClip_Code_020B5F68:
    lsr r4, r4, #0x18
MobiClip_Code_020B5F6C:
    add r4, r4, r5, lsl #8
MobiClip_Code_020B5F70:
    lsr r5, r5, #0x18
MobiClip_Code_020B5F74:
    add r5, r5, r6, lsl #8
MobiClip_Code_020B5F78:
    lsr r6, r6, #0x18
MobiClip_Code_020B5F7C:
    add r6, r6, lr, lsl #8
MobiClip_Code_020B5F80:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B5F84:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B5F88:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B5F8C:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B5F90:
    add r7, r7, r3
MobiClip_Code_020B5F94:
    add r8, r8, r4
MobiClip_Code_020B5F98:
    add sb, sb, r5
MobiClip_Code_020B5F9C:
    add sl, sl, r6
MobiClip_Code_020B5FA0:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_020B5FA4:
    add r1, r1, #0x100
MobiClip_Code_020B5FA8:
    subs r2, r2, #2
MobiClip_Code_020B5FAC:
    bne MobiClip_Code_020B5F08
MobiClip_Code_020B5FB0:
    pop {r5, r6, pc}
MobiClip_Code_020B5FB4:
    ldr ip, [pc, #0x18c]
MobiClip_Code_020B5FB8:
    add r0, r0, #1
MobiClip_Code_020B5FBC:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B5FC0:
    ldm r0, {r4, r7, r8, sb}
MobiClip_Code_020B5FC4:
    add r0, r0, #0x100
MobiClip_Code_020B5FC8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B5FCC:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B5FD0:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B5FD4:
    and r8, ip, r8, lsr #1
MobiClip_Code_020B5FD8:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B5FDC:
    add r3, r3, r4, lsl #8
MobiClip_Code_020B5FE0:
    add r3, r3, r4
MobiClip_Code_020B5FE4:
    add r4, r7, r4, lsr #24
MobiClip_Code_020B5FE8:
    add r4, r4, r7, lsl #8
MobiClip_Code_020B5FEC:
    add r7, r8, r7, lsr #24
MobiClip_Code_020B5FF0:
    add r7, r7, r8, lsl #8
MobiClip_Code_020B5FF4:
    add r8, sb, r8, lsr #24
MobiClip_Code_020B5FF8:
    add r8, r8, sb, lsl #8
MobiClip_Code_020B5FFC:
    stm r1, {r3, r4, r7, r8}
MobiClip_Code_020B6000:
    add r1, r1, #0x100
MobiClip_Code_020B6004:
    subs r2, r2, #1
MobiClip_Code_020B6008:
    bne MobiClip_Code_020B5FBC
MobiClip_Code_020B600C:
    mov pc, lr
MobiClip_Code_020B6010:
    push {r5, r6, lr}
MobiClip_Code_020B6014:
    ldr ip, [pc, #0x12c]
MobiClip_Code_020B6018:
    add r0, r0, #1
MobiClip_Code_020B601C:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B6020:
    ldm r0, {r4, r5, r6, lr}
MobiClip_Code_020B6024:
    add r0, r0, #0x100
MobiClip_Code_020B6028:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B602C:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B6030:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B6034:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B6038:
    and lr, ip, lr, lsr #1
MobiClip_Code_020B603C:
    add r3, r3, r4, lsl #8
MobiClip_Code_020B6040:
    add r3, r3, r4
MobiClip_Code_020B6044:
    add r4, r5, r4, lsr #24
MobiClip_Code_020B6048:
    add r4, r4, r5, lsl #8
MobiClip_Code_020B604C:
    add r5, r6, r5, lsr #24
MobiClip_Code_020B6050:
    add r5, r5, r6, lsl #8
MobiClip_Code_020B6054:
    add r6, lr, r6, lsr #24
MobiClip_Code_020B6058:
    add r6, r6, lr, lsl #8
MobiClip_Code_020B605C:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6060:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B6064:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B6068:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B606C:
    ldrb r7, [r0, #-1]
MobiClip_Code_020B6070:
    ldm r0, {r8, sb, sl, lr}
MobiClip_Code_020B6074:
    add r0, r0, #0x100
MobiClip_Code_020B6078:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B607C:
    and r8, ip, r8, lsr #1
MobiClip_Code_020B6080:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6084:
    and sl, ip, sl, lsr #1
MobiClip_Code_020B6088:
    and lr, ip, lr, lsr #1
MobiClip_Code_020B608C:
    add r7, r7, r8, lsl #8
MobiClip_Code_020B6090:
    add r7, r7, r8
MobiClip_Code_020B6094:
    add r8, sb, r8, lsr #24
MobiClip_Code_020B6098:
    add r8, r8, sb, lsl #8
MobiClip_Code_020B609C:
    add sb, sl, sb, lsr #24
MobiClip_Code_020B60A0:
    add sb, sb, sl, lsl #8
MobiClip_Code_020B60A4:
    add sl, lr, sl, lsr #24
MobiClip_Code_020B60A8:
    add sl, sl, lr, lsl #8
MobiClip_Code_020B60AC:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B60B0:
    and r8, ip, r8, lsr #1
MobiClip_Code_020B60B4:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B60B8:
    and sl, ip, sl, lsr #1
MobiClip_Code_020B60BC:
    add r3, r3, r7
MobiClip_Code_020B60C0:
    add r4, r4, r8
MobiClip_Code_020B60C4:
    add r5, r5, sb
MobiClip_Code_020B60C8:
    add r6, r6, sl
MobiClip_Code_020B60CC:
    stm r1, {r3, r4, r5, r6}
MobiClip_Code_020B60D0:
    add r1, r1, #0x100
MobiClip_Code_020B60D4:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B60D8:
    ldm r0, {r4, r5, r6, lr}
MobiClip_Code_020B60DC:
    add r0, r0, #0x100
MobiClip_Code_020B60E0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B60E4:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B60E8:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B60EC:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B60F0:
    and lr, ip, lr, lsr #1
MobiClip_Code_020B60F4:
    add r3, r3, r4, lsl #8
MobiClip_Code_020B60F8:
    add r3, r3, r4
MobiClip_Code_020B60FC:
    add r4, r5, r4, lsr #24
MobiClip_Code_020B6100:
    add r4, r4, r5, lsl #8
MobiClip_Code_020B6104:
    add r5, r6, r5, lsr #24
MobiClip_Code_020B6108:
    add r5, r5, r6, lsl #8
MobiClip_Code_020B610C:
    add r6, lr, r6, lsr #24
MobiClip_Code_020B6110:
    add r6, r6, lr, lsl #8
MobiClip_Code_020B6114:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6118:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B611C:
    and r5, ip, r5, lsr #1
MobiClip_Code_020B6120:
    and r6, ip, r6, lsr #1
MobiClip_Code_020B6124:
    add r7, r7, r3
MobiClip_Code_020B6128:
    add r8, r8, r4
MobiClip_Code_020B612C:
    add sb, sb, r5
MobiClip_Code_020B6130:
    add sl, sl, r6
MobiClip_Code_020B6134:
    stm r1, {r7, r8, sb, sl}
MobiClip_Code_020B6138:
    add r1, r1, #0x100
MobiClip_Code_020B613C:
    subs r2, r2, #2
MobiClip_Code_020B6140:
    bne MobiClip_Code_020B606C
MobiClip_Code_020B6144:
    pop {r5, r6, pc}
    /* semantic constants 0x02091e4c..0x02091e50 */
    .global gMobiClipPackedAverageLaneMask
    .type gMobiClipPackedAverageLaneMask, %object
gMobiClipPackedAverageLaneMask:
    .byte 0x7f, 0x7f, 0x7f, 0x7f
MobiClip_Code_020B614C:
    ldm r0, {r3, r4}
MobiClip_Code_020B6150:
    add r0, r0, #0x100
MobiClip_Code_020B6154:
    stm r1, {r3, r4}
MobiClip_Code_020B6158:
    add r1, r1, #0x100
MobiClip_Code_020B615C:
    subs r2, r2, #1
MobiClip_Code_020B6160:
    bne MobiClip_Code_020B614C
MobiClip_Code_020B6164:
    mov pc, lr
MobiClip_Code_020B6168:
    ldr ip, [pc, #0x784]
MobiClip_Code_020B616C:
    ldm r0, {r3, r4}
MobiClip_Code_020B6170:
    add r0, r0, #0x100
MobiClip_Code_020B6174:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6178:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B617C:
    ldm r0, {r7, r8}
MobiClip_Code_020B6180:
    add r0, r0, #0x100
MobiClip_Code_020B6184:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B6188:
    and r8, ip, r8, lsr #1
MobiClip_Code_020B618C:
    add r3, r3, r7
MobiClip_Code_020B6190:
    add r4, r4, r8
MobiClip_Code_020B6194:
    stm r1, {r3, r4}
MobiClip_Code_020B6198:
    add r1, r1, #0x100
MobiClip_Code_020B619C:
    subs r2, r2, #1
MobiClip_Code_020B61A0:
    moveq pc, lr
MobiClip_Code_020B61A4:
    ldm r0, {r3, r4}
MobiClip_Code_020B61A8:
    add r0, r0, #0x100
MobiClip_Code_020B61AC:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B61B0:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B61B4:
    add r7, r7, r3
MobiClip_Code_020B61B8:
    add r8, r8, r4
MobiClip_Code_020B61BC:
    stm r1, {r7, r8}
MobiClip_Code_020B61C0:
    add r1, r1, #0x100
MobiClip_Code_020B61C4:
    subs r2, r2, #1
MobiClip_Code_020B61C8:
    bne MobiClip_Code_020B617C
MobiClip_Code_020B61CC:
    mov pc, lr
MobiClip_Code_020B61D0:
    ldr ip, [pc, #0x71c]
MobiClip_Code_020B61D4:
    ldm r0, {r3, r4}
MobiClip_Code_020B61D8:
    ldrb sb, [r0, #8]
MobiClip_Code_020B61DC:
    add r0, r0, #0x100
MobiClip_Code_020B61E0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B61E4:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B61E8:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B61EC:
    add r3, r3, r3, lsr #8
MobiClip_Code_020B61F0:
    add r3, r3, r4, lsl #24
MobiClip_Code_020B61F4:
    add r4, r4, r4, lsr #8
MobiClip_Code_020B61F8:
    add r4, r4, sb, lsl #24
MobiClip_Code_020B61FC:
    stm r1, {r3, r4}
MobiClip_Code_020B6200:
    add r1, r1, #0x100
MobiClip_Code_020B6204:
    subs r2, r2, #1
MobiClip_Code_020B6208:
    bne MobiClip_Code_020B61D4
MobiClip_Code_020B620C:
    mov pc, lr
MobiClip_Code_020B6210:
    ldr ip, [pc, #0x6dc]
MobiClip_Code_020B6214:
    ldm r0, {r3, r4}
MobiClip_Code_020B6218:
    ldrb sb, [r0, #8]
MobiClip_Code_020B621C:
    add r0, r0, #0x100
MobiClip_Code_020B6220:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6224:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B6228:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B622C:
    add r3, r3, r3, lsr #8
MobiClip_Code_020B6230:
    add r3, r3, r4, lsl #24
MobiClip_Code_020B6234:
    add r4, r4, r4, lsr #8
MobiClip_Code_020B6238:
    add r4, r4, sb, lsl #24
MobiClip_Code_020B623C:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6240:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B6244:
    ldm r0, {r7, r8}
MobiClip_Code_020B6248:
    ldrb sb, [r0, #8]
MobiClip_Code_020B624C:
    add r0, r0, #0x100
MobiClip_Code_020B6250:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B6254:
    and r8, ip, r8, lsr #1
MobiClip_Code_020B6258:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B625C:
    add r7, r7, r7, lsr #8
MobiClip_Code_020B6260:
    add r7, r7, r8, lsl #24
MobiClip_Code_020B6264:
    add r8, r8, r8, lsr #8
MobiClip_Code_020B6268:
    add r8, r8, sb, lsl #24
MobiClip_Code_020B626C:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B6270:
    and r8, ip, r8, lsr #1
MobiClip_Code_020B6274:
    add r3, r3, r7
MobiClip_Code_020B6278:
    add r4, r4, r8
MobiClip_Code_020B627C:
    stm r1, {r3, r4}
MobiClip_Code_020B6280:
    add r1, r1, #0x100
MobiClip_Code_020B6284:
    subs r2, r2, #1
MobiClip_Code_020B6288:
    moveq pc, lr
MobiClip_Code_020B628C:
    ldm r0, {r3, r4}
MobiClip_Code_020B6290:
    ldrb sb, [r0, #8]
MobiClip_Code_020B6294:
    add r0, r0, #0x100
MobiClip_Code_020B6298:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B629C:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B62A0:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B62A4:
    add r3, r3, r3, lsr #8
MobiClip_Code_020B62A8:
    add r3, r3, r4, lsl #24
MobiClip_Code_020B62AC:
    add r4, r4, r4, lsr #8
MobiClip_Code_020B62B0:
    add r4, r4, sb, lsl #24
MobiClip_Code_020B62B4:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B62B8:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B62BC:
    add r7, r7, r3
MobiClip_Code_020B62C0:
    add r8, r8, r4
MobiClip_Code_020B62C4:
    stm r1, {r7, r8}
MobiClip_Code_020B62C8:
    add r1, r1, #0x100
MobiClip_Code_020B62CC:
    subs r2, r2, #1
MobiClip_Code_020B62D0:
    bne MobiClip_Code_020B6244
MobiClip_Code_020B62D4:
    mov pc, lr
MobiClip_Code_020B62D8:
    sub r0, r0, #1
MobiClip_Code_020B62DC:
    ldm r0, {r3, r4}
MobiClip_Code_020B62E0:
    ldrb sb, [r0, #8]
MobiClip_Code_020B62E4:
    add r0, r0, #0x100
MobiClip_Code_020B62E8:
    lsr r3, r3, #8
MobiClip_Code_020B62EC:
    add r3, r3, r4, lsl #24
MobiClip_Code_020B62F0:
    lsr r4, r4, #8
MobiClip_Code_020B62F4:
    add r4, r4, sb, lsl #24
MobiClip_Code_020B62F8:
    stm r1, {r3, r4}
MobiClip_Code_020b62fc:
    add r1, r1, #0x100
MobiClip_Code_020b6300:
    subs r2, r2, #1
MobiClip_Code_020b6304:
    bne MobiClip_Code_020B62DC
MobiClip_Code_020B6308:
    mov pc, lr
MobiClip_Code_020b630c:
    sub r0, r0, #1
MobiClip_Code_020b6310:
    ldr ip, [pc, #0x5dc]
MobiClip_Code_020b6314:
    ldm r0, {r3, r4}
MobiClip_Code_020B6318:
    ldrb sb, [r0, #8]
MobiClip_Code_020b631c:
    add r0, r0, #0x100
MobiClip_Code_020b6320:
    lsr r3, r3, #8
MobiClip_Code_020b6324:
    add r3, r3, r4, lsl #24
MobiClip_Code_020B6328:
    lsr r4, r4, #8
MobiClip_Code_020b632c:
    add r4, r4, sb, lsl #24
MobiClip_Code_020b6330:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b6334:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B6338:
    ldm r0, {r7, r8}
MobiClip_Code_020b633c:
    ldrb sb, [r0, #8]
MobiClip_Code_020b6340:
    add r0, r0, #0x100
MobiClip_Code_020b6344:
    lsr r7, r7, #8
MobiClip_Code_020B6348:
    add r7, r7, r8, lsl #24
MobiClip_Code_020b634c:
    lsr r8, r8, #8
MobiClip_Code_020b6350:
    add r8, r8, sb, lsl #24
MobiClip_Code_020b6354:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B6358:
    and r8, ip, r8, lsr #1
MobiClip_Code_020b635c:
    add r3, r3, r7
MobiClip_Code_020b6360:
    add r4, r4, r8
MobiClip_Code_020b6364:
    stm r1, {r3, r4}
MobiClip_Code_020B6368:
    add r1, r1, #0x100
MobiClip_Code_020b636c:
    subs r2, r2, #1
MobiClip_Code_020b6370:
    moveq pc, lr
MobiClip_Code_020b6374:
    ldm r0, {r3, r4}
MobiClip_Code_020B6378:
    ldrb sb, [r0, #8]
MobiClip_Code_020b637c:
    add r0, r0, #0x100
MobiClip_Code_020b6380:
    lsr r3, r3, #8
MobiClip_Code_020b6384:
    add r3, r3, r4, lsl #24
MobiClip_Code_020B6388:
    lsr r4, r4, #8
MobiClip_Code_020b638c:
    add r4, r4, sb, lsl #24
MobiClip_Code_020b6390:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b6394:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B6398:
    add r7, r7, r3
MobiClip_Code_020B639C:
    add r8, r8, r4
MobiClip_Code_020B63A0:
    stm r1, {r7, r8}
MobiClip_Code_020B63A4:
    add r1, r1, #0x100
MobiClip_Code_020B63A8:
    subs r2, r2, #1
MobiClip_Code_020B63AC:
    bne MobiClip_Code_020B6338
MobiClip_Code_020B63B0:
    mov pc, lr
MobiClip_Code_020B63B4:
    ldr ip, [pc, #0x538]
MobiClip_Code_020B63B8:
    sub r0, r0, #1
MobiClip_Code_020B63BC:
    ldm r0, {r3, r4}
MobiClip_Code_020B63C0:
    ldrh sb, [r0, #8]
MobiClip_Code_020B63C4:
    add r0, r0, #0x100
MobiClip_Code_020B63C8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B63CC:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B63D0:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B63D4:
    lsr sl, r3, #0x10
MobiClip_Code_020B63D8:
    add sl, sl, r4, lsl #16
MobiClip_Code_020B63DC:
    add sl, sl, r3, lsr #8
MobiClip_Code_020B63E0:
    add r3, sl, r4, lsl #24
MobiClip_Code_020B63E4:
    lsr sl, r4, #0x10
MobiClip_Code_020B63E8:
    add sl, sl, sb, lsl #16
MobiClip_Code_020B63EC:
    add sl, sl, r4, lsr #8
MobiClip_Code_020B63F0:
    add r4, sl, sb, lsl #24
MobiClip_Code_020B63F4:
    stm r1, {r3, r4}
MobiClip_Code_020B63F8:
    add r1, r1, #0x100
MobiClip_Code_020b63fc:
    subs r2, r2, #1
MobiClip_Code_020b6400:
    bne MobiClip_Code_020B63BC
MobiClip_Code_020b6404:
    mov pc, lr
MobiClip_Code_020B6408:
    ldr ip, [pc, #0x4e4]
MobiClip_Code_020b640c:
    sub r0, r0, #1
MobiClip_Code_020b6410:
    ldm r0, {r3, r4}
MobiClip_Code_020b6414:
    ldrh sb, [r0, #8]
MobiClip_Code_020B6418:
    add r0, r0, #0x100
MobiClip_Code_020b641c:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b6420:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b6424:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6428:
    lsr sl, r3, #0x10
MobiClip_Code_020b642c:
    add sl, sl, r4, lsl #16
MobiClip_Code_020b6430:
    add sl, sl, r3, lsr #8
MobiClip_Code_020b6434:
    add r3, sl, r4, lsl #24
MobiClip_Code_020B6438:
    lsr sl, r4, #0x10
MobiClip_Code_020b643c:
    add sl, sl, sb, lsl #16
MobiClip_Code_020b6440:
    add sl, sl, r4, lsr #8
MobiClip_Code_020b6444:
    add r4, sl, sb, lsl #24
MobiClip_Code_020B6448:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b644c:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b6450:
    ldm r0, {r7, r8}
MobiClip_Code_020b6454:
    ldrh sb, [r0, #8]
MobiClip_Code_020B6458:
    add r0, r0, #0x100
MobiClip_Code_020b645c:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b6460:
    and r8, ip, r8, lsr #1
MobiClip_Code_020b6464:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6468:
    lsr sl, r7, #0x10
MobiClip_Code_020b646c:
    add sl, sl, r8, lsl #16
MobiClip_Code_020b6470:
    add sl, sl, r7, lsr #8
MobiClip_Code_020b6474:
    add r7, sl, r8, lsl #24
MobiClip_Code_020B6478:
    lsr sl, r8, #0x10
MobiClip_Code_020b647c:
    add sl, sl, sb, lsl #16
MobiClip_Code_020b6480:
    add sl, sl, r8, lsr #8
MobiClip_Code_020b6484:
    add r8, sl, sb, lsl #24
MobiClip_Code_020B6488:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b648c:
    and r8, ip, r8, lsr #1
MobiClip_Code_020b6490:
    add r3, r3, r7
MobiClip_Code_020b6494:
    add r4, r4, r8
MobiClip_Code_020B6498:
    stm r1, {r3, r4}
MobiClip_Code_020B649C:
    add r1, r1, #0x100
MobiClip_Code_020B64A0:
    subs r2, r2, #1
MobiClip_Code_020B64A4:
    moveq pc, lr
MobiClip_Code_020B64A8:
    ldm r0, {r3, r4}
MobiClip_Code_020B64AC:
    ldrh sb, [r0, #8]
MobiClip_Code_020B64B0:
    add r0, r0, #0x100
MobiClip_Code_020B64B4:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B64B8:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B64BC:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B64C0:
    lsr sl, r3, #0x10
MobiClip_Code_020B64C4:
    add sl, sl, r4, lsl #16
MobiClip_Code_020B64C8:
    add sl, sl, r3, lsr #8
MobiClip_Code_020B64CC:
    add r3, sl, r4, lsl #24
MobiClip_Code_020B64D0:
    lsr sl, r4, #0x10
MobiClip_Code_020B64D4:
    add sl, sl, sb, lsl #16
MobiClip_Code_020B64D8:
    add sl, sl, r4, lsr #8
MobiClip_Code_020B64DC:
    add r4, sl, sb, lsl #24
MobiClip_Code_020B64E0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B64E4:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B64E8:
    add r7, r7, r3
MobiClip_Code_020B64EC:
    add r8, r8, r4
MobiClip_Code_020B64F0:
    stm r1, {r7, r8}
MobiClip_Code_020B64F4:
    add r1, r1, #0x100
MobiClip_Code_020B64F8:
    subs r2, r2, #1
MobiClip_Code_020b64fc:
    bne MobiClip_Code_020b6450
MobiClip_Code_020b6500:
    mov pc, lr
MobiClip_Code_020b6504:
    ldrh r3, [r0], #2
MobiClip_Code_020B6508:
    ldr r4, [r0], #4
MobiClip_Code_020b650c:
    ldrh sb, [r0], #-6
MobiClip_Code_020b6510:
    add r0, r0, #0x100
MobiClip_Code_020b6514:
    add r3, r3, r4, lsl #16
MobiClip_Code_020B6518:
    lsr r4, r4, #0x10
MobiClip_Code_020b651c:
    add r4, r4, sb, lsl #16
MobiClip_Code_020b6520:
    stm r1, {r3, r4}
MobiClip_Code_020b6524:
    add r1, r1, #0x100
MobiClip_Code_020B6528:
    subs r2, r2, #1
MobiClip_Code_020b652c:
    bne MobiClip_Code_020b6504
MobiClip_Code_020b6530:
    mov pc, lr
MobiClip_Code_020b6534:
    ldr ip, [pc, #0x3b8]
MobiClip_Code_020B6538:
    ldrh r3, [r0], #2
MobiClip_Code_020b653c:
    ldr r4, [r0], #4
MobiClip_Code_020b6540:
    ldrh sb, [r0], #-6
MobiClip_Code_020b6544:
    add r0, r0, #0x100
MobiClip_Code_020B6548:
    add r3, r3, r4, lsl #16
MobiClip_Code_020b654c:
    lsr r4, r4, #0x10
MobiClip_Code_020b6550:
    add r4, r4, sb, lsl #16
MobiClip_Code_020b6554:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6558:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b655c:
    ldrh r7, [r0], #2
MobiClip_Code_020b6560:
    ldr r8, [r0], #4
MobiClip_Code_020b6564:
    ldrh sb, [r0], #-6
MobiClip_Code_020B6568:
    add r0, r0, #0x100
MobiClip_Code_020b656c:
    add r7, r7, r8, lsl #16
MobiClip_Code_020b6570:
    lsr r8, r8, #0x10
MobiClip_Code_020b6574:
    add r8, r8, sb, lsl #16
MobiClip_Code_020B6578:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b657c:
    and r8, ip, r8, lsr #1
MobiClip_Code_020b6580:
    add r3, r3, r7
MobiClip_Code_020b6584:
    add r4, r4, r8
MobiClip_Code_020B6588:
    stm r1, {r3, r4}
MobiClip_Code_020b658c:
    add r1, r1, #0x100
MobiClip_Code_020b6590:
    subs r2, r2, #1
MobiClip_Code_020b6594:
    moveq pc, lr
MobiClip_Code_020B6598:
    ldrh r3, [r0], #2
MobiClip_Code_020B659C:
    ldr r4, [r0], #4
MobiClip_Code_020B65A0:
    ldrh sb, [r0], #-6
MobiClip_Code_020B65A4:
    add r0, r0, #0x100
MobiClip_Code_020B65A8:
    add r3, r3, r4, lsl #16
MobiClip_Code_020B65AC:
    lsr r4, r4, #0x10
MobiClip_Code_020B65B0:
    add r4, r4, sb, lsl #16
MobiClip_Code_020B65B4:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B65B8:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B65BC:
    add r7, r7, r3
MobiClip_Code_020B65C0:
    add r8, r8, r4
MobiClip_Code_020B65C4:
    stm r1, {r7, r8}
MobiClip_Code_020B65C8:
    add r1, r1, #0x100
MobiClip_Code_020B65CC:
    subs r2, r2, #1
MobiClip_Code_020B65D0:
    bne MobiClip_Code_020b655c
MobiClip_Code_020B65D4:
    mov pc, lr
MobiClip_Code_020B65D8:
    ldr ip, [pc, #0x314]
MobiClip_Code_020B65DC:
    add r0, r0, #2
MobiClip_Code_020B65E0:
    ldrh r3, [r0, #-2]
MobiClip_Code_020B65E4:
    ldm r0, {r4, sb}
MobiClip_Code_020B65E8:
    add r0, r0, #0x100
MobiClip_Code_020B65EC:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B65F0:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B65F4:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B65F8:
    add sl, r3, r4, lsl #16
MobiClip_Code_020b65fc:
    add sl, sl, r3, lsr #8
MobiClip_Code_020b6600:
    add r3, sl, r4, lsl #8
MobiClip_Code_020b6604:
    lsr r4, r4, #0x10
MobiClip_Code_020B6608:
    add sl, r4, sb, lsl #16
MobiClip_Code_020b660c:
    add sl, sl, r4, lsr #8
MobiClip_Code_020b6610:
    add r4, sl, sb, lsl #8
MobiClip_Code_020b6614:
    stm r1, {r3, r4}
MobiClip_Code_020B6618:
    add r1, r1, #0x100
MobiClip_Code_020b661c:
    subs r2, r2, #1
MobiClip_Code_020b6620:
    bne MobiClip_Code_020B65E0
MobiClip_Code_020b6624:
    mov pc, lr
MobiClip_Code_020B6628:
    ldr ip, [pc, #0x2c4]
MobiClip_Code_020b662c:
    add r0, r0, #2
MobiClip_Code_020b6630:
    ldrh r3, [r0, #-2]
MobiClip_Code_020b6634:
    ldm r0, {r4, sb}
MobiClip_Code_020B6638:
    add r0, r0, #0x100
MobiClip_Code_020b663c:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b6640:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b6644:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6648:
    add sl, r3, r4, lsl #16
MobiClip_Code_020b664c:
    add sl, sl, r3, lsr #8
MobiClip_Code_020b6650:
    add r3, sl, r4, lsl #8
MobiClip_Code_020b6654:
    lsr r4, r4, #0x10
MobiClip_Code_020B6658:
    add sl, r4, sb, lsl #16
MobiClip_Code_020b665c:
    add sl, sl, r4, lsr #8
MobiClip_Code_020b6660:
    add r4, sl, sb, lsl #8
MobiClip_Code_020b6664:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6668:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b666c:
    ldrh r7, [r0, #-2]
MobiClip_Code_020b6670:
    ldm r0, {r8, sb}
MobiClip_Code_020b6674:
    add r0, r0, #0x100
MobiClip_Code_020B6678:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b667c:
    and r8, ip, r8, lsr #1
MobiClip_Code_020b6680:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b6684:
    add sl, r7, r8, lsl #16
MobiClip_Code_020B6688:
    add sl, sl, r7, lsr #8
MobiClip_Code_020b668c:
    add r7, sl, r8, lsl #8
MobiClip_Code_020b6690:
    lsr r8, r8, #0x10
MobiClip_Code_020b6694:
    add sl, r8, sb, lsl #16
MobiClip_Code_020B6698:
    add sl, sl, r8, lsr #8
MobiClip_Code_020B669C:
    add r8, sl, sb, lsl #8
MobiClip_Code_020B66A0:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B66A4:
    and r8, ip, r8, lsr #1
MobiClip_Code_020B66A8:
    add r3, r3, r7
MobiClip_Code_020B66AC:
    add r4, r4, r8
MobiClip_Code_020B66B0:
    stm r1, {r3, r4}
MobiClip_Code_020B66B4:
    add r1, r1, #0x100
MobiClip_Code_020B66B8:
    subs r2, r2, #1
MobiClip_Code_020B66BC:
    moveq pc, lr
MobiClip_Code_020B66C0:
    ldrh r3, [r0, #-2]
MobiClip_Code_020B66C4:
    ldm r0, {r4, sb}
MobiClip_Code_020B66C8:
    add r0, r0, #0x100
MobiClip_Code_020B66CC:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B66D0:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B66D4:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B66D8:
    add sl, r3, r4, lsl #16
MobiClip_Code_020B66DC:
    add sl, sl, r3, lsr #8
MobiClip_Code_020B66E0:
    add r3, sl, r4, lsl #8
MobiClip_Code_020B66E4:
    lsr r4, r4, #0x10
MobiClip_Code_020B66E8:
    add sl, r4, sb, lsl #16
MobiClip_Code_020B66EC:
    add sl, sl, r4, lsr #8
MobiClip_Code_020B66F0:
    add r4, sl, sb, lsl #8
MobiClip_Code_020B66F4:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B66F8:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b66fc:
    add r7, r7, r3
MobiClip_Code_020b6700:
    add r8, r8, r4
MobiClip_Code_020b6704:
    stm r1, {r7, r8}
MobiClip_Code_020B6708:
    add r1, r1, #0x100
MobiClip_Code_020b670c:
    subs r2, r2, #1
MobiClip_Code_020b6710:
    bne MobiClip_Code_020b666c
MobiClip_Code_020b6714:
    mov pc, lr
MobiClip_Code_020B6718:
    add r0, r0, #1
MobiClip_Code_020b671c:
    ldrb r3, [r0, #-1]
MobiClip_Code_020b6720:
    ldm r0, {r4, sb}
MobiClip_Code_020b6724:
    add r0, r0, #0x100
MobiClip_Code_020B6728:
    add r3, r3, r4, lsl #8
MobiClip_Code_020b672c:
    lsr r4, r4, #0x18
MobiClip_Code_020b6730:
    add r4, r4, sb, lsl #8
MobiClip_Code_020b6734:
    stm r1, {r3, r4}
MobiClip_Code_020B6738:
    add r1, r1, #0x100
MobiClip_Code_020b673c:
    subs r2, r2, #1
MobiClip_Code_020b6740:
    bne MobiClip_Code_020b671c
MobiClip_Code_020b6744:
    mov pc, lr
MobiClip_Code_020B6748:
    ldr ip, [pc, #0x1a4]
MobiClip_Code_020b674c:
    add r0, r0, #1
MobiClip_Code_020b6750:
    ldrb r3, [r0, #-1]
MobiClip_Code_020b6754:
    ldm r0, {r4, sb}
MobiClip_Code_020B6758:
    add r0, r0, #0x100
MobiClip_Code_020b675c:
    add r3, r3, r4, lsl #8
MobiClip_Code_020b6760:
    lsr r4, r4, #0x18
MobiClip_Code_020b6764:
    add r4, r4, sb, lsl #8
MobiClip_Code_020B6768:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b676c:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b6770:
    ldrb r7, [r0, #-1]
MobiClip_Code_020b6774:
    ldm r0, {r8, sb}
MobiClip_Code_020B6778:
    add r0, r0, #0x100
MobiClip_Code_020b677c:
    add r7, r7, r8, lsl #8
MobiClip_Code_020b6780:
    lsr r8, r8, #0x18
MobiClip_Code_020b6784:
    add r8, r8, sb, lsl #8
MobiClip_Code_020B6788:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b678c:
    and r8, ip, r8, lsr #1
MobiClip_Code_020b6790:
    add r3, r3, r7
MobiClip_Code_020b6794:
    add r4, r4, r8
MobiClip_Code_020B6798:
    stm r1, {r3, r4}
MobiClip_Code_020B679C:
    add r1, r1, #0x100
MobiClip_Code_020B67A0:
    subs r2, r2, #1
MobiClip_Code_020B67A4:
    moveq pc, lr
MobiClip_Code_020B67A8:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B67AC:
    ldm r0, {r4, sb}
MobiClip_Code_020B67B0:
    add r0, r0, #0x100
MobiClip_Code_020B67B4:
    add r3, r3, r4, lsl #8
MobiClip_Code_020B67B8:
    lsr r4, r4, #0x18
MobiClip_Code_020B67BC:
    add r4, r4, sb, lsl #8
MobiClip_Code_020B67C0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B67C4:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B67C8:
    add r7, r7, r3
MobiClip_Code_020B67CC:
    add r8, r8, r4
MobiClip_Code_020B67D0:
    stm r1, {r7, r8}
MobiClip_Code_020B67D4:
    add r1, r1, #0x100
MobiClip_Code_020B67D8:
    subs r2, r2, #1
MobiClip_Code_020B67DC:
    bne MobiClip_Code_020b6770
MobiClip_Code_020B67E0:
    mov pc, lr
MobiClip_Code_020B67E4:
    ldr ip, [pc, #0x108]
MobiClip_Code_020B67E8:
    add r0, r0, #1
MobiClip_Code_020B67EC:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B67F0:
    ldm r0, {r4, sb}
MobiClip_Code_020B67F4:
    add r0, r0, #0x100
MobiClip_Code_020B67F8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b67fc:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b6800:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b6804:
    add r3, r3, r4, lsl #8
MobiClip_Code_020B6808:
    add r3, r3, r4
MobiClip_Code_020b680c:
    add r4, sb, r4, lsr #24
MobiClip_Code_020b6810:
    add r4, r4, sb, lsl #8
MobiClip_Code_020b6814:
    stm r1, {r3, r4}
MobiClip_Code_020B6818:
    add r1, r1, #0x100
MobiClip_Code_020b681c:
    subs r2, r2, #1
MobiClip_Code_020b6820:
    bne MobiClip_Code_020B67EC
MobiClip_Code_020b6824:
    mov pc, lr
MobiClip_Code_020B6828:
    ldr ip, [pc, #0xc4]
MobiClip_Code_020b682c:
    add r0, r0, #1
MobiClip_Code_020b6830:
    ldrb r3, [r0, #-1]
MobiClip_Code_020b6834:
    ldm r0, {r4, sb}
MobiClip_Code_020B6838:
    add r0, r0, #0x100
MobiClip_Code_020b683c:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b6840:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b6844:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6848:
    add r3, r3, r4, lsl #8
MobiClip_Code_020b684c:
    add r3, r3, r4
MobiClip_Code_020b6850:
    add r4, sb, r4, lsr #24
MobiClip_Code_020b6854:
    add r4, r4, sb, lsl #8
MobiClip_Code_020B6858:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b685c:
    and r4, ip, r4, lsr #1
MobiClip_Code_020b6860:
    ldrb r7, [r0, #-1]
MobiClip_Code_020b6864:
    ldm r0, {r8, sb}
MobiClip_Code_020B6868:
    add r0, r0, #0x100
MobiClip_Code_020b686c:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b6870:
    and r8, ip, r8, lsr #1
MobiClip_Code_020b6874:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6878:
    add r7, r7, r8, lsl #8
MobiClip_Code_020b687c:
    add r7, r7, r8
MobiClip_Code_020b6880:
    add r8, sb, r8, lsr #24
MobiClip_Code_020b6884:
    add r8, r8, sb, lsl #8
MobiClip_Code_020B6888:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b688c:
    and r8, ip, r8, lsr #1
MobiClip_Code_020b6890:
    add r3, r3, r7
MobiClip_Code_020b6894:
    add r4, r4, r8
MobiClip_Code_020B6898:
    stm r1, {r3, r4}
MobiClip_Code_020B689C:
    add r1, r1, #0x100
MobiClip_Code_020B68A0:
    subs r2, r2, #1
MobiClip_Code_020B68A4:
    moveq pc, lr
MobiClip_Code_020B68A8:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B68AC:
    ldm r0, {r4, sb}
MobiClip_Code_020B68B0:
    add r0, r0, #0x100
MobiClip_Code_020B68B4:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B68B8:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B68BC:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B68C0:
    add r3, r3, r4, lsl #8
MobiClip_Code_020B68C4:
    add r3, r3, r4
MobiClip_Code_020B68C8:
    add r4, sb, r4, lsr #24
MobiClip_Code_020B68CC:
    add r4, r4, sb, lsl #8
MobiClip_Code_020B68D0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B68D4:
    and r4, ip, r4, lsr #1
MobiClip_Code_020B68D8:
    add r7, r7, r3
MobiClip_Code_020B68DC:
    add r8, r8, r4
MobiClip_Code_020B68E0:
    stm r1, {r7, r8}
MobiClip_Code_020B68E4:
    add r1, r1, #0x100
MobiClip_Code_020B68E8:
    subs r2, r2, #1
MobiClip_Code_020B68EC:
    bne MobiClip_Code_020b6860
MobiClip_Code_020B68F0:
    mov pc, lr
    /* semantic constants 0x020925f8..0x020925fc */
    .global gMobiClipPackedAverageLaneMask1
    .type gMobiClipPackedAverageLaneMask1, %object
gMobiClipPackedAverageLaneMask1:
    .byte 0x7f, 0x7f, 0x7f, 0x7f
MobiClip_Code_020B68F8:
    ldr r3, [r0], #0x100
MobiClip_Code_020b68fc:
    str r3, [r1], #0x100
MobiClip_Code_020b6900:
    subs r2, r2, #1
MobiClip_Code_020b6904:
    bne MobiClip_Code_020B68F8
MobiClip_Code_020B6908:
    mov pc, lr
MobiClip_Code_020b690c:
    ldr ip, [pc, #0x4dc]
MobiClip_Code_020b6910:
    ldr r3, [r0], #0x100
MobiClip_Code_020b6914:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6918:
    ldr r7, [r0], #0x100
MobiClip_Code_020b691c:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b6920:
    add r3, r3, r7
MobiClip_Code_020b6924:
    str r3, [r1], #0x100
MobiClip_Code_020B6928:
    subs r2, r2, #1
MobiClip_Code_020b692c:
    moveq pc, lr
MobiClip_Code_020b6930:
    ldr r3, [r0], #0x100
MobiClip_Code_020b6934:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6938:
    add r7, r7, r3
MobiClip_Code_020b693c:
    str r7, [r1], #0x100
MobiClip_Code_020b6940:
    subs r2, r2, #1
MobiClip_Code_020b6944:
    bne MobiClip_Code_020B6918
MobiClip_Code_020B6948:
    mov pc, lr
MobiClip_Code_020b694c:
    ldr ip, [pc, #0x49c]
MobiClip_Code_020b6950:
    ldr r3, [r0]
MobiClip_Code_020b6954:
    ldrb sb, [r0, #4]
MobiClip_Code_020B6958:
    add r0, r0, #0x100
MobiClip_Code_020b695c:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b6960:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b6964:
    add r3, r3, r3, lsr #8
MobiClip_Code_020B6968:
    add r3, r3, sb, lsl #24
MobiClip_Code_020b696c:
    str r3, [r1], #0x100
MobiClip_Code_020b6970:
    subs r2, r2, #1
MobiClip_Code_020b6974:
    bne MobiClip_Code_020b6950
MobiClip_Code_020B6978:
    mov pc, lr
MobiClip_Code_020b697c:
    ldr ip, [pc, #0x46c]
MobiClip_Code_020b6980:
    ldr r3, [r0]
MobiClip_Code_020b6984:
    ldrb sb, [r0, #4]
MobiClip_Code_020B6988:
    add r0, r0, #0x100
MobiClip_Code_020b698c:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b6990:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b6994:
    add r3, r3, r3, lsr #8
MobiClip_Code_020B6998:
    add r3, r3, sb, lsl #24
MobiClip_Code_020B699C:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B69A0:
    ldr r7, [r0]
MobiClip_Code_020B69A4:
    ldrb sb, [r0, #4]
MobiClip_Code_020B69A8:
    add r0, r0, #0x100
MobiClip_Code_020B69AC:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B69B0:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B69B4:
    add r7, r7, r7, lsr #8
MobiClip_Code_020B69B8:
    add r7, r7, sb, lsl #24
MobiClip_Code_020B69BC:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B69C0:
    add r3, r3, r7
MobiClip_Code_020B69C4:
    str r3, [r1], #0x100
MobiClip_Code_020B69C8:
    subs r2, r2, #1
MobiClip_Code_020B69CC:
    moveq pc, lr
MobiClip_Code_020B69D0:
    ldr r3, [r0]
MobiClip_Code_020B69D4:
    ldrb sb, [r0, #4]
MobiClip_Code_020B69D8:
    add r0, r0, #0x100
MobiClip_Code_020B69DC:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B69E0:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B69E4:
    add r3, r3, r3, lsr #8
MobiClip_Code_020B69E8:
    add r3, r3, sb, lsl #24
MobiClip_Code_020B69EC:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B69F0:
    add r7, r7, r3
MobiClip_Code_020B69F4:
    str r7, [r1], #0x100
MobiClip_Code_020B69F8:
    subs r2, r2, #1
MobiClip_Code_020b69fc:
    bne MobiClip_Code_020B69A0
MobiClip_Code_020b6a00:
    mov pc, lr
MobiClip_Code_020b6a04:
    sub r0, r0, #1
MobiClip_Code_020B6A08:
    ldr r3, [r0]
MobiClip_Code_020b6a0c:
    ldrb sb, [r0, #4]
MobiClip_Code_020b6a10:
    add r0, r0, #0x100
MobiClip_Code_020b6a14:
    lsr r3, r3, #8
MobiClip_Code_020B6A18:
    add r3, r3, sb, lsl #24
MobiClip_Code_020b6a1c:
    str r3, [r1], #0x100
MobiClip_Code_020b6a20:
    subs r2, r2, #1
MobiClip_Code_020b6a24:
    bne MobiClip_Code_020B6A08
MobiClip_Code_020B6A28:
    mov pc, lr
MobiClip_Code_020b6a2c:
    sub r0, r0, #1
MobiClip_Code_020b6a30:
    ldr ip, [pc, #0x3b8]
MobiClip_Code_020b6a34:
    ldr r3, [r0]
MobiClip_Code_020B6A38:
    ldrb sb, [r0, #4]
MobiClip_Code_020b6a3c:
    add r0, r0, #0x100
MobiClip_Code_020b6a40:
    lsr r3, r3, #8
MobiClip_Code_020b6a44:
    add r3, r3, sb, lsl #24
MobiClip_Code_020B6A48:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b6a4c:
    ldr r7, [r0]
MobiClip_Code_020b6a50:
    ldrb sb, [r0, #4]
MobiClip_Code_020b6a54:
    add r0, r0, #0x100
MobiClip_Code_020B6A58:
    lsr r7, r7, #8
MobiClip_Code_020b6a5c:
    add r7, r7, sb, lsl #24
MobiClip_Code_020b6a60:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b6a64:
    add r3, r3, r7
MobiClip_Code_020B6A68:
    str r3, [r1], #0x100
MobiClip_Code_020b6a6c:
    subs r2, r2, #1
MobiClip_Code_020b6a70:
    moveq pc, lr
MobiClip_Code_020b6a74:
    ldr r3, [r0]
MobiClip_Code_020B6A78:
    ldrb sb, [r0, #4]
MobiClip_Code_020b6a7c:
    add r0, r0, #0x100
MobiClip_Code_020b6a80:
    lsr r3, r3, #8
MobiClip_Code_020b6a84:
    add r3, r3, sb, lsl #24
MobiClip_Code_020B6A88:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b6a8c:
    add r7, r7, r3
MobiClip_Code_020b6a90:
    str r7, [r1], #0x100
MobiClip_Code_020b6a94:
    subs r2, r2, #1
MobiClip_Code_020B6A98:
    bne MobiClip_Code_020b6a4c
MobiClip_Code_020B6A9C:
    mov pc, lr
MobiClip_Code_020B6AA0:
    ldr ip, [pc, #0x348]
MobiClip_Code_020B6AA4:
    sub r0, r0, #1
MobiClip_Code_020B6AA8:
    ldr r3, [r0]
MobiClip_Code_020B6AAC:
    ldrh sb, [r0, #4]
MobiClip_Code_020B6AB0:
    add r0, r0, #0x100
MobiClip_Code_020B6AB4:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6AB8:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6ABC:
    lsr sl, r3, #0x10
MobiClip_Code_020B6AC0:
    add sl, sl, sb, lsl #16
MobiClip_Code_020B6AC4:
    add sl, sl, r3, lsr #8
MobiClip_Code_020B6AC8:
    add r3, sl, sb, lsl #24
MobiClip_Code_020B6ACC:
    str r3, [r1], #0x100
MobiClip_Code_020B6AD0:
    subs r2, r2, #1
MobiClip_Code_020B6AD4:
    bne MobiClip_Code_020B6AA8
MobiClip_Code_020B6AD8:
    mov pc, lr
MobiClip_Code_020B6ADC:
    ldr ip, [pc, #0x30c]
MobiClip_Code_020B6AE0:
    sub r0, r0, #1
MobiClip_Code_020B6AE4:
    ldr r3, [r0]
MobiClip_Code_020B6AE8:
    ldrh sb, [r0, #4]
MobiClip_Code_020B6AEC:
    add r0, r0, #0x100
MobiClip_Code_020B6AF0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6AF4:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6AF8:
    lsr sl, r3, #0x10
MobiClip_Code_020b6afc:
    add sl, sl, sb, lsl #16
MobiClip_Code_020b6b00:
    add sl, sl, r3, lsr #8
MobiClip_Code_020b6b04:
    add r3, sl, sb, lsl #24
MobiClip_Code_020B6B08:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b6b0c:
    ldr r7, [r0]
MobiClip_Code_020b6b10:
    ldrh sb, [r0, #4]
MobiClip_Code_020b6b14:
    add r0, r0, #0x100
MobiClip_Code_020B6B18:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b6b1c:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b6b20:
    lsr sl, r7, #0x10
MobiClip_Code_020b6b24:
    add sl, sl, sb, lsl #16
MobiClip_Code_020B6B28:
    add sl, sl, r7, lsr #8
MobiClip_Code_020b6b2c:
    add r7, sl, sb, lsl #24
MobiClip_Code_020b6b30:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b6b34:
    add r3, r3, r7
MobiClip_Code_020B6B38:
    str r3, [r1], #0x100
MobiClip_Code_020b6b3c:
    subs r2, r2, #1
MobiClip_Code_020b6b40:
    moveq pc, lr
MobiClip_Code_020b6b44:
    ldr r3, [r0]
MobiClip_Code_020B6B48:
    ldrh sb, [r0, #4]
MobiClip_Code_020b6b4c:
    add r0, r0, #0x100
MobiClip_Code_020b6b50:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b6b54:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6B58:
    lsr sl, r3, #0x10
MobiClip_Code_020b6b5c:
    add sl, sl, sb, lsl #16
MobiClip_Code_020b6b60:
    add sl, sl, r3, lsr #8
MobiClip_Code_020b6b64:
    add r3, sl, sb, lsl #24
MobiClip_Code_020B6B68:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b6b6c:
    add r7, r7, r3
MobiClip_Code_020b6b70:
    str r7, [r1], #0x100
MobiClip_Code_020b6b74:
    subs r2, r2, #1
MobiClip_Code_020B6B78:
    bne MobiClip_Code_020b6b0c
MobiClip_Code_020b6b7c:
    mov pc, lr
MobiClip_Code_020b6b80:
    ldrh r3, [r0], #2
MobiClip_Code_020b6b84:
    ldrh sb, [r0], #-2
MobiClip_Code_020B6B88:
    add r0, r0, #0x100
MobiClip_Code_020b6b8c:
    add r3, r3, sb, lsl #16
MobiClip_Code_020b6b90:
    str r3, [r1], #0x100
MobiClip_Code_020b6b94:
    subs r2, r2, #1
MobiClip_Code_020B6B98:
    bne MobiClip_Code_020b6b80
MobiClip_Code_020B6B9C:
    mov pc, lr
MobiClip_Code_020B6BA0:
    ldr ip, [pc, #0x248]
MobiClip_Code_020B6BA4:
    ldrh r3, [r0], #2
MobiClip_Code_020B6BA8:
    ldrh sb, [r0], #-2
MobiClip_Code_020B6BAC:
    add r0, r0, #0x100
MobiClip_Code_020B6BB0:
    add r3, r3, sb, lsl #16
MobiClip_Code_020B6BB4:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6BB8:
    ldrh r7, [r0], #2
MobiClip_Code_020B6BBC:
    ldrh sb, [r0], #-2
MobiClip_Code_020B6BC0:
    add r0, r0, #0x100
MobiClip_Code_020B6BC4:
    add r7, r7, sb, lsl #16
MobiClip_Code_020B6BC8:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B6BCC:
    add r3, r3, r7
MobiClip_Code_020B6BD0:
    str r3, [r1], #0x100
MobiClip_Code_020B6BD4:
    subs r2, r2, #1
MobiClip_Code_020B6BD8:
    moveq pc, lr
MobiClip_Code_020B6BDC:
    ldrh r3, [r0], #2
MobiClip_Code_020B6BE0:
    ldrh sb, [r0], #-2
MobiClip_Code_020B6BE4:
    add r0, r0, #0x100
MobiClip_Code_020B6BE8:
    add r3, r3, sb, lsl #16
MobiClip_Code_020B6BEC:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6BF0:
    add r7, r7, r3
MobiClip_Code_020B6BF4:
    str r7, [r1], #0x100
MobiClip_Code_020B6BF8:
    subs r2, r2, #1
MobiClip_Code_020b6bfc:
    bne MobiClip_Code_020B6BB8
MobiClip_Code_020b6c00:
    mov pc, lr
MobiClip_Code_020b6c04:
    ldr ip, [pc, #0x1e4]
MobiClip_Code_020B6C08:
    add r0, r0, #2
MobiClip_Code_020b6c0c:
    ldrh r3, [r0, #-2]
MobiClip_Code_020b6c10:
    ldr sb, [r0], #0x100
MobiClip_Code_020b6c14:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6C18:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b6c1c:
    add sl, r3, sb, lsl #16
MobiClip_Code_020b6c20:
    add sl, sl, r3, lsr #8
MobiClip_Code_020b6c24:
    add r3, sl, sb, lsl #8
MobiClip_Code_020B6C28:
    str r3, [r1], #0x100
MobiClip_Code_020b6c2c:
    subs r2, r2, #1
MobiClip_Code_020b6c30:
    bne MobiClip_Code_020b6c0c
MobiClip_Code_020b6c34:
    mov pc, lr
MobiClip_Code_020B6C38:
    ldr ip, [pc, #0x1b0]
MobiClip_Code_020b6c3c:
    add r0, r0, #2
MobiClip_Code_020b6c40:
    ldrh r3, [r0, #-2]
MobiClip_Code_020b6c44:
    ldr sb, [r0], #0x100
MobiClip_Code_020B6C48:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b6c4c:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b6c50:
    add sl, r3, sb, lsl #16
MobiClip_Code_020b6c54:
    add sl, sl, r3, lsr #8
MobiClip_Code_020B6C58:
    add r3, sl, sb, lsl #8
MobiClip_Code_020b6c5c:
    and r3, ip, r3, lsr #1
MobiClip_Code_020b6c60:
    ldrh r7, [r0, #-2]
MobiClip_Code_020b6c64:
    ldr sb, [r0], #0x100
MobiClip_Code_020B6C68:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b6c6c:
    and sb, ip, sb, lsr #1
MobiClip_Code_020b6c70:
    add sl, r7, sb, lsl #16
MobiClip_Code_020b6c74:
    add sl, sl, r7, lsr #8
MobiClip_Code_020B6C78:
    add r7, sl, sb, lsl #8
MobiClip_Code_020b6c7c:
    and r7, ip, r7, lsr #1
MobiClip_Code_020b6c80:
    add r3, r3, r7
MobiClip_Code_020b6c84:
    str r3, [r1], #0x100
MobiClip_Code_020B6C88:
    subs r2, r2, #1
MobiClip_Code_020b6c8c:
    moveq pc, lr
MobiClip_Code_020b6c90:
    ldrh r3, [r0, #-2]
MobiClip_Code_020b6c94:
    ldr sb, [r0], #0x100
MobiClip_Code_020B6C98:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6C9C:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6CA0:
    add sl, r3, sb, lsl #16
MobiClip_Code_020B6CA4:
    add sl, sl, r3, lsr #8
MobiClip_Code_020B6CA8:
    add r3, sl, sb, lsl #8
MobiClip_Code_020B6CAC:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6CB0:
    add r7, r7, r3
MobiClip_Code_020B6CB4:
    str r7, [r1], #0x100
MobiClip_Code_020B6CB8:
    subs r2, r2, #1
MobiClip_Code_020B6CBC:
    bne MobiClip_Code_020b6c60
MobiClip_Code_020B6CC0:
    mov pc, lr
MobiClip_Code_020B6CC4:
    add r0, r0, #1
MobiClip_Code_020B6CC8:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B6CCC:
    ldr sb, [r0], #0x100
MobiClip_Code_020B6CD0:
    add r3, r3, sb, lsl #8
MobiClip_Code_020B6CD4:
    str r3, [r1], #0x100
MobiClip_Code_020B6CD8:
    subs r2, r2, #1
MobiClip_Code_020B6CDC:
    bne MobiClip_Code_020B6CC8
MobiClip_Code_020B6CE0:
    mov pc, lr
MobiClip_Code_020B6CE4:
    ldr ip, [pc, #0x104]
MobiClip_Code_020B6CE8:
    add r0, r0, #1
MobiClip_Code_020B6CEC:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B6CF0:
    ldr sb, [r0], #0x100
MobiClip_Code_020B6CF4:
    add r3, r3, sb, lsl #8
MobiClip_Code_020B6CF8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6CFC:
    ldrb r7, [r0, #-1]
MobiClip_Code_020B6D00:
    ldr sb, [r0], #0x100
MobiClip_Code_020B6D04:
    add r7, r7, sb, lsl #8
MobiClip_Code_020B6D08:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B6D0C:
    add r3, r3, r7
MobiClip_Code_020B6D10:
    str r3, [r1], #0x100
MobiClip_Code_020B6D14:
    subs r2, r2, #1
MobiClip_Code_020B6D18:
    moveq pc, lr
MobiClip_Code_020B6D1C:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B6D20:
    ldr sb, [r0], #0x100
MobiClip_Code_020B6D24:
    add r3, r3, sb, lsl #8
MobiClip_Code_020B6D28:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6D2C:
    add r7, r7, r3
MobiClip_Code_020B6D30:
    str r7, [r1], #0x100
MobiClip_Code_020B6D34:
    subs r2, r2, #1
MobiClip_Code_020B6D38:
    bne MobiClip_Code_020B6CFC
MobiClip_Code_020B6D3C:
    mov pc, lr
MobiClip_Code_020B6D40:
    ldr ip, [pc, #0xa8]
MobiClip_Code_020B6D44:
    add r0, r0, #1
MobiClip_Code_020B6D48:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B6D4C:
    ldr sb, [r0], #0x100
MobiClip_Code_020B6D50:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6D54:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6D58:
    add r3, r3, sb, lsl #8
MobiClip_Code_020B6D5C:
    add r3, r3, sb
MobiClip_Code_020B6D60:
    str r3, [r1], #0x100
MobiClip_Code_020B6D64:
    subs r2, r2, #1
MobiClip_Code_020B6D68:
    bne MobiClip_Code_020B6D48
MobiClip_Code_020B6D6C:
    mov pc, lr
MobiClip_Code_020B6D70:
    ldr ip, [pc, #0x78]
MobiClip_Code_020B6D74:
    add r0, r0, #1
MobiClip_Code_020B6D78:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B6D7C:
    ldr sb, [r0], #0x100
MobiClip_Code_020B6D80:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6D84:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6D88:
    add r3, r3, sb, lsl #8
MobiClip_Code_020B6D8C:
    add r3, r3, sb
MobiClip_Code_020B6D90:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6D94:
    ldrb r7, [r0, #-1]
MobiClip_Code_020B6D98:
    ldr sb, [r0], #0x100
MobiClip_Code_020B6D9C:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B6DA0:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6DA4:
    add r7, r7, sb, lsl #8
MobiClip_Code_020B6DA8:
    add r7, r7, sb
MobiClip_Code_020B6DAC:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B6DB0:
    add r3, r3, r7
MobiClip_Code_020B6DB4:
    str r3, [r1], #0x100
MobiClip_Code_020B6DB8:
    subs r2, r2, #1
MobiClip_Code_020B6DBC:
    moveq pc, lr
MobiClip_Code_020B6DC0:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B6DC4:
    ldr sb, [r0], #0x100
MobiClip_Code_020B6DC8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6DCC:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6DD0:
    add r3, r3, sb, lsl #8
MobiClip_Code_020B6DD4:
    add r3, r3, sb
MobiClip_Code_020B6DD8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6DDC:
    add r7, r7, r3
MobiClip_Code_020B6DE0:
    str r7, [r1], #0x100
MobiClip_Code_020B6DE4:
    subs r2, r2, #1
MobiClip_Code_020B6DE8:
    bne MobiClip_Code_020B6D94
MobiClip_Code_020B6DEC:
    mov pc, lr
    /* semantic constants 0x02092af4..0x02092af8 */
    .global gMobiClipPackedAverageLaneMask2
    .type gMobiClipPackedAverageLaneMask2, %object
gMobiClipPackedAverageLaneMask2:
    .byte 0x7f, 0x7f, 0x7f, 0x7f
MobiClip_Code_020B6DF4:
    ldrh r3, [r0]
MobiClip_Code_020B6DF8:
    add r0, r0, #0x100
MobiClip_Code_020B6DFC:
    strh r3, [r1]
MobiClip_Code_020B6E00:
    add r1, r1, #0x100
MobiClip_Code_020B6E04:
    subs r2, r2, #1
MobiClip_Code_020B6E08:
    bne MobiClip_Code_020B6DF4
MobiClip_Code_020B6E0C:
    mov pc, lr
MobiClip_Code_020B6E10:
    ldr ip, [pc, #0x26c]
MobiClip_Code_020B6E14:
    ldrh r3, [r0]
MobiClip_Code_020B6E18:
    add r0, r0, #0x100
MobiClip_Code_020B6E1C:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6E20:
    ldrh r7, [r0]
MobiClip_Code_020B6E24:
    add r0, r0, #0x100
MobiClip_Code_020B6E28:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B6E2C:
    add r3, r3, r7
MobiClip_Code_020B6E30:
    strh r3, [r1]
MobiClip_Code_020B6E34:
    add r1, r1, #0x100
MobiClip_Code_020B6E38:
    subs r2, r2, #1
MobiClip_Code_020B6E3C:
    moveq pc, lr
MobiClip_Code_020B6E40:
    ldrh r3, [r0]
MobiClip_Code_020B6E44:
    add r0, r0, #0x100
MobiClip_Code_020B6E48:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6E4C:
    add r7, r7, r3
MobiClip_Code_020B6E50:
    strh r7, [r1]
MobiClip_Code_020B6E54:
    add r1, r1, #0x100
MobiClip_Code_020B6E58:
    subs r2, r2, #1
MobiClip_Code_020B6E5C:
    bne MobiClip_Code_020B6E20
MobiClip_Code_020B6E60:
    mov pc, lr
MobiClip_Code_020B6E64:
    ldr ip, [pc, #0x218]
MobiClip_Code_020B6E68:
    ldrh r3, [r0]
MobiClip_Code_020B6E6C:
    ldrb sb, [r0, #2]
MobiClip_Code_020B6E70:
    add r0, r0, #0x100
MobiClip_Code_020B6E74:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6E78:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6E7C:
    add r3, r3, r3, lsr #8
MobiClip_Code_020B6E80:
    add r3, r3, sb, lsl #8
MobiClip_Code_020B6E84:
    strh r3, [r1]
MobiClip_Code_020B6E88:
    add r1, r1, #0x100
MobiClip_Code_020B6E8C:
    subs r2, r2, #1
MobiClip_Code_020B6E90:
    bne MobiClip_Code_020B6E68
MobiClip_Code_020B6E94:
    mov pc, lr
MobiClip_Code_020B6E98:
    ldr ip, [pc, #0x1e4]
MobiClip_Code_020B6E9C:
    ldrh r3, [r0]
MobiClip_Code_020B6EA0:
    ldrb sb, [r0, #2]
MobiClip_Code_020B6EA4:
    add r0, r0, #0x100
MobiClip_Code_020B6EA8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6EAC:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6EB0:
    add r3, r3, r3, lsr #8
MobiClip_Code_020B6EB4:
    add r3, r3, sb, lsl #8
MobiClip_Code_020B6EB8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6EBC:
    ldrh r7, [r0]
MobiClip_Code_020B6EC0:
    ldrb sb, [r0, #2]
MobiClip_Code_020B6EC4:
    add r0, r0, #0x100
MobiClip_Code_020B6EC8:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B6ECC:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6ED0:
    add r7, r7, r7, lsr #8
MobiClip_Code_020B6ED4:
    add r7, r7, sb, lsl #8
MobiClip_Code_020B6ED8:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B6EDC:
    add r3, r3, r7
MobiClip_Code_020B6EE0:
    strh r3, [r1]
MobiClip_Code_020B6EE4:
    add r1, r1, #0x100
MobiClip_Code_020B6EE8:
    subs r2, r2, #1
MobiClip_Code_020B6EEC:
    moveq pc, lr
MobiClip_Code_020B6EF0:
    ldrh r3, [r0]
MobiClip_Code_020B6EF4:
    ldrb sb, [r0, #2]
MobiClip_Code_020B6EF8:
    add r0, r0, #0x100
MobiClip_Code_020B6EFC:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6F00:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6F04:
    add r3, r3, r3, lsr #8
MobiClip_Code_020B6F08:
    add r3, r3, sb, lsl #8
MobiClip_Code_020B6F0C:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6F10:
    add r7, r7, r3
MobiClip_Code_020B6F14:
    strh r7, [r1]
MobiClip_Code_020B6F18:
    add r1, r1, #0x100
MobiClip_Code_020B6F1C:
    subs r2, r2, #1
MobiClip_Code_020B6F20:
    bne MobiClip_Code_020B6EBC
MobiClip_Code_020B6F24:
    mov pc, lr
MobiClip_Code_020B6F28:
    add r0, r0, #1
MobiClip_Code_020B6F2C:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B6F30:
    ldrb sb, [r0], #0x100
MobiClip_Code_020B6F34:
    add r3, r3, sb, lsl #8
MobiClip_Code_020B6F38:
    strh r3, [r1]
MobiClip_Code_020B6F3C:
    add r1, r1, #0x100
MobiClip_Code_020B6F40:
    subs r2, r2, #1
MobiClip_Code_020B6F44:
    bne MobiClip_Code_020B6F2C
MobiClip_Code_020B6F48:
    mov pc, lr
MobiClip_Code_020B6F4C:
    add r0, r0, #1
MobiClip_Code_020B6F50:
    ldr ip, [pc, #0x12c]
MobiClip_Code_020B6F54:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B6F58:
    ldrb sb, [r0], #0x100
MobiClip_Code_020B6F5C:
    add r3, r3, sb, lsl #8
MobiClip_Code_020B6F60:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6F64:
    ldrb r7, [r0, #-1]
MobiClip_Code_020B6F68:
    ldrb sb, [r0], #0x100
MobiClip_Code_020B6F6C:
    add r7, r7, sb, lsl #8
MobiClip_Code_020B6F70:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B6F74:
    add r3, r3, r7
MobiClip_Code_020B6F78:
    strh r3, [r1]
MobiClip_Code_020B6F7C:
    add r1, r1, #0x100
MobiClip_Code_020B6F80:
    subs r2, r2, #1
MobiClip_Code_020B6F84:
    moveq pc, lr
MobiClip_Code_020B6F88:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B6F8C:
    ldrb sb, [r0], #0x100
MobiClip_Code_020B6F90:
    add r3, r3, sb, lsl #8
MobiClip_Code_020B6F94:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6F98:
    add r7, r7, r3
MobiClip_Code_020B6F9C:
    strh r7, [r1]
MobiClip_Code_020B6FA0:
    add r1, r1, #0x100
MobiClip_Code_020B6FA4:
    subs r2, r2, #1
MobiClip_Code_020B6FA8:
    bne MobiClip_Code_020B6F64
MobiClip_Code_020B6FAC:
    mov pc, lr
MobiClip_Code_020B6FB0:
    ldr ip, [pc, #0xcc]
MobiClip_Code_020B6FB4:
    ldrb r3, [r0]
MobiClip_Code_020B6FB8:
    ldrh sb, [r0, #1]
MobiClip_Code_020B6FBC:
    add r0, r0, #0x100
MobiClip_Code_020B6FC0:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6FC4:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B6FC8:
    lsl sl, sb, #0x18
MobiClip_Code_020B6FCC:
    add sl, r3, sl, lsr #16
MobiClip_Code_020B6FD0:
    add r3, sl, sb
MobiClip_Code_020B6FD4:
    strh r3, [r1]
MobiClip_Code_020B6FD8:
    add r1, r1, #0x100
MobiClip_Code_020B6FDC:
    subs r2, r2, #1
MobiClip_Code_020B6FE0:
    bne MobiClip_Code_020B6FB4
MobiClip_Code_020B6FE4:
    mov pc, lr
MobiClip_Code_020B6FE8:
    ldr ip, [pc, #0x94]
MobiClip_Code_020B6FEC:
    ldrb r3, [r0]
MobiClip_Code_020B6FF0:
    ldrh sb, [r0, #1]
MobiClip_Code_020B6FF4:
    add r0, r0, #0x100
MobiClip_Code_020B6FF8:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B6FFC:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B7000:
    lsl sl, sb, #0x18
MobiClip_Code_020B7004:
    add sl, r3, sl, lsr #16
MobiClip_Code_020B7008:
    add r3, sl, sb
MobiClip_Code_020B700C:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B7010:
    ldrb r7, [r0]
MobiClip_Code_020B7014:
    ldrh sb, [r0, #1]
MobiClip_Code_020B7018:
    add r0, r0, #0x100
MobiClip_Code_020B701C:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B7020:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B7024:
    lsl sl, sb, #0x18
MobiClip_Code_020B7028:
    add sl, r7, sl, lsr #16
MobiClip_Code_020B702C:
    add r7, sl, sb
MobiClip_Code_020B7030:
    and r7, ip, r7, lsr #1
MobiClip_Code_020B7034:
    add r3, r3, r7
MobiClip_Code_020B7038:
    strh r3, [r1]
MobiClip_Code_020B703C:
    add r1, r1, #0x100
MobiClip_Code_020B7040:
    subs r2, r2, #1
MobiClip_Code_020B7044:
    moveq pc, lr
MobiClip_Code_020B7048:
    ldrb r3, [r0]
MobiClip_Code_020B704C:
    ldrh sb, [r0, #1]
MobiClip_Code_020B7050:
    add r0, r0, #0x100
MobiClip_Code_020B7054:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B7058:
    and sb, ip, sb, lsr #1
MobiClip_Code_020B705C:
    lsl sl, sb, #0x18
MobiClip_Code_020B7060:
    add sl, r3, sl, lsr #16
MobiClip_Code_020B7064:
    add r3, sl, sb
MobiClip_Code_020B7068:
    and r3, ip, r3, lsr #1
MobiClip_Code_020B706C:
    add r7, r7, r3
MobiClip_Code_020B7070:
    strh r7, [r1]
MobiClip_Code_020B7074:
    add r1, r1, #0x100
MobiClip_Code_020B7078:
    subs r2, r2, #1
MobiClip_Code_020B707C:
    bne MobiClip_Code_020B7010
MobiClip_Code_020B7080:
    mov pc, lr
    /* semantic constants 0x02092d88..0x02092d8c */
    .global gMobiClipPackedAverageLaneMask3
    .type gMobiClipPackedAverageLaneMask3, %object
gMobiClipPackedAverageLaneMask3:
    .byte 0x7f, 0x7f, 0x7f, 0x7f
MobiClip_Code_020B7088:
    ldrb r3, [r0], #0x100
MobiClip_Code_020B708C:
    strb r3, [r1], #0x100
MobiClip_Code_020B7090:
    subs r2, r2, #1
MobiClip_Code_020B7094:
    bne MobiClip_Code_020B7088
MobiClip_Code_020B7098:
    mov pc, lr
MobiClip_Code_020B709C:
    ldrb r3, [r0], #0x100
MobiClip_Code_020B70A0:
    lsr r3, r3, #1
MobiClip_Code_020B70A4:
    ldrb r7, [r0], #0x100
MobiClip_Code_020B70A8:
    lsr r7, r7, #1
MobiClip_Code_020B70AC:
    add r3, r3, r7
MobiClip_Code_020B70B0:
    strb r3, [r1], #0x100
MobiClip_Code_020B70B4:
    subs r2, r2, #1
MobiClip_Code_020B70B8:
    moveq pc, lr
MobiClip_Code_020B70BC:
    ldrb r3, [r0], #0x100
MobiClip_Code_020B70C0:
    lsr r3, r3, #1
MobiClip_Code_020B70C4:
    add r7, r7, r3
MobiClip_Code_020B70C8:
    strb r7, [r1], #0x100
MobiClip_Code_020B70CC:
    subs r2, r2, #1
MobiClip_Code_020B70D0:
    bne MobiClip_Code_020B70A4
MobiClip_Code_020B70D4:
    mov pc, lr
MobiClip_Code_020B70D8:
    add r0, r0, #1
MobiClip_Code_020B70DC:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B70E0:
    ldrb sb, [r0], #0x100
MobiClip_Code_020B70E4:
    lsr r3, r3, #1
MobiClip_Code_020B70E8:
    add r3, r3, sb, lsr #1
MobiClip_Code_020B70EC:
    strb r3, [r1], #0x100
MobiClip_Code_020B70F0:
    subs r2, r2, #1
MobiClip_Code_020B70F4:
    bne MobiClip_Code_020B70DC
MobiClip_Code_020B70F8:
    mov pc, lr
MobiClip_Code_020B70FC:
    ldrb r3, [r0], #1
MobiClip_Code_020B7100:
    ldrb sb, [r0], #0x100
MobiClip_Code_020B7104:
    lsr r3, r3, #1
MobiClip_Code_020B7108:
    add r3, r3, sb, lsr #1
MobiClip_Code_020B710C:
    lsr r3, r3, #1
MobiClip_Code_020B7110:
    ldrb r7, [r0, #-1]
MobiClip_Code_020B7114:
    ldrb sb, [r0], #0x100
MobiClip_Code_020B7118:
    lsr r7, r7, #1
MobiClip_Code_020B711C:
    add r7, r7, sb, lsr #1
MobiClip_Code_020B7120:
    lsr r7, r7, #1
MobiClip_Code_020B7124:
    add r3, r3, r7
MobiClip_Code_020B7128:
    strb r3, [r1], #0x100
MobiClip_Code_020B712C:
    subs r2, r2, #1
MobiClip_Code_020B7130:
    moveq pc, lr
MobiClip_Code_020B7134:
    ldrb r3, [r0, #-1]
MobiClip_Code_020B7138:
    ldrb sb, [r0], #0x100
MobiClip_Code_020B713C:
    lsr r3, r3, #1
MobiClip_Code_020B7140:
    add r3, r3, sb, lsr #1
MobiClip_Code_020B7144:
    lsr r3, r3, #1
MobiClip_Code_020B7148:
    add r7, r7, r3
MobiClip_Code_020B714C:
    strb r7, [r1], #0x100
MobiClip_Code_020B7150:
    subs r2, r2, #1
MobiClip_Code_020B7154:
    bne MobiClip_Code_020B7110
MobiClip_Code_020B7158:
    mov pc, lr
    .size gMovieDecoderCodeBlob, . - gMovieDecoderCodeBlob
