/* Returns sub BG2 character-data address unless BG2 is a bitmap layer.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/auto/G2S_GetBG2CharPtr.c.
 * Original routine: G2S_GetBG2CharPtr. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* From BG mode 5 up, BG2 can be a bitmap layer: then it has no character base at all. */
void *G2S_GetBG2CharPtr_02007170(void) {
    int mode = *(volatile unsigned *)0x04001000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400100c;
    if (mode < 5 || (cnt & 0x80) == 0) {
        return (void *)(0x06200000 + (((cnt & 0x3c) >> 2) << 14));
    }
    return 0;
}
