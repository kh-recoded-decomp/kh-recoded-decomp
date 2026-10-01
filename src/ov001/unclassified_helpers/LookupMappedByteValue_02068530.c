#include "nitro/types.h"

typedef struct {
    u8 pad[0x109];
    u8 count;
    u8 ids[0x16];
    u8 values[1];
} MapTable;

extern MapTable *data_ov001_020a0470;

u8 LookupMappedByteValue_02068530(u32 id) {
    MapTable *table = data_ov001_020a0470;
    int i = 0;
    while (i < table->count) {
        if (id == table->ids[i]) {
            return table->values[i];
        }
        i++;
    }
    return 0x28;
}
