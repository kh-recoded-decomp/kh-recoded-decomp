#include "nitro/types.h"

typedef struct Record Record;

typedef struct StatusRecordHolder {
    u8 pad_000[0x144];
    Record *record;
} StatusRecordHolder;

extern void ReleaseResourceWithBuffers_0205206c(Record **handle, int heapTag);
extern Record *CloneRecord_02051fc8(Record **out, u32 id, int useTailAlloc, int heapTag);

void ReloadStatusRecord_020c29d8(StatusRecordHolder *holder, u32 id)
{
    if (holder->record != NULL) {
        ReleaseResourceWithBuffers_0205206c(&holder->record, 0xe);
    }
    CloneRecord_02051fc8(&holder->record, id, 1, 0xe);
}
