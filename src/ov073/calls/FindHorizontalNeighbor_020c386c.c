#include "nitro/types.h"
#pragma opt_propagation off
#pragma opt_common_subs off
#pragma opt_loop_invariants off

#define ABS_VALUE(value) ((value) < 0 ? -(value) : (value))

typedef struct ListEntry {
    u16 parameters00;
    u16 column;
    u16 row;
    u16 parameters06;
} ListEntry;

typedef struct ListTable {
    u8 reserved00[6];
    u16 count;
    ListEntry entries[1];
} ListTable;

typedef struct ListData {
    u8 reserved00[4];
    ListTable *table;
} ListData;

typedef struct ListView {
    u8 reserved00[4];
    ListData *data;
    u8 reserved08[0xa0];
    int selectedIndex;
} ListView;

int FindHorizontalNeighbor_020c386c(ListView *list, int columnStep)
{

    ListEntry *best;
    int i;
    int distance;
    ListEntry *entry;
    ListEntry *current;
    int bestIndex;
    ListTable *table;
    int targetColumn;
    int count;

    table = list->data->table;
    best = NULL;
    bestIndex = -1;
    current = &table->entries[list->selectedIndex];
    i = 0;
    count = table->count;
    if (count > 0) {
        targetColumn = current->column + columnStep;
        do {
            entry = &table->entries[i];
            if (entry->column == targetColumn) {
                int currentRow = current->row;
                distance = entry->row - currentRow;
                if (best == NULL) {
                    bestIndex = i;
                    best = entry;
                } else {
                    int bestDistance = ABS_VALUE(best->row - currentRow);
                    if (bestDistance == ABS_VALUE(distance)) {
                        if (distance < 0) {
                            bestIndex = i;
                            best = entry;
                        }
                    } else if (ABS_VALUE(distance) < bestDistance) {
                        bestIndex = i;
                        best = entry;
                    }
                }
            }
            i++;
        } while (i < table->count);
    }
    return bestIndex;

}
