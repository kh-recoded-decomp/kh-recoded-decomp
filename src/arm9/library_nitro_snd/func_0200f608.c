/* Invalidates cache for the finished-command tag and returns the tag value.
 * Uncertainty: Tag wrap/ordering semantics are not established. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SNDi_GetFinishedCommandTag.c.
 * Original routine: SNDi_GetFinishedCommandTag. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Reads the completion tag the ARM7 writes into the shared work area. */
extern void DC_InvalidateRange(void *p, unsigned int len);
extern int *data_02059780;

int func_0200f608(void) {
    DC_InvalidateRange(data_02059780, 4);
    return *data_02059780;
}
