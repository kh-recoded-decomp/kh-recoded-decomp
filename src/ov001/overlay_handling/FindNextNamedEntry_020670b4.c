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
