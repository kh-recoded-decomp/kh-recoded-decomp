/* Shared implementation for the two identical EU list navigators. */
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
