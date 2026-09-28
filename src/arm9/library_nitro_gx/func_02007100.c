/* Returns sub BG1 character-data address from BG1CNT.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/auto/G2S_GetBG1CharPtr.c.
 * Original routine: G2S_GetBG1CharPtr. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Sub-engine BG base: 0x06200000 plus the per-BG slot in BG1CNT (no display-wide block). */
void *G2S_GetBG1CharPtr_02007100(void) {
    int slot = (*(volatile unsigned short *)0x0400100a & 0x3c) >> 2;
    return (void *)(0x06200000 + (slot << 14));
}
