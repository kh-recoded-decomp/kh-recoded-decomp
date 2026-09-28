/* Runs a collection helper, then visits records whose word at offset 0x14 is nonzero.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov026/calls/func_ov026_02083330.c. */

extern void func_020b8334(int ctx, int arg);
extern void func_020b7f60(int ctx, int element, int arg);
struct Elem3 { unsigned char _pad[0x14]; int field_14; unsigned char _pad2[0x20]; };
struct Ctx3 { unsigned char _0[0xc]; struct Elem3 *items; unsigned char _1[0x20]; int count; };
void func_ov027_020b7f8c(int ctx_, int arg) {
    struct Ctx3 *ctx = (struct Ctx3 *)ctx_;
    int i;
    func_020b8334(ctx_, arg);
    for (i = 0; i < ctx->count; i++) {
        if (ctx->items[i].field_14 != 0) {
            func_020b7f60(ctx_, (int)&ctx->items[i], arg);
        }
    }
}
