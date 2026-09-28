/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
void func_02013498(int *p)
{
    int *node = (int *)p[0x2c / 4];
    while (node != 0) {
        node[8 / 4] = p[0x1c / 4];
        node = (int *)node[0xc / 4];
    }
    p[0x28 / 4] = p[0x1c / 4];
}
