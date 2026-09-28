/* Based on src/auto/func_020255d4.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
int func_0202d3e0(int *objectBase, int recordIndex, int entryIndex)
{
    int *table = ((int **)(objectBase + recordIndex))[2];
    return table ? ((int **)(table + entryIndex))[1] : 0;
}
