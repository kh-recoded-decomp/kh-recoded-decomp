/* Based on src/auto/func_020149b0.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
unsigned short ReadAndAdvanceHalfword(unsigned short **cursor)
{
    unsigned short *valuePointer = *cursor;
    unsigned short value = *valuePointer++;
    *cursor = valuePointer;
    return value;
}
