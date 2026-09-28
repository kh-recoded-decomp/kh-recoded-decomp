extern unsigned char *func_0204cf58(int value);
extern void func_0204ce84(int unknownMode, int value, int unknownOption);

int func_0204d7b0(int value) {
    unsigned char *pendingRecord = func_0204cf58(0);

    if (pendingRecord == 0 || pendingRecord[0] != 1) {
        func_0204ce84(1, value, 0);
    } else {
        pendingRecord[1] = value;
    }

    return 1;
}
