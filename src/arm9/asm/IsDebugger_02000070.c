/* Nintendo DS BIOS SWI 0x0f veneer. */
asm int IsDebugger_02000070(void)
{
    swi 0x0f
    bx lr
}
