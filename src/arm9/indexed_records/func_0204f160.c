/* Based on src/auto/func_020325a0.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
int func_0204f160(int recordBase, int recordIndex)
{
    if (recordIndex < 0)
        return 0;
    return recordBase + 0x10 + recordIndex * 0x8c;
}
