/* Enqueues a track-parameter command, packing the player and immediate flag and carrying the track mask, parameter and value.
 * Uncertainty: Parameter codes and flag use are caller-defined. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SNDi_SetTrackParam.c.
 * Original routine: SNDi_SetTrackParam. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Sound command 7; the immediate flag rides in the top byte of the track mask. */
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void func_0200ed24(int player, unsigned int trackMask, int param, int value, int immediate) {
    PushCommand_impl(7, player | (immediate << 24), trackMask, param, value);
}
