#include "src/indexed_records/IndexedRecordState.h"

int IndexedRecord_SetActive(IndexedRecordStateView *records, int index)
{
    if (index < 0) {
        return (int)(u32)records;
    }
    return (int)(records[index].flags |= 2);
}
