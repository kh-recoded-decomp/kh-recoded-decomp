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

struct Entry *func_ov027_020b789c(struct EntryArrayOwner *owner, int entryId) {
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
