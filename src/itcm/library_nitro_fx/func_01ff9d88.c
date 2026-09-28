/* Starts hardware fixed-point reciprocal operation by programming divider registers.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/fx/auto/FX_InvAsync.c.
 * Original routine: FX_InvAsync. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Kicks the divider with FX32_ONE in the high word of the numerator: that is 1.0 << 32, so the
 * quotient comes out as the fx32 reciprocal. */
void FX_InvAsync_01ff9d88(int x) {
    volatile unsigned *div = (volatile unsigned *)0x04000280;
    *(volatile unsigned short *)div = 1;
    *(volatile long long *)(div + 4) = (long long)0x1000 << 32;
    *(volatile long long *)(div + 6) = (long long)(unsigned)x;
}
