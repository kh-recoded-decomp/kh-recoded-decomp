/* Returns sub BG0 screen-map address from BG0CNT.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/auto/G2S_GetBG0ScrPtr.c.
 * Original routine: G2S_GetBG0ScrPtr. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Sub-engine BG base: 0x06200000 plus the per-BG slot in BG0CNT (no display-wide block). */
void *G2S_GetBG0ScrPtr_02006e14(void) {
    int slot = (*(volatile unsigned short *)0x04001008 & 0x1f00) >> 8;
    return (void *)(0x06200000 + (slot << 11));
}
