#include "nitro/types.h"

typedef struct {
    void **entries;
    s8 count;
} Registry;

extern Registry *data_ov001_020a04d8;

int FindRegisteredEntryIndex_0207ee7c(void *value) {
    int i = 0;
    while (i < data_ov001_020a04d8->count) {
        if (data_ov001_020a04d8->entries[i] == value) {
            return i;
        }
        i++;
    }
    return -1;
}
