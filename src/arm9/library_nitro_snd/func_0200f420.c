/* Repeatedly requests command processing until the request is accepted.
 * Uncertainty: The command processor’s scheduling behavior is outside this function. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/RequestCommandProc.c.
 * Original routine: RequestCommandProc. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Retries the PXI request until it is accepted. */
extern int func_0200e30c(int a, int b, int c);

void func_0200f420(void) {
    int cmd = 7;
    int zero = 0;
    while (func_0200e30c(cmd, zero, zero) < 0) {
        ;
    }
}
