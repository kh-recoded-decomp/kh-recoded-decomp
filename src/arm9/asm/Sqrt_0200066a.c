/* Nintendo DS BIOS SWI 0x0d veneer. */
asm void Sqrt_0200066a(void)
{
    swi 0x0d
    bx lr
}
