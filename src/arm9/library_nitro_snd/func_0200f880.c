/* Clears linked wave-archive ownership nodes while holding the sound mutex and flushes each node.
 * Uncertainty: Prepared-source helper names were stale; behavior here is derived from the body and target data layout. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/snd/calls/SND_DestroyWaveArc.c.
 * Original routine: SND_DestroyWaveArc. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
/* Unlinks and clears the whole wave-archive chain under the sound mutex. */
extern void func_0200edc8(void);
extern void func_0200eddc(void);
extern void DC_StoreRange(void *p, unsigned int len);

void func_0200f880(int **owner) {
    int *node;
    int zero;
    int len;
    int *next;
    func_0200edc8();
    node = (int *)owner[6];
    if (node != 0) {
        zero = 0;
        len = 8;
        do {
            next = (int *)node[1];
            node[0] = zero;
            node[1] = zero;
            DC_StoreRange(node, len);
            node = next;
        } while (next != 0);
    }
    func_0200eddc();
}
