#include "nitro/types.h"

typedef struct RecordPool RecordPool;
typedef struct Record Record;

extern Record *FindActiveRecordById_020b8184(RecordPool *pool, u32 recordId);
extern void TagTracker_InvokeCallback_020b8210(RecordPool *pool, Record *record);

void InvokeCallbackForRecordId_020bf0c4(RecordPool *pool, u32 recordId)
{
    Record *record = FindActiveRecordById_020b8184(pool, (u16)recordId);
    TagTracker_InvokeCallback_020b8210(pool, record);
}
