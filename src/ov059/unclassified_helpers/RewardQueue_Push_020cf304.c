#include "nitro/types.h"

typedef struct RewardEntry {
    union {
        u32 kind;
        u16 eventId;
    } id;
    int type;
} RewardEntry;

typedef struct RewardQueue {
    u8 pad_000[0x60];
    RewardEntry entries[16];
    u32 timers[8];
    u32 flags[8];
    u8 count;
    u8 capacity;
    u8 pad_122[2];
    int uniqueCount;
} RewardQueue;

extern int func_ov059_020cf404(RewardQueue *queue, RewardEntry *entry);
extern u32 func_ov031_020bc710(u32 eventId);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void PlaySoundChecked_0204d8d0(int seqArcNo, int index);

void RewardQueue_Push_020cf304(RewardQueue *queue, RewardEntry *entry) {
    if (queue->count == 0) {
        queue->uniqueCount = 1;
    } else if (func_ov059_020cf404(queue, entry) == -1) {
        queue->uniqueCount++;
    }
    queue->entries[queue->count] = *entry;
    queue->timers[queue->count] = 0;
    queue->flags[queue->count] = 0;
    queue->count++;
    if (entry->type == 2) {
        func_ov031_020bc710(entry->id.eventId);
    }
    PlaySoundEffect_0204d924(0x19d, 4);
    if (queue->count == queue->capacity) {
        PlaySoundChecked_0204d8d0(0x19d, 5);
    }
}
