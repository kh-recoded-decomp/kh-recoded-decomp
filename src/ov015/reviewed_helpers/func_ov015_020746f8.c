extern void func_020737c4(int mode);
extern int func_020116e8(void *cb);
extern void func_020737d4(int result);
extern void func_02074728(void);

int func_ov015_020746f8(void) {
    int r;

    func_020737c4(3);
    r = func_020116e8(&func_02074728);
    if (r == 2) {
        return 1;
    }
    func_020737d4(r);
    return 0;
}
