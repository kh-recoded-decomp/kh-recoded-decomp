/* Waits for texture-palette DMA, restores saved mapping, and clears state.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/calls/GX_EndLoadTexPltt.c.
 * Original routine: GX_EndLoadTexPltt. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Waits for the texture palette upload DMA and restores the banks it had to release. */
extern void MI_WaitDma(int ch);
extern void GX_BeginLoadOBJExtPltt(int mask);
extern int data_02055c1c[];
extern int data_02056f28[];

void GX_EndLoadTexPltt_02008284(void) {
    if (data_02055c1c[0] != -1) {
        MI_WaitDma(data_02055c1c[0]);
    }
    GX_BeginLoadOBJExtPltt(data_02056f28[3]);
    data_02056f28[3] = 0;
    data_02056f28[2] = 0;
}
