/* CC0 source: Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/mi/calls/MI_SetWramBank.c. */
/* MI_SetWramBank: selects the WRAM bank via WRAMCNT (0x04000247). */

void MI_SetWramBank(unsigned char bank) {
    *(volatile unsigned char *)0x04000247 = bank;
}
