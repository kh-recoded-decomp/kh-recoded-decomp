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
