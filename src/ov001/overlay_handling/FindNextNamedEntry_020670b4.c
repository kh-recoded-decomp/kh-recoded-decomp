/* Searches a fixed-size name table from a caller index and returns the next match. Evidence: Source implementation directly performs the described operations; see src/overlays/ov002/calls/func_ov002_020713cc.c. Uncertainty: No material uncertainty for the stated operation; game-specific use may depend on callers. Recovered from Days source src/overlays/ov002/calls/func_ov002_020713cc.c; CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */
typedef unsigned short u16;

extern int strncmp(const char *unknown_argument_a, const char *unknown_argument_b, int unknown_argument_n);

char *FindNextNamedEntry_020670b4(char *table_owner, const char *wanted_name, int name_length, int *search_index) {
    if (*search_index < *(u16 *)(table_owner + 0x82)) {
        do {
            long entry_offset = *search_index * 0x14;
            char *entry_table = *(char **)(table_owner + 0xac);

            if (strncmp(entry_table + entry_offset, wanted_name, name_length) == 0) {
                return entry_table + entry_offset;
            }
            *search_index = *search_index + 1;
        } while (*search_index < *(u16 *)(table_owner + 0x82));
    }
    return 0;
}
