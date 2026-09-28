/* Enqueues invalidation of a wave-data address range.
 * Uncertainty: The exact cache/device handling occurs in the command processor. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_InvalidateWaveData.c.
 * Original routine: SND_InvalidateWaveData. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Invalidates a wave range: sound command 0x20. */
extern void PushCommand_impl(int cmd, unsigned int start, unsigned int end, int a, int b);

void func_0200ecb4(unsigned int start, unsigned int end) {
    PushCommand_impl(0x20, start, end, 0, 0);
}
