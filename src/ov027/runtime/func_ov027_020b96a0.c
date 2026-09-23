/* Checks two record fields and forwards each value that is not -1 with the supplied context and mode.
 * Evidence: Indices 5 and 6 and sentinel check in source.
 * Uncertainty: Meaning of the two record entries and helper operation are not established.
 * Source: src/overlays/ov000/calls/func_ov000_02055e10.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */

extern void func_0204f204(int unknownContext, int recordValue, int unknownMode);

void func_ov027_020b96a0(int context, int record, int mode) {
    int entryIndex;
    for (entryIndex = 0; entryIndex < 2; entryIndex++) {
        int entryValue = ((int *)record)[entryIndex + 5];
        if (entryValue != -1) {
            func_0204f204(context, entryValue, mode);
        }
    }
}
