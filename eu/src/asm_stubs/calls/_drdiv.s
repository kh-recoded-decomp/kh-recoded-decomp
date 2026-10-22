/* MSL runtime double-precision reverse divide: swaps the operands and falls into _ddiv (original assembly) */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global _drdiv
    .type _drdiv, %function
_drdiv:
    eor r1, r1, r3
    eor r3, r1, r3
    eor r1, r1, r3
    eor r0, r0, r2
    eor r2, r0, r2
    eor r0, r0, r2
    .size _drdiv, . - _drdiv
