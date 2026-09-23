/* Behavior: Searches a packed table for a name matching the supplied string.
 * Inputs/outputs and evidence: Gets the string length, derives the entry list after a variable-sized header, and returns the first matching entry index or -1.
 * Uncertainty: Table entry layout and the compared key encoding are only partially known.
 * Source: khdays-decomp/src/calls/func_02024fe8.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e.
 */
extern int strlen(void *text);
extern int WM_EndKeySharing_0x0202019c(void *entry, void *name, int nameLength);

int findSharedResourceByName_0202cd8c(unsigned char *table, void *name) {
    int entryIndex;
    unsigned char *entry;
    int nameLength;
    unsigned short entryCount;

    nameLength = strlen(name);
    entryCount = (unsigned short)(*(unsigned short *)(table + 2) & 0x1ff);
    entry = (table + 0x10) + (((unsigned int)((entryCount + 1) / 2) << 17) >> 15);
    entry += entryCount * 4;
    for (entryIndex = 0; entryIndex < entryCount; entryIndex++) {
        if (WM_EndKeySharing_0x0202019c(entry, name, nameLength) == 0) {
            return entryIndex;
        }
        entry += 8;
    }
    return -1;
}
