extern void MI_CpuCopy8(void *src, void *dst, int size);
extern int func_020b9f7c(int target);
extern void func_020b79bc(int self, int target);
struct RecordStateFlags { unsigned char unusedFlag : 1, hasPendingData : 1, dataIsCurrent : 1; };
int func_ov027_020b7a30(int record, int sourceTarget) {
    struct RecordStateFlags *recordState = (struct RecordStateFlags *)(record + 0x2c);
    int success = 1;
    if (recordState->hasPendingData) {
        if (recordState->dataIsCurrent == 0) {
            success = 0;
        } else {
            MI_CpuCopy8((void *)(record + 0x24), (void *)sourceTarget, 8);
            *(unsigned char *)(record + 0x2c) &= ~4;
        }
    } else {
        if (func_020b9f7c(sourceTarget) == 0)
            func_020b79bc(record, sourceTarget);
    }
    return success;
}
