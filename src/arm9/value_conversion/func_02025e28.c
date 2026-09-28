/* Based on src/auto/func_020219c4.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
int func_02025e28(short *typedValue) {
    int convertedValue = 0;
    if (*typedValue == 1) convertedValue = *(int *)(typedValue + 2) << 0xc;
    else if (*typedValue != 2) convertedValue = *(int *)(typedValue + 2);
    return convertedValue;
}
