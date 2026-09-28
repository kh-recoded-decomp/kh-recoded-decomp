/* Waits for texture DMA, restores saved bank mapping, and clears load-session state.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/calls/GX_EndLoadTex.c.
 * Original routine: GX_EndLoadTex. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Waits for the texture upload DMA and restores the released banks. */
extern void MI_WaitDma(int ch);
extern void GX_SetBankForTex(int mask);
extern int data_02055c1c[];
extern int data_02056f28[];

void GX_EndLoadTex_0200819c(void) {
    if (data_02055c1c[0] != -1) {
        MI_WaitDma(data_02055c1c[0]);
    }
    GX_SetBankForTex(data_02056f28[5]);
    data_02056f28[7] = 0;
    data_02056f28[6] = 0;
    data_02056f28[1] = 0;
    data_02056f28[5] = 0;
}
