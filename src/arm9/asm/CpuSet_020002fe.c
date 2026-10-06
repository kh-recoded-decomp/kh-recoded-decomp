typedef unsigned int u32;

/* Nintendo DS BIOS SWI 0x0b veneer. */
asm void CpuSet_020002fe(register const void *source, register void *destination,
                register u32 control)
{
    swi 0x0b
    bx lr
}
