#include "nitro/types.h"

typedef struct {
    u16 unk_00;
    u16 count;
    void **entries;
} RecordArray;

extern void _fp_init_0203056c(void);
extern void func_0202a1c4(void *block);

/* Frees each entry, then the array itself. */
void FreeRecordArrayAndReset_02035178(RecordArray *table) {
    int i = 0;
    if (i < table->count) {
        do {
            if (table->entries[i] != 0) {
                _fp_init_0203056c();
                table->entries[i] = 0;
            }
            i++;
        } while (i < table->count);
    }
    if (table->entries != 0) {
        func_0202a1c4(table->entries);
        table->entries = 0;
    }
    table->count = 0;
    table->unk_00 = 0;
}
