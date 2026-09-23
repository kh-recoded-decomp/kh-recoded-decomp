/* Behavior: Releases one indexed 0x8c-byte record when its active bit is set.
 * Inputs/outputs and evidence: Rejects negative index or inactive record, calls a release helper, then clears the active bit.
 * Uncertainty: Record layout and release-helper semantics are only known from offsets.
 * Source: khdays-decomp/src/calls/func_02032450.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
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
