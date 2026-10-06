extern void CreateWidget(int ctx, int element);
extern void LinkElementNeighbors(int ctx, int element);
void func_ov027_020b8f7c(int ctx, int base, int count) {
    int i;
    for (i = 0; i < count; i++) {
        CreateWidget(ctx, base + i * 0x58);
    }
    for (i = 0; i < count; i++) {
        LinkElementNeighbors(ctx, base + i * 0x58);
    }
}
