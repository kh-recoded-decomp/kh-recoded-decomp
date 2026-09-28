/* Invokes a second table object callback at offset eight unless its global index is minus one.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov025/calls/func_ov025_0208527c.c. */
extern int data_020bea84[];
extern char data_020be8d0[];

void func_ov039_020bd054(int arg0)
{
    int index = data_020bea84[1];

    if (index != -1) {
        ((void (*)(int))*(int *)(*(char **)(data_020be8d0 + index * 8) + 8))(arg0);
    }
}
