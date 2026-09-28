/* Writes 3D clear-color from color/alpha/polygon-ID/fog inputs, then writes clear depth.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/auto/G3X_SetClearColor.c.
 * Original routine: G3X_SetClearColor. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
void G3X_SetClearColor_02006c08(unsigned color, unsigned alpha, unsigned depth,
                       unsigned polygonID, int fog) {
    unsigned v = color | (alpha << 16) | (polygonID << 24);
    if (fog != 0) {
        v |= 0x8000;
    }
    *(volatile unsigned *)0x04000350 = v;
    *(volatile unsigned short *)0x04000354 = (unsigned short)depth;
}
