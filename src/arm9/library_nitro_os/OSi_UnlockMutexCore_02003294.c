#include "nitro/types.h"

typedef int OSIntrMode;
typedef struct OSThread OSThread;

typedef struct {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

typedef struct OSMutex {
    OSThreadQueue queue;
    OSThread *thread;
    s32 count;
    struct OSMutex *prev;
    struct OSMutex *next;
} OSMutex;

typedef struct {
    u16 isNeedRescheduling;
    u16 irqDepth;
    OSThread *current;
} OSThreadInfo;

#define OS_MUTEX_TYPE_NONE 0x00000000
#define OS_MUTEX_TYPE_STD 0x10000000
#define OS_MUTEX_TYPE_R 0x20000000
#define OS_MUTEX_TYPE_W 0x30000000
#define OSi_MUTEX_TYPE_MASK 0xff000000
#define OSi_MUTEX_COUNT_MASK 0x00ffffff

extern OSThreadInfo data_02056b6c;
extern OSIntrMode OS_DisableInterrupts_02004938(void);
extern OSIntrMode OS_RestoreInterrupts_0200494c(OSIntrMode state);
extern void OSi_DequeueItem_02003390(OSThread *thread, OSMutex *mutex);
extern void OS_WakeupThread_02002af8(OSThreadQueue *queue);

static inline u32 OSi_GetMutexType(OSMutex *mutex)
{
    return (u32)mutex->count & OSi_MUTEX_TYPE_MASK;
}

static inline u32 OSi_GetMutexCount(OSMutex *mutex)
{
    return (u32)mutex->count & OSi_MUTEX_COUNT_MASK;
}

static inline void OSi_DecreaseMutexCount(OSMutex *mutex)
{
    u32 type = OSi_GetMutexType(mutex);

    mutex->count--;
    mutex->count = (s32)(type | OSi_GetMutexCount(mutex));
}

static inline void OSi_SetMutexType(OSMutex *mutex, u32 type)
{
    mutex->count = (s32)(type | OSi_GetMutexCount(mutex));
}

void OSi_UnlockMutexCore_02003294(OSMutex *mutex, u32 type)
{
    OSIntrMode enabled = OS_DisableInterrupts_02004938();
    BOOL unlock = FALSE;
    OSThread *current = data_02056b6c.current;

    if (type != OS_MUTEX_TYPE_NONE && type != OSi_GetMutexType(mutex)) {
        (void)OS_RestoreInterrupts_0200494c(enabled);
        return;
    }

    switch (OSi_GetMutexType(mutex)) {
    case OS_MUTEX_TYPE_STD:
    case OS_MUTEX_TYPE_W:
        if (mutex->thread == current) {
            OSi_DecreaseMutexCount(mutex);
            if (OSi_GetMutexCount(mutex) == 0) {
                unlock = TRUE;
            }
        }
        break;
    case OS_MUTEX_TYPE_R:
        OSi_DecreaseMutexCount(mutex);
        if (OSi_GetMutexCount(mutex) == 0) {
            unlock = TRUE;
        }
        break;
    default:
        (void)OS_RestoreInterrupts_0200494c(enabled);
        return;
    }

    if (unlock) {
        OSi_DequeueItem_02003390(current, mutex);
        mutex->thread = NULL;
        OSi_SetMutexType(mutex, OS_MUTEX_TYPE_NONE);
        OS_WakeupThread_02002af8(&mutex->queue);
    }

    (void)OS_RestoreInterrupts_0200494c(enabled);
}
