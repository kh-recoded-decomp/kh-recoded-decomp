/* Behavior: Obtains a buffer from an object and clears it when a flag requests initialization.
 * Inputs/outputs and evidence: Calls an allocator/helper with an embedded field address; on non-null result, conditionally zeroes the returned buffer for the stored size.
 * Uncertainty: The object fields' higher-level meaning is unknown; helper identifiers remain address based.
 * Source: khdays-decomp/src/calls/func_02010ce4.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
extern void *func_0201360c(void *descriptor);
extern void INITi_CpuClear32_0x01ff86fc(unsigned int data, void *dst, unsigned int bufferSize);

typedef struct {
    char padding[0x20];
    unsigned int descriptorFlags;
    char allocationRequest[4];
    unsigned int bufferSize;
} BufferDescriptor;

void *allocateAndOptionallyClearBuffer_02013624(BufferDescriptor *descriptor)
{
    void *buffer = func_0201360c(&descriptor->allocationRequest);

    if (buffer != 0) {
        unsigned char descriptorFlags = descriptor->descriptorFlags;
        unsigned int bufferSize = descriptor->bufferSize;

        if (descriptorFlags & 1)
            INITi_CpuClear32_0x01ff86fc(0, buffer, bufferSize);
    }

    return buffer;
}
