/* Enqueues invalidation of a sequence-data address range.
 * Uncertainty: The exact cache/device handling occurs in the command processor. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_InvalidateSeqData.c.
 * Original routine: SND_InvalidateSeqData. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Invalidates a sequence range: sound command 0x1e. */
extern void PushCommand_impl(int cmd, unsigned int start, unsigned int end, int a, int b);

void func_0200ec74(unsigned int start, unsigned int end) {
    PushCommand_impl(0x1e, start, end, 0, 0);
}
