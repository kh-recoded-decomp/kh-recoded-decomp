/* Returns main BG2 character-data address unless BG2 is a bitmap layer.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/auto/G2_GetBG2CharPtr.c.
 * Original routine: G2_GetBG2CharPtr. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* From BG mode 5 up, BG2 can be a bitmap layer: then it has no character base at all. */
void *G2_GetBG2CharPtr_02007120(void) {
    int mode = *(volatile unsigned *)0x04000000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400000c;
    if (mode < 5 || (cnt & 0x80) == 0) {
        unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x07000000) >> 24;
        return (void *)(0x06000000 + (dispBase << 16) + (((cnt & 0x3c) >> 2) << 14));
    }
    return 0;
}
