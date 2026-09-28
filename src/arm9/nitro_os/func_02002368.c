/* CC0 source: Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/os/auto/OSi_AllocateCardBus.c. */
/* Clears EXMEMCNT bit 11 so the ARM9 owns the card bus. */
void OSi_AllocateCardBus(void) {
    volatile unsigned short *exmemcnt = (volatile unsigned short *)0x4000204;
    *exmemcnt = (unsigned short)(*exmemcnt & ~0x800);
}
