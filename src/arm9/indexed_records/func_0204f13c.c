/* Based on src/auto/func_0203257c.c from Yokimitsuro/khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e (CC0-1.0). */
struct TwoWordValue {
    int first;
    int second;
};

struct IndexedRecord {
    char pad0[0x10];
    struct TwoWordValue value;
    char pad1[0x8c - 0x18];
};

void func_0204f13c(struct IndexedRecord *recordBase, int recordIndex, struct TwoWordValue *sourceValue) {
    if (recordIndex < 0) return;
    recordBase[recordIndex].value = *sourceValue;
}
