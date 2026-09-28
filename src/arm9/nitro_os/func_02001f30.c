/* CC0 source: Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/os/auto/OS_SetIrqMask.c. */
/* IME is read back before being restored: the hardware needs the read to settle. */
static inline unsigned OS_DisableInterrupts(void) {
    volatile unsigned short *ime = (volatile unsigned short *)0x04000208;
    unsigned old = *ime;
    *ime = 0;
    return old;
}

static inline void OS_RestoreInterrupts(unsigned state) {
    volatile unsigned short *ime = (volatile unsigned short *)0x04000208;
    (void)*ime;
    *ime = (unsigned short)state;
}

unsigned OS_SetIrqMask(unsigned mask) {
    unsigned enabled = OS_DisableInterrupts();
    unsigned last = *(volatile unsigned *)0x04000210;
    *(volatile unsigned *)0x04000210 = mask;
    OS_RestoreInterrupts(enabled);
    return last;
}
