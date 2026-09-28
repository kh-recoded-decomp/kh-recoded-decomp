/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */

extern int data_0206055c[];
extern void *data_02060394;
extern void *func_0202a1e4(int size, void *heap);

void func_0202b760(int n) {
    if (data_0206055c[1] == 0) {
        data_0206055c[1] = (int)func_0202a1e4(0x40, data_02060394);
    }
    *(short *)data_0206055c = (short)n;
}
