typedef unsigned int u32;

/* NitroSDK overlap-safe halfword copy primitive. */
asm void MIi_CpuCopy16Backward_01ff86b8(register const void *source,
                               register void *destination, register u32 size)
{
    mov     ip, r1
    add     r0, r0, r2
    add     r1, r1, r2
copyPreviousHalfword:
    cmp     ip, r1
    ldrlth  r2, [r0, #-2]!
    strlth  r2, [r1, #-2]!
    blt     copyPreviousHalfword
    bx      lr
}
