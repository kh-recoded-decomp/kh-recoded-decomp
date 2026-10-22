/* NitroSDK MATH: the four SHA-1 round constants, kept in .text just before
 * MATHi_SHA1ProcessBlock, which loads them pc-relative. */
    .syntax unified
    .text
    .align 2
    .global MATHi_SHA1RoundConstants
    .type MATHi_SHA1RoundConstants, %object
MATHi_SHA1RoundConstants:
    .word 0x5a827999
    .word 0x6ed9eba1
    .word 0x8f1bbcdc
    .word 0xca62c1d6
    .size MATHi_SHA1RoundConstants, . - MATHi_SHA1RoundConstants
