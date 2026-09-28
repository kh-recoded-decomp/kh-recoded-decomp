/* Returns main BG0 character-data address from display VRAM base and BG0CNT slot.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/auto/G2_GetBG0CharPtr.c.
 * Original routine: G2_GetBG0CharPtr. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Main-engine BG base: the display-wide 64K block from DISPCNT plus the per-BG slot in BG0CNT. */
void *G2_GetBG0CharPtr_02007078(void) {
    int slot = (*(volatile unsigned short *)0x04000008 & 0x3c) >> 2;
    unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x07000000) >> 24;
    return (void *)(0x06000000 + (dispBase << 16) + (slot << 14));
}
