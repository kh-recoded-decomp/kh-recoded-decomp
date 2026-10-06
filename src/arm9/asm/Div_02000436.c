typedef signed int s32;

/* Nintendo DS BIOS signed divide veneer. */
asm s32 Div_02000436(register s32 numerator, register s32 denominator)
{
    swi 0x09
    bx lr
}
