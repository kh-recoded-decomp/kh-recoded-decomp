extern int func_02025de4(int owner, void *entry);
extern int func_02025e18(int owner, int handle);
extern int func_02063fe4(int handle);
extern int func_020a8918(void);

int func_ov003_020647b8(int owner, void *entry) {
    int len;
    int pos;

    len = func_02025de4(owner, entry);
    if (func_02063fe4(func_02025e18(owner, len)) == 0) {
        return 1;
    }
    if (len == 0) {
        return 0;
    }

    pos = func_020a8918();
    if (pos < len) {
        return 0;
    }
    if (pos >= len) {
        return 1;
    }
    return 1;
}
