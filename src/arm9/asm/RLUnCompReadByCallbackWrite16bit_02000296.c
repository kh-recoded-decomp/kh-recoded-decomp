/* Nintendo DS BIOS SWI 0x15 veneer. */
asm void RLUnCompReadByCallbackWrite16bit_02000296(register const void *source,
                                          register void *destination)
{
    swi 0x15
    bx lr
}
