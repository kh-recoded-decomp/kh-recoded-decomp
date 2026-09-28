extern void func_020737c4(int mode);
extern int func_02011c78(void *cb);
extern void func_020737d4(int result);
extern void func_02073cec(void);

int func_ov015_02073cbc(void) {
    int r;

    func_020737c4(3);
    r = func_02011c78(&func_02073cec);
    if (r == 2) {
        return 1;
    }
    func_020737d4(r);
    return 0;
}
