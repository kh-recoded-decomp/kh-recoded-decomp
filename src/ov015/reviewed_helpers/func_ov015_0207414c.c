extern int func_0201193c(void *handler);
extern void func_020737d4(int id);
extern void func_02074174(int req);

int func_ov015_0207414c(void) {
    int r = func_0201193c(&func_02074174);
    if (r != 2) {
        func_020737d4(r);
        return 0;
    }
    return 1;
}
