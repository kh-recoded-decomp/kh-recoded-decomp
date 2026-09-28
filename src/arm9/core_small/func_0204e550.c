/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern unsigned int func_02014ba8(unsigned int a, unsigned int b);
extern void func_02015760(void *p, unsigned int v, void *q);

void func_0204e550(void *p, unsigned int a, void *q, int b)
{
    unsigned int v;
    if (b < 0) return;
    v = func_02014ba8(a, (unsigned int)(unsigned short)b);
    func_02015760(p, v, q);
}
