extern int CopyRecentInputRecords();
extern int MI_CpuCopy8();

struct AvailableRecord {
    int word0;
    short halfword4;
    unsigned short marker6;
};

int func_ov027_020b79dc(int unusedArgument, int sourceRecord) {
    struct AvailableRecord recordTable[4];
    int recordIndex;
    int lastRecordIndex;

    lastRecordIndex = CopyRecentInputRecords(recordTable) - 1;
    for (recordIndex = lastRecordIndex; recordIndex >= 0; recordIndex--) {
        if (recordTable[recordIndex].marker6 == 0) {
            MI_CpuCopy8(&recordTable[recordIndex], sourceRecord, 8);
            return sourceRecord;
        }
    }
    MI_CpuCopy8(&recordTable[lastRecordIndex], sourceRecord, 8);
    return sourceRecord;
}
