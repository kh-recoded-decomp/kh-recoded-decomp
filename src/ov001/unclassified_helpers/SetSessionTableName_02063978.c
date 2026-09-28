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
extern int Strlen_02021e44(const char *s);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern char *strcpy_02021e60(char *dst, const char *src);

void SetSessionTableName_02063978(int index, const char *name) {
    NameTable *table = &data_ov001_020a0460->nameTable;
    int length = Strlen_02021e44(name);
    table->names[index] = NNSi_FndAllocFromDefaultHeap_0202a178(length + 1);
    strcpy_02021e60(table->names[index], name);
}
