/* Loads a resource of kind fourteen, processes its three relative-offset sections, and releases the buffer.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov026/calls/func_ov026_0208325c.c. */

extern int func_0202c48c(int param2, int type);
extern void func_020b7780(int ctx, int section);
extern void func_020b77c0(int ctx, int section);
extern void func_020b7828(int ctx, int section);
extern void func_0202a1c4(int ptr);
void func_ov027_020b7e24(int ctx, int param2) {
    int *buf = (int *)func_0202c48c(param2, 0xe);
    int a = buf[0], c = buf[2], b = buf[1];
    func_020b7780(ctx, (int)buf + a);
    func_020b77c0(ctx, (int)buf + b);
    func_020b7828(ctx, (int)buf + c);
    if (buf != 0) {
        func_0202a1c4((int)buf);
    }
}
