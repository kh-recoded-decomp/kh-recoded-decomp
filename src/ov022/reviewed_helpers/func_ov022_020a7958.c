extern int func_02025de4(int owner, void *entry);
extern int func_02025e18(int owner, int handle);
extern int func_020a73d8(int handle);
extern int func_020a8918(void);

int func_ov022_020a7958(int owner, void *entry) {
    int len;
    int pos;

    len = func_02025de4(owner, entry);
    if (func_020a73d8(func_02025e18(owner, len)) == 0) {
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
