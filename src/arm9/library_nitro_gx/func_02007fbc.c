/* Waits for sub OBJ extended-palette DMA and restores saved mapping.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/calls/GXS_EndLoadOBJExtPltt.c.
 * Original routine: GXS_EndLoadOBJExtPltt. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Waits for the sub OBJ extended palette upload DMA and restores the banks it had to release. */
extern void MI_WaitDma(int ch);
extern void GX_SetBankForSubOBJExtPltt(int mask);
extern int data_02055c1c[];
extern int data_02056f0c[];

void GXS_EndLoadOBJExtPltt_02007fbc(void) {
    if (data_02055c1c[0] != -1) {
        MI_WaitDma(data_02055c1c[0]);
    }
    GX_SetBankForSubOBJExtPltt(data_02056f0c[6]);
    data_02056f0c[6] = 0;
}
