/* Clears one bit in the NNS sound capture/channel-state byte.
 * Uncertainty: This is a higher-level shared sound state helper; the specific channel role is not named by the routine. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_ClearChannelBit.c.
 * Original routine: SND_ClearChannelBit. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
extern struct { int a, b; } data_0205d894;

void func_0201d3d8(int bit) {
    data_0205d894.b &= ~(1 << bit);
}
