/* Returns sub BG3 character-data address for tiled modes; otherwise null.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/auto/G2S_GetBG3CharPtr.c.
 * Original routine: G2S_GetBG3CharPtr. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* BG3 only has a character base in the tiled modes: below 3 always, 3..5 unless it is running as
 * a bitmap layer, and never from mode 6 up. */
void *G2S_GetBG3CharPtr_02007208(void) {
    int mode = *(volatile unsigned *)0x04001000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400100e;
    if (mode < 3 || (mode < 6 && (cnt & 0x80) == 0)) {
        return (void *)(0x06200000 + (((cnt & 0x3c) >> 2) << 14));
    }
    return 0;
}
