/* Based on src/auto/func_02025694.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
int GetPackedBitMask(int *bitWords, int bitIndex) {
    int wordIndex = bitIndex / 32;
    bitIndex = 31 - (bitIndex & 0x1f);
    return bitWords[wordIndex] & (1U << bitIndex);
}
