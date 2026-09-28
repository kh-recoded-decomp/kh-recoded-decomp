/* Enqueues a command with four arguments for changing the output selector.
 * Uncertainty: Argument meanings depend on the caller/API contract. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_SetOutputSelector.c.
 * Original routine: SND_SetOutputSelector. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Sound command 0x19. */
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void func_0200ecd4(int a, int b, int c, int d) {
    PushCommand_impl(0x19, a, b, c, d);
}
