/* Based on src/auto/func_020255bc.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
int func_0202d3c8(int *objectBase, int recordIndex)
{
    int *table = ((int **)(objectBase + recordIndex))[2];
    if (table != 0)
        return *table;
    return 0;
}
