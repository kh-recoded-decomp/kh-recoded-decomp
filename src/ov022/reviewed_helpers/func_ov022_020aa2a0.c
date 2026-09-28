extern void func_0200b1e4(int *file);

void func_ov022_020aa2a0(int cur) {
    if (*(unsigned char *)(cur + 0x10) == 1) {
        func_0200b1e4(*(int **)(cur + 0xc));
    }
    *(unsigned char *)(cur + 0x10) = 0;
}
