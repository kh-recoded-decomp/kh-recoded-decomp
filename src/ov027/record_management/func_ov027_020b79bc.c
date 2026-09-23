/* Behavior: Copies an eight-byte value into a record selected from a four-entry list.
 * Inputs/outputs and evidence: Scans records backward for a zero marker and copies to that entry, falling back to the last entry.
 * Uncertainty: Record marker and list helper semantics are unknown; argument a is unused by the recovered body.
 * Source: khdays-decomp/src/overlays/ov000/calls/func_ov000_020560d0.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
extern int func_0202b6d0();
extern int MI_CpuCopy8();

struct AvailableRecord {
    int word0;
    short halfword4;
    unsigned short marker6;
};

int func_ov027_020b79bc(int unusedArgument, int sourceRecord) {
    struct AvailableRecord recordTable[4];
    int recordIndex;
    int lastRecordIndex;

    lastRecordIndex = func_0202b6d0(recordTable) - 1;
    for (recordIndex = lastRecordIndex; recordIndex >= 0; recordIndex--) {
        if (recordTable[recordIndex].marker6 == 0) {
            MI_CpuCopy8(&recordTable[recordIndex], sourceRecord, 8);
            return sourceRecord;
        }
    }
    MI_CpuCopy8(&recordTable[lastRecordIndex], sourceRecord, 8);
    return sourceRecord;
}
