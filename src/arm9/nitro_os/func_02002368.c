void OSi_AllocateCardBus(void) {
    volatile unsigned short *exmemcnt = (volatile unsigned short *)0x4000204;
    *exmemcnt = (unsigned short)(*exmemcnt & ~0x800);
}
