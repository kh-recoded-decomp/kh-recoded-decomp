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
