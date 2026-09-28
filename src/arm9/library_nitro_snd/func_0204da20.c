/* Applies the same channel operation argument to player numbers 2 through 31.
 * Uncertainty: The callee operation is sound-player control; no game-specific player roles are known. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SNDi_BroadcastChannelOp.c.
 * Original routine: SNDi_BroadcastChannelOp. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
extern void func_0201d5f0(int a, int b);

void func_0204da20(int arg0)
{
    int i;
    for (i = 2; i < 0x20; i++) {
        func_0201d5f0(i, arg0);
    }
}
