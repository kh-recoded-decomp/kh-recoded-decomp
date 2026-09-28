/* Returns main BG0 screen-map address from display VRAM base and BG0CNT slot.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/auto/G2_GetBG0ScrPtr.c.
 * Original routine: G2_GetBG0ScrPtr. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* BG screen base = the display-wide 64K block from DISPCNT plus the per-BG 2K slot in BG0CNT. */
void *G2_GetBG0ScrPtr_02006de0(void) {
    int scrBase = (*(volatile unsigned short *)0x04000008 & 0x1f00) >> 8;
    unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x38000000) >> 27;
    return (void *)(0x06000000 + (dispBase << 16) + (scrBase << 11));
}
