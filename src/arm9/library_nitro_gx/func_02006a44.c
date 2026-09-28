/* Writes 128 NOP commands to flush geometry FIFO, then waits for engine idle.
 * This is a reusable Nitro/NitroSystem subsystem operation; a specific Re:coded gameplay caller or use is not inferred. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/gx/calls/G3X_ClearFifo.c.
 * Original routine: G3X_ClearFifo. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Flushes the geometry FIFO with 128 NOP commands and waits for the engine to go idle. */
extern void GXi_NopClearFifo128_(volatile unsigned int *fifo);

void G3X_ClearFifo_02006a44(void) {
    GXi_NopClearFifo128_((volatile unsigned int *)0x4000400);
    while (*(volatile unsigned int *)0x4000600 & 0x8000000) {
        ;
    }
}
