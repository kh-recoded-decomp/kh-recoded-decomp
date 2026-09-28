/* Adapted from CC0-1.0 source Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov024/calls/func_ov024_02084e94.c.
 * Runs the observed pre-initialization hook before setting up movie decode
 * state from the stream, preserving the target static object address.
 */
/* initializeMovieStreamWrapper_020a9170 -- MobiClip: decoder-init trampoline.
 * Runs the pre-init hook against the static object at 0x02000bc4 before handing over to the
 * real init. */
extern void func_02000b64(void *p);
extern int func_ov022_020a9430(int *ctx, int cursor, unsigned int a);

int initializeMovieStreamWrapper_020a9170(int *ctx, int cursor, unsigned int a) {
    func_02000b64((void *)0x02000bc4);
    return func_ov022_020a9430(ctx, cursor, a);
}
