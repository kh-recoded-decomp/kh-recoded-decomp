#include "nitro/types.h"

typedef struct ValueTables {
    u8 pad_00[0x38];
    s16 **entries;
} ValueTables;

extern ValueTables *data_020613d0;

int GetTableEntryValue_0205213c(int index)
{
    ValueTables *tables = data_020613d0;

    if (index >= 0 && index < 9) {
        return *tables->entries[index];
    }
    return 0;
}
