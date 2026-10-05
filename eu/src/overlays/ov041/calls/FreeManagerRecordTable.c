#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x4bc];
    u32 *records[0x1b];
} Manager;

extern u32 data_ov035_020bc4e0;
extern void ZeroHalfThenFree(u32 value);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void FreeManagerRecordTable(void) {
    Manager *manager;
    u32 *entry;
    int i;

    manager = *(Manager **)(data_ov035_020bc4e0 + 0xb8);
    i = 0;
    do {
        entry = manager->records[i];
        if (entry != NULL) {
            ZeroHalfThenFree(*entry);
            NNSi_FndFreeFromDefaultHeap(manager->records[i]);
        }
        i = i + 1;
    } while (i < 0x1b);
}
