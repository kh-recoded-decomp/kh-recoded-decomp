/* Returns sub BG2 screen-map address from mode and BG2CNT, selecting tiled/bitmap spacing.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/auto/G2S_GetBG2ScrPtr.c.
 * Original routine: G2S_GetBG2ScrPtr. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* BG2's screen base moves with the BG mode: tiled modes use the 2K slot, mode 5 uses the 16K one
 * when BG2 is a bitmap, and from mode 6 up BG2 has no screen at all. */
void *G2S_GetBG2ScrPtr_02006f0c(void) {
    int mode = *(volatile unsigned *)0x04001000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400100c;
    unsigned slot = (cnt & 0x1f00) >> 8;
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        return (void *)(0x06200000 + (slot << 11));
    case 5:
        if ((cnt & 0x80) != 0) {
            slot <<= 14;
        } else {
            slot <<= 11;
        }
        return (void *)(0x06200000 + slot);
    case 6:
        return 0;
    default:
        return 0;
    }
}
