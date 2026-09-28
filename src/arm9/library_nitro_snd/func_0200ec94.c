/* Enqueues invalidation of a bank-data address range.
 * Uncertainty: The exact cache/device handling occurs in the command processor. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_InvalidateBankData.c.
 * Original routine: SND_InvalidateBankData. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Invalidates a bank range: sound command 0x1f. */
extern void PushCommand_impl(int cmd, unsigned int start, unsigned int end, int a, int b);

void func_0200ec94(unsigned int start, unsigned int end) {
    PushCommand_impl(0x1f, start, end, 0, 0);
}
