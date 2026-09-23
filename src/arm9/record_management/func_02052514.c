/* Behavior: Clears a 0x1c-byte record, stores four supplied values, and clears three low flag bits.
 * Inputs/outputs and evidence: The body performs a zero-fill, four field assignments, and three bit clears.
 * Uncertainty: Record field purposes are unknown; field layout is retained from the source.
 * Source: khdays-decomp/src/calls/func_02035fb0.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
extern void MI_CpuFill8(void *dst, unsigned char val, unsigned int size);

struct SmallRecord {
    int field0;
    int field4;
    int field8;
    int fieldC;
    char _10[8];
    unsigned int flags;
};

void func_02052514(struct SmallRecord *record, int value0, int value1, int value2, int value3) {
    MI_CpuFill8(record, 0, 0x1c);
    record->field0 = value0;
    record->field8 = value1;
    record->fieldC = value2;
    record->field4 = value3;
    record->flags &= ~1;
    record->flags &= ~2;
    record->flags &= ~4;
}
