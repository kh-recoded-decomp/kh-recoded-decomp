/* Behavior: Returns the first array entry whose second one-bit flag is clear.
 * Inputs/outputs and evidence: Scans up to the stored entry count and returns the first entry with b1 clear, or the end slot.
 * Uncertainty: The flag's application-level meaning and miss handling are unknown.
 * Source: khdays-decomp/src/overlays/ov000/auto/func_ov000_02056050.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
struct Entry {
    char padding0[0x24];
    unsigned char flag0 : 1;
    unsigned char isAvailable : 1;
    unsigned char flagsRemainder : 6;
    char padding25[0xb];
};

struct EntryArrayOwner {
    char padding0[0x10];
    struct Entry *entries;
    char padding14[0x20];
    int entryCount;
};

struct Entry *func_ov027_020b7934(struct EntryArrayOwner *owner) {
    int entryIndex;
    for (entryIndex = 0; entryIndex < owner->entryCount; entryIndex++) {
        if (!owner->entries[entryIndex].isAvailable) break;
    }
    return &owner->entries[entryIndex];
}
