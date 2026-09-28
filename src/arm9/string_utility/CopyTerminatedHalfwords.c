/* Based on src/auto/func_020200e4.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
unsigned short *CopyTerminatedHalfwords(unsigned short *destination, unsigned short *source) {
    unsigned short *destinationCursor = destination, *destinationSlot;
    unsigned short copiedValue;
    do {
        destinationSlot = destinationCursor++;
        *destinationSlot = *source++;
        copiedValue = *(volatile unsigned short *)destinationSlot;
    } while (copiedValue != 0);
    return destination;
}
