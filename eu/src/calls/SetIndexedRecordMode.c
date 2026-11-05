#include "src/indexed_records/IndexedRecordState.h"

void SetIndexedRecordMode(IndexedRecordStateView *records, int index, int mode)
{
    if (index < 0) {
        return;
    }
    records[index].mode = mode & 3;
}
