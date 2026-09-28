#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    void *currentThread;
} ThreadInfo_02056b6c;

typedef struct {
    u8 pad_00[8];
    void *owner;
    u32 tagAndCount;
} OSMutex;

extern ThreadInfo_02056b6c data_02056b6c;
extern int func_02004938(void);
extern void func_0200494c(int state);
extern void OSi_EnqueueTail(void *list, void *node);

int TryLockSyncObject_02003200(OSMutex *mutex)
{
    int state = func_02004938();
    void *currentThread = data_02056b6c.currentThread;
    int result;
    u32 combined;
    u32 incremented;
    u32 tag2;
    u32 count2;

    if (mutex->owner == NULL) {
        combined = (mutex->tagAndCount & 0xffffff) | 0x10000000;
        incremented = combined + 1;
        tag2 = combined & 0xff000000;
        count2 = incremented & 0xffffff;
        mutex->owner = currentThread;
        mutex->tagAndCount = tag2 | count2;
        OSi_EnqueueTail(currentThread, mutex);
        result = 1;
    } else if (mutex->owner == currentThread) {
        result = 1;
        mutex->tagAndCount = (mutex->tagAndCount & 0xff000000) | ((mutex->tagAndCount + 1) & 0xffffff);
    } else {
        result = 0;
    }
    func_0200494c(state);
    return result;
}
