#ifndef EU_FILE_LOADER_STATE_H
#define EU_FILE_LOADER_STATE_H

#include "nitro/types.h"

typedef struct FileLoaderThreadQueue {
    void *head;
    void *tail;
} FileLoaderThreadQueue;

/* DS message-queue layout, also read by IsRecordIdFree. OS_InitMessageQueue
 * initializes both wait queues and the table/capacity/head/count words.
 * Index/count fields retain the unsigned view used by that existing query.
 */
typedef struct FileLoaderMessageQueue {
    FileLoaderThreadQueue senders;
    FileLoaderThreadQueue receivers;
    void **table;
    u32 capacity;
    u32 head;
    u32 count;
} FileLoaderMessageQueue;

typedef char FileLoaderThreadQueueSizeCheck[sizeof(FileLoaderThreadQueue) == 8 ? 1 : -1];
typedef char FileLoaderMessageQueueSizeCheck[sizeof(FileLoaderMessageQueue) == 32 ? 1 : -1];

extern FileLoaderMessageQueue gFileLoaderMessageQueue;
extern void *gFileLoaderMessages[64];
/* Keep the original 192 bytes of 32-bit word storage; no OSThread fields inferred. */
extern u32 gFileLoaderThreadStorage[48];

/* May sleep once, then returns 1. This is not a returned completion predicate. */
int SleepIfFileLoaderBusy(void);

#endif
