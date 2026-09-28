#include "nitro/types.h"

typedef struct {
    void *queueHead;
    void *queueTail;
    void *owner;
    u32 tagAndCount;
} SyncObject;

void InitSyncObject_02003134(SyncObject *obj)
{
    u32 tag = obj->tagAndCount & 0xff000000;
    obj->queueTail = NULL;
    obj->queueHead = NULL;
    obj->owner = NULL;
    obj->tagAndCount = tag & 0xffffff;
}
