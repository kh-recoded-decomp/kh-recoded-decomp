#include "nitro/types.h"

typedef struct MotionParams {
    u32 words[4];
} MotionParams;

typedef struct MotionEntry {
    void *actor;
    MotionParams params;
    int state;
    int active;
} MotionEntry;

typedef struct MotionQueue {
    MotionEntry entries[9];
    int count;
} MotionQueue;

typedef struct MotionActor {
    u8 pad_000[0x150];
    MotionQueue *queue;
} MotionActor;

typedef struct StageEvent {
    u8 pad_00[8];
    int type;
    u8 pad_0c[0x18 - 0xc];
    u16 recordId;
} StageEvent;

extern const MotionParams data_02055838;
extern void func_ov056_020d7728(void);
extern void StageRecord_SetCallback_02087d74(u32 id, void *callback, void *userData);

void QueueMotionOnStageEvent_020d7814(void *source, MotionActor *actor, StageEvent *event)
{
    if (event->type == 4) {
        MotionQueue *queue = actor->queue;
        int index = queue->count;
        if (index < 8) {
            MotionEntry *entry;
            queue->count++;
            entry = &queue->entries[index];
            entry->actor = actor;
            entry->params = data_02055838;
            entry->state = 0;
            entry->active = 1;
            StageRecord_SetCallback_02087d74(event->recordId, func_ov056_020d7728, entry);
        }
    }
}
