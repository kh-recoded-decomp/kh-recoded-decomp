/* Enqueues a timer-start command with the supplied four arguments.
 * Uncertainty: Timer timing units are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_StartTimer.c.
 * Original routine: SND_StartTimer. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Sound command 0xc. */
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void func_0200ead4(int a, int b, int c, int d) {
    PushCommand_impl(0xc, a, b, c, d);
}
