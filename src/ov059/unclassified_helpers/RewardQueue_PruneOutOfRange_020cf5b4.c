#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct RewardEntry {
    u32 id;
    int type;
} RewardEntry;

typedef struct RewardQueue {
    u8 pad_000[0x60];
    RewardEntry entries[16];
    fx32 timers[8];
    fx32 fades[8];
    u8 count;
    u8 capacity;
} RewardQueue;

extern BOOL IsTargetInVerticalRange_020cf100(RewardEntry *entry);
extern void func_01ff8710(void *src, void *dest, u32 size);

void RewardQueue_PruneOutOfRange_020cf5b4(RewardQueue *queue) {
    u8 i;

    for (i = 0; i < queue->count; i++) {
        if (!IsTargetInVerticalRange_020cf100(&queue->entries[i])) {
            u8 remaining = queue->count - 1 - i;
            if (remaining != 0) {
                func_01ff8710(&queue->entries[i + 1], &queue->entries[i], remaining * sizeof(RewardEntry));
            }
            queue->count--;
            i--;
        } else if (queue->fades[i] < 0x5000) {
            queue->fades[i] += 0x1000;
        }
    }
}
