/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern int func_02025de4(void *a, void *b);
extern int func_0204d670(int x);

int func_020267a4(void *p, char *buf)
{
    int saved;
    saved = func_02025de4(p, buf);
    func_02025de4(p, buf + 8);
    func_0204d670(saved);
    return 1;
}
