/* Invokes the selected object callback at offset four unless the global index is minus one.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov025/calls/func_ov025_0208516c.c. */
extern int data_020bea84[];
extern char data_020be930[];

void func_ov039_020bcef0(int arg0)
{
    int index = data_020bea84[0];

    if (index != -1) {
        ((void (*)(int))*(int *)(*(char **)(data_020be930 + index * 8) + 4))(arg0);
    }
}
