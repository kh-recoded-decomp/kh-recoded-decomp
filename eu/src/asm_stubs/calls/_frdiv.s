/* MSL runtime single-precision reverse divide: swaps the operands and falls into _fdiv (original assembly) */
    .syntax unified
    .arch armv5te
    .text
    .arm
    .align 2
    .global _frdiv
    .type _frdiv, %function
_frdiv:
    eor r0, r0, r1
    eor r1, r0, r1
    eor r0, r0, r1
    .size _frdiv, . - _frdiv
