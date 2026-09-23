/* Behavior: Copies an eight-byte pending record to a target or registers the target for later updates.
 * Inputs/outputs and evidence: Checks two state bits, copies and clears one flag for ready records, returns failure for stale records, otherwise conditionally registers the target.
 * Uncertainty: The bit meanings and object relationship are inferred from branches; no actor identity is established.
 * Source: khdays-decomp/src/overlays/ov000/calls/func_ov000_02056144.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
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
