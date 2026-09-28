/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern void func_020195f4(void);
extern int data_0205a924[];
extern int data_0205aa5c[];


int func_0201968c(void) {
    if ((data_0205a924[0x35] & 0x80) == 0) {
        func_020195f4();
        data_0205a924[0x35] |= 0x80;
    }
    return (int)data_0205aa5c;
}
