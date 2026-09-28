/* Based on src/auto/func_02025894.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
/* The cursor advances by requestedCount even when the write is capacity-clamped. */
void CopyIntoByteBuffer(unsigned int *bufferState, char *sourceBytes, unsigned int requestedCount) {
    unsigned int byteOffset;
    unsigned int copyCount;
    if ((int)requestedCount > 0) {
        copyCount = bufferState[0];
        if (copyCount > requestedCount) {
            copyCount = requestedCount;
        }
        byteOffset = 0;
        if (byteOffset < copyCount) {
            do {
                *(unsigned char *)(bufferState[1] + byteOffset) = sourceBytes[byteOffset];
                byteOffset++;
            } while (byteOffset < copyCount);
        }
        bufferState[0] = bufferState[0] - copyCount;
        bufferState[1] = bufferState[1] + requestedCount;
    }
}
