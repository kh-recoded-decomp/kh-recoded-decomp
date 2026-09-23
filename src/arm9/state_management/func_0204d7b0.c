/* Behavior: Stores a value in an existing pending record or asks a helper to create/update that record.
 * Inputs/outputs and evidence: When state is absent or has a different tag, calls a helper; otherwise writes byte 1, then returns success.
 * Uncertainty: The record tag and value's meaning are unknown.
 * Source: khdays-decomp/src/calls/func_02033660.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
extern unsigned char *func_0204cf58(int value);
extern void func_0204ce84(int unknownMode, int value, int unknownOption);

int func_0204d7b0(int value) {
    unsigned char *pendingRecord = func_0204cf58(0);

    if (pendingRecord == 0 || pendingRecord[0] != 1) {
        func_0204ce84(1, value, 0);
    } else {
        pendingRecord[1] = value;
    }

    return 1;
}
