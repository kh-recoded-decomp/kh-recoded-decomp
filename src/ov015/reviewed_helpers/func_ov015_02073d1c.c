extern int func_02011840(void *handler);
extern void func_020737d4(int id);
extern void func_02073d44(int req);

int func_ov015_02073d1c(void) {
    int r = func_02011840(&func_02073d44);
    if (r != 2) {
        func_020737d4(r);
        return 0;
    }
    return 1;
}
