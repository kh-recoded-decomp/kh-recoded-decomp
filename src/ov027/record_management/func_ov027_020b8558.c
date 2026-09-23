/* Behavior: Searches an entry array for an active item with the requested identifier.
 * Inputs/outputs and evidence: Checks the active marker and ID, then returns the matching slot or the one-past-end slot when absent.
 * Uncertainty: Return-on-miss behavior follows the loop and is not a null result.
 * Source: khdays-decomp/src/overlays/ov000/auto/func_ov000_02055fc0.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
struct Entry {
    unsigned short entryId;
    short padding;
    int value4;
    int value8;
    int isActive;
};

struct EntryArrayOwner {
    char padding0[0x14];
    struct Entry *entries;
    char padding18[0x38 - 0x18];
    int entryCount;
};

struct Entry *func_ov027_020b8558(struct EntryArrayOwner *owner, int entryId) {
    int entryIndex;
    for (entryIndex = 0; entryIndex < owner->entryCount; entryIndex++) {
        if (owner->entries[entryIndex].isActive != 0) {
            if (entryId == owner->entries[entryIndex].entryId) {
                break;
            }
        }
    }
    return &owner->entries[entryIndex];
}
