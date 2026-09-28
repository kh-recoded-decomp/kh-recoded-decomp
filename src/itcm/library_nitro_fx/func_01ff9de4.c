/* Starts hardware fixed-point division by programming divider registers.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/fx/auto/FX_DivAsync.c.
 * Original routine: FX_DivAsync. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Kicks the hardware divider for a fx32 divide: the numerator goes in the HIGH word of the
 * 64-bit DIV_NUMER, which is the same as shifting it left by 32 before dividing. */
void FX_DivAsync_01ff9de4(int numer, int denom) {
    volatile unsigned *div = (volatile unsigned *)0x04000280;
    *(volatile unsigned short *)div = 1;
    div[4] = 0;
    div[5] = (unsigned)numer;
    div[6] = (unsigned)denom;
    div[7] = 0;
}
