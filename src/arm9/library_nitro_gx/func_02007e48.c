/* Waits for main OBJ extended-palette DMA, restores saved mapping, and clears state.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/calls/GX_EndLoadOBJExtPltt.c.
 * Original routine: GX_EndLoadOBJExtPltt. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Waits for the main OBJ extended palette upload DMA and restores the banks it had to release. */
extern void MI_WaitDma(int ch);
extern void GX_SetBankForOBJExtPltt(int mask);
extern int data_02055c1c[];
extern int data_02056f0c[];

void GX_EndLoadOBJExtPltt_02007e48(void) {
    if (data_02055c1c[0] != -1) {
        MI_WaitDma(data_02055c1c[0]);
    }
    GX_SetBankForOBJExtPltt(data_02056f0c[2]);
    data_02056f0c[2] = 0;
    data_02056f0c[1] = 0;
}
