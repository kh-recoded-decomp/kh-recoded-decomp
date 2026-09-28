/* Waits for main BG extended-palette DMA, restores saved mapping, and clears state.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/calls/GX_EndLoadBGExtPltt.c.
 * Original routine: GX_EndLoadBGExtPltt. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Waits for the main BG extended-palette upload DMA and restores the released banks. */
extern void MI_WaitDma(int ch);
extern void GX_SetBankForBGExtPltt(int mask);
extern int data_02055c1c[];
extern int data_02056f0c[];

void GX_EndLoadBGExtPltt_02007d50(void) {
    if (data_02055c1c[0] != -1) {
        MI_WaitDma(data_02055c1c[0]);
    }
    GX_SetBankForBGExtPltt(data_02056f0c[5]);
    data_02056f0c[5] = 0;
    data_02056f0c[4] = 0;
    data_02056f0c[3] = 0;
}
