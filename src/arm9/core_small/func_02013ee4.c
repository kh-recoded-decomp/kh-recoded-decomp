/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */
extern void DC_FlushRange(const void *addr, unsigned size);
extern void *data_02052efc[];

int func_02013ee4(int *job, int do_flush) {
    int (*fn)(void *, int, int);
    fn = (int (*)(void *, int, int))data_02052efc[job[0]];
    if (do_flush) DC_FlushRange((void *)job[1], (unsigned)job[3]);
    return fn((void *)job[1], job[2], job[3]);
}
