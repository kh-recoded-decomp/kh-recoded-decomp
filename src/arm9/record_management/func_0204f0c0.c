extern void func_0204e904(void *recordArray, void *recordPayload);

void func_0204f0c0(unsigned char *recordArray, int recordIndex) {
    int recordOffset;
    int *recordFlags;

    if (recordIndex < 0) {
        return;
    }

    recordOffset = recordIndex * 0x8c;
    recordFlags = (int *)(recordArray + 0x7c + recordOffset);
    if (((unsigned int)(*recordFlags << 31) >> 31) == 0) {
        return;
    }

    func_0204e904(recordArray, recordArray + 4 + recordOffset);
    *recordFlags &= ~1;
}
