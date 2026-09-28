/* Enqueues a command to set volume for a channel mask.
 * Uncertainty: The volume scale is defined by the sound API. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_SetChannelVolume.c.
 * Original routine: SND_SetChannelVolume. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Sound command 0x14. */
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void func_0200ebe0(int a, int b, int c) {
    PushCommand_impl(0x14, a, b, c, 0);
}
