#include "nitro/types.h"

typedef struct LevelRecord {
    u32 value;
    u32 base;
    u32 statA;
    u32 statB;
    u32 statC;
} LevelRecord;

typedef struct LevelEntry {
    u32 value;
    u16 base;
    u8 statA;
    u8 statB;
    u8 statC;
    u8 pad_09[3];
} LevelEntry;

extern char data_0205616c[];
extern LevelEntry data_02060f1c[];
extern LevelRecord *func_0202c48c(const char *path, int flags);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void LoadLevelTable_0204f5f4(void)
{
    LevelRecord *records = func_0202c48c(data_0205616c, 0x11);
    LevelRecord *record = records;
    int i;

    for (i = 0; i < 99; i++) {
        data_02060f1c[i].value = record->value;
        data_02060f1c[i].base = record->base;
        data_02060f1c[i].statA = record->statA;
        data_02060f1c[i].statB = record->statB;
        data_02060f1c[i].statC = record->statC;
        record++;
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(records);
}
