/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern void OS_Terminate(void);
extern unsigned short data_02056b48;

void func_0200202c(int unused, int status) {
    if ((unsigned int)((status & 0x7f00) << 8) >> 16 == 0x10) {
        data_02056b48 = 1;
        return;
    }
    OS_Terminate();
}
