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
