extern void ReleaseTrackerScreenResource(int ctx, int element);
struct Elem2 { unsigned char _pad[0xc]; int field_c; };
struct Ctx2 { unsigned char _0[0x14]; struct Elem2 *items; unsigned char _1[0x20]; int count; };
void ReleaseAllTrackerScreenResources(int ctx_) {
    struct Ctx2 *ctx = (struct Ctx2 *)ctx_;
    int i;
    for (i = 0; i < ctx->count; i++) {
        if (ctx->items[i].field_c != 0) {
            ReleaseTrackerScreenResource(ctx_, (int)&ctx->items[i]);
        }
    }
}
