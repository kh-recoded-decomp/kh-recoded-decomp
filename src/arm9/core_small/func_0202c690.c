/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern char data_02060564[];
extern void func_0202c184();
extern void func_0202c1c8();
extern void func_0202c19c();
extern void func_0202c1e0();

void func_0202c690(int arg0) {
    if (arg0 == 0) {
        *(void **)(data_02060564 + 0xc) = (void *)func_0202c19c;
        *(void **)(data_02060564 + 0x10) = (void *)func_0202c1e0;
    } else {
        *(void **)(data_02060564 + 0xc) = (void *)func_0202c184;
        *(void **)(data_02060564 + 0x10) = (void *)func_0202c1c8;
    }
}
