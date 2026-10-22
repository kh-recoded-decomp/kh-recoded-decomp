/* MSL runtime single-precision reverse subtract: swaps the operands and falls into _fsub (original assembly) */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global _frsb
    .type _frsb, %function
_frsb:
    eor r0, r0, r1
    eor r1, r0, r1
    eor r0, r0, r1
    .size _frsb, . - _frsb
