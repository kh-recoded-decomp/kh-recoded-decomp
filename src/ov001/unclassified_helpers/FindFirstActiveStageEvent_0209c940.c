#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xe];
    u16 kind;
    u16 active;
    u8 pad_12[0x1c8 - 0x12];
} StageEvent;

typedef struct {
    u8 pad_00[0x210];
    StageEvent *events;
    u8 pad_214[0x18dee - 0x214];
    u16 eventCount;
} StageManager;

extern StageManager *g_stageManager_020a0508;

u16 FindFirstActiveStageEvent_0209c940(void)
{
    u16 index;
    StageEvent *event;

    for (index = 0; index < g_stageManager_020a0508->eventCount; index++) {
        event = &g_stageManager_020a0508->events[index];
        if (event->active != 0) {
            return index + 1;
        }
        if (event->kind == 99) {
            return index + 1;
        }
    }
    return 0;
}
