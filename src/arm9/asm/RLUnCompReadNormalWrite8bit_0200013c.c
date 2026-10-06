/* Nintendo DS BIOS SWI 0x14 veneer. */
asm void RLUnCompReadNormalWrite8bit_0200013c(register const void *source,
                                     register void *destination)
{
    swi 0x14
    bx lr
}
