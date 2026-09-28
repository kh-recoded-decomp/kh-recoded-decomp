/* Sets/clears V-blank interrupt enable in DISPSTAT and returns previous state.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/auto/GX_VBlankIntr.c.
 * Original routine: GX_VBlankIntr. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Enables or disables the V-blank interrupt in DISPSTAT; returns the previous state. */
int GX_VBlankIntr_020065f8(int enable) {
    volatile unsigned short *dispstat = (volatile unsigned short *)0x04000004;
    int prev = *dispstat & 8;
    if (enable != 0) {
        *dispstat |= 8;
        return prev;
    }
    *dispstat &= ~8;
    return prev;
}
