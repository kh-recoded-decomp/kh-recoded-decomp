/* Enqueues a command with four arguments for setting player parameters.
 * Uncertainty: Parameter semantics are not shown in this wrapper. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SNDi_SetPlayerParam.c.
 * Original routine: SNDi_SetPlayerParam. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Sound command 0x6. */
extern void PushCommand_impl(int cmd, int a, int b, int c, int d);

void func_0200ecfc(int a, int b, int c, int d) {
    PushCommand_impl(0x6, a, b, c, d);
}
