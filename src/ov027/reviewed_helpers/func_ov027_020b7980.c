/* Finds the first sixteen-byte array record whose word at offset twelve is zero, or returns the end pointer.
 * Higher-level purpose remains unclassified. Recovered CC0 C from
 * Yokimitsuro/khdays-decomp, ab832f38b943c15f461228968a89002e1a99c03e,
 * src/overlays/ov026/auto/func_ov026_02082dac.c. */
struct Element {
    int unk0;
    int unk4;
    int unk8;
    int field_c;
};

struct Obj {
    char pad[0x14];
    struct Element *elems;
    char pad2[0x38 - 0x14 - 4];
    int count;
};

struct Element *func_ov027_020b7980(struct Obj *obj) {
    int i;
    for (i = 0; i < obj->count; i++) {
        if (obj->elems[i].field_c == 0) {
            break;
        }
    }
    return &obj->elems[i];
}
