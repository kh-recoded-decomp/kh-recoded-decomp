/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern void func_01ff86fc(unsigned int data, void *dst, unsigned int size);
extern unsigned short data_020604fc[];
extern int data_02060504[];

int func_0202aba8(void)
{
    data_020604fc[1] = 0;
    data_020604fc[2] = 0;
    data_020604fc[0] = 0;
    func_01ff86fc(0, data_02060504, 0x30);
    return 1;
}
