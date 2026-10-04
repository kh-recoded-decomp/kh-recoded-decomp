#include "nitro/types.h"

typedef struct {
    u8 pad[0x20];
    void **cells;
    int width;
    int height;
    int count;
} GridTable;

typedef struct {
    u8 pad[0x110a4];
    GridTable table;
} GridWork;

extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void FreeGridCells_020c098c(GridWork *work) {
    GridTable *table = &work->table;
    int i;

    if (table->cells == NULL) {
        return;
    }
    for (i = 0; i < table->count; i++) {
        if (table->cells[i] != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(table->cells[i]);
            table->cells[i] = NULL;
        }
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(table->cells);
    table->cells = NULL;
}