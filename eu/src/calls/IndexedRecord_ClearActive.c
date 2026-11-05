#include "src/indexed_records/IndexedRecordState.h"

void IndexedRecord_ClearActive(IndexedRecordStateView *records, int index)
{
    if (index < 0) {
        return;
    }
    records[index].flags &= ~(u32)2;
}
