/* Enqueues a command to prepare sequence data for a player.
 * Uncertainty: Sequence identity/data interpretation is caller-defined. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_PrepareSeq.c.
 * Original routine: SND_PrepareSeq. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Sound command 0x2. */
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void func_0200e9b4(int a, int b, int c, int d) {
    PushCommand_impl(0x2, a, b, c, d);
}
