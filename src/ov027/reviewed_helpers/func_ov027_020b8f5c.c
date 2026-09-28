extern void func_020b8cbc(int ctx, int element);
extern void func_020b85d0(int ctx, int element);
void func_ov027_020b8f5c(int ctx, int base, int count) {
    int i;
    for (i = 0; i < count; i++) {
        func_020b8cbc(ctx, base + i * 0x58);
    }
    for (i = 0; i < count; i++) {
        func_020b85d0(ctx, base + i * 0x58);
    }
}
