#include "nitro/types.h"

typedef struct PendingPair {
    int first;
    int second;
} PendingPair;

typedef struct PendingQueue {
    u8 pad_00[3];
    u8 count;
    u8 pad_04[0xc];
    PendingPair entries[1];
} PendingQueue;

extern PendingQueue *func_ov039_020bc630(void);

void PushPendingPair_020bf614(int first, int second)
{
    PendingQueue *queue = func_ov039_020bc630();

    queue->entries[queue->count].first = first;
    queue->entries[queue->count].second = second;
    queue->count++;
}