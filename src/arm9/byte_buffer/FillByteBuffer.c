/* Based on src/auto/func_02025830.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
/* The cursor advances by requestedCount even when the write is capacity-clamped. */
void FillByteBuffer(unsigned int *bufferState, unsigned char fillValue, unsigned int requestedCount) {
    unsigned int byteOffset;
    unsigned int writeCount;
    if ((int)requestedCount > 0) {
        writeCount = bufferState[0];
        if (writeCount > requestedCount) {
            writeCount = requestedCount;
        }
        byteOffset = 0;
        if (byteOffset < writeCount) {
            do {
                *(unsigned char *)(bufferState[1] + byteOffset) = fillValue;
                byteOffset++;
            } while (byteOffset < writeCount);
        }
        bufferState[0] = bufferState[0] - writeCount;
        bufferState[1] = bufferState[1] + requestedCount;
    }
}
