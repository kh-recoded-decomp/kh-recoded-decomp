/* Based on src/auto/func_020326a8.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
int func_0204f2c0(int recordBase, int recordIndex)
{
    int *recordFlags;
    if (recordIndex < 0)
        return recordBase;
    recordFlags = (int *)(recordBase + 0x7c + recordIndex * 0x8c);
    return *recordFlags |= 2;
}
