extern void func_ov027_020b8154(int ctx, int element);
struct Elem2 { unsigned char _pad[0xc]; int field_c; };
struct Ctx2 { unsigned char _0[0x14]; struct Elem2 *items; unsigned char _1[0x20]; int count; };
void func_ov027_020b817c(int ctx_) {
    struct Ctx2 *ctx = (struct Ctx2 *)ctx_;
    int i;
    for (i = 0; i < ctx->count; i++) {
        if (ctx->items[i].field_c != 0) {
            func_ov027_020b8154(ctx_, (int)&ctx->items[i]);
        }
    }
}
