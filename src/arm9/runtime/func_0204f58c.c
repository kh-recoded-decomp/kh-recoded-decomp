/* Clears a record, copies two nonnegative limits from an optional source with defaults, and clears the remaining short body.
 * Evidence: Clear sizes, source tests, defaults, and short stores in source.
 * Uncertainty: Meaning of the two limits is not established.
 * Source: src/calls/func_02036298.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */

extern void MI_CpuFill8(void *p, int v, unsigned int n);
extern void MIi_CpuClear16(int v, void *p, unsigned int n);

int func_0204f58c(short *record, short *limits) {
    MI_CpuFill8(record, 0, 0x1a);
    if (limits != 0) {
        record[1] = limits[0] >= 0 ? (unsigned short)limits[0] : 0xf;
        record[2] = limits[1] >= 0 ? (unsigned short)limits[1] : 4;
    } else {
        record[1] = 0xf;
        record[2] = 4;
    }
    MIi_CpuClear16(0, record + 3, 0x14);
    return 1;
}
