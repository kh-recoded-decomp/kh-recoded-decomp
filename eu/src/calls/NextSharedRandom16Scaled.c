/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */

/* Existing BSS owner has exactly these three 32-bit words. */
extern unsigned int gSharedRandom32State[3];
unsigned int NextSharedRandom16Scaled(unsigned int range) {
    unsigned int *st = gSharedRandom32State;
    unsigned int r = st[1] * st[0] + st[2];
    st[0] = r;
    if (range == 0) {
        return (unsigned short)(r >> 16);
    }
    return (unsigned short)(((r >> 16) * range) >> 16);
}
