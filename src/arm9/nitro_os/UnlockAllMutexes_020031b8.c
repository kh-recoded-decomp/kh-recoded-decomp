#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x88];
    void *mutexQueue;
} OSThread;

typedef struct {
    u8 pad_00[8];
    u32 owner;
    vu32 tagAndCount;
} OSMutex;

extern void *OSi_RemoveMutexLinkFromQueue(void **queue);
extern void OS_WakeupThread_02002af8(void *queue);

void UnlockAllMutexes_020031b8(OSThread *thread)
{
    OSMutex *mutex;
    u32 tag;

    if (thread->mutexQueue == NULL) {
        return;
    }
    do {
        mutex = OSi_RemoveMutexLinkFromQueue(&thread->mutexQueue);
        tag = mutex->tagAndCount & 0xff000000;
        mutex->owner = 0;
        mutex->tagAndCount = tag & 0xffffff;
        OS_WakeupThread_02002af8(mutex);
    } while (thread->mutexQueue != NULL);
}
