/* Nintendo DS BIOS SWI 0x11 veneer. */
asm void LZ77UnCompReadNormalWrite8bit_0200036c(register const void *source,
                                       register void *destination)
{
    swi 0x11
    bx lr
}
