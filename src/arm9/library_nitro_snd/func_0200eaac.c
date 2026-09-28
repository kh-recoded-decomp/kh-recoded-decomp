/* Enqueues a command configuring a player’s allocatable track channels.
 * Uncertainty: Player/channel interpretation is caller-supplied. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_SetTrackAllocatableChannel.c.
 * Original routine: SND_SetTrackAllocatableChannel. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Sound command 0x9. */
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void func_0200eaac(int a, int b, int c) {
    PushCommand_impl(0x9, a, b, c, 0);
}
