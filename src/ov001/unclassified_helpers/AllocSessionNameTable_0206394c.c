#include "nitro/types.h"

typedef struct NameTable {
    u8 pad_00[0xa];
    u8 count;
    u8 pad_0b;
    char **names;
} NameTable;

typedef struct Session {
    u8 pad_0000[0x27e8];
    NameTable nameTable;
} Session;

extern Session *data_ov001_020a0460;
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void func_01ff86fc(u32 value, void *destination, u32 size);

void AllocSessionNameTable_0206394c(int count) {
    NameTable *table = &data_ov001_020a0460->nameTable;
    u32 size = count * 4;
    char **names;
    table->count = count;
    names = NNSi_FndAllocFromDefaultHeap_0202a178(size);
    table->names = names;
    func_01ff86fc(0, names, size);
}
