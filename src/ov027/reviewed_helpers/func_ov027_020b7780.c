extern void *func_0202a19c(int size, int align);
extern void func_01ff878c(const void *src, void *dst, int size);
extern void func_020b80f0(int owner, void *obj, unsigned short kind);
void func_ov027_020b7780(int param_1, int param_2) {
    unsigned int n = *(unsigned int *)param_2;
    unsigned int i;
    int p = param_2 + 4;
    for (i = 0; i < n; i++) {
        void *obj = func_0202a19c(*(int *)p - 8, 4);
        func_01ff878c((const void *)(p + 8), obj, *(int *)p - 8);
        func_020b80f0(param_1, obj, *(unsigned short *)(p + 4));
        p += *(int *)p;
    }
}
