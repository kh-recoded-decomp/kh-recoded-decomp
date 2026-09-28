/* CC0 source: Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/os/auto/OSi_DequeueItem.c. */
void OSi_DequeueItem(int *r0, int *r1)
{
    int *r2 = (int *)r1[4];
    int *next = (int *)r1[5];

    if (r2 == 0) {
        r0[35] = (int)next;
    } else {
        r2[5] = (int)next;
    }

    if (next == 0) {
        r0[34] = (int)r2;
    } else {
        next[4] = (int)r2;
    }
}
