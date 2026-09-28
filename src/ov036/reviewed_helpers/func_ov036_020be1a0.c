extern int func_02025de4(void *self, void *desc);
extern void func_020bcd08(int a, int b, int c, int d);

int func_ov036_020be1a0(void *self, char *descs) {
    int a = func_02025de4(self, descs);
    int b = func_02025de4(self, descs + 8);
    int c = func_02025de4(self, descs + 0x10);
    int d = func_02025de4(self, descs + 0x18);

    func_020bcd08(a, b, c, d);
    return 1;
}
