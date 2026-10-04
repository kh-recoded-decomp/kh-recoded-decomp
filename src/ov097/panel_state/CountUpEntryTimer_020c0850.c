#include "nitro/types.h"

typedef struct {
    int handle;
    int step;
    int limit;
    int velocity;
    u8 pad_10[0x1c];
    int timer;
    int active;
    u8 pad_34[0x18];
} TimedEntry;

typedef struct {
    u8 pad_000[0x180];
    TimedEntry entries[1];
} TimedEntryOwner;

extern void func_ov097_020c08b4(int handle, TimedEntryOwner *owner);

BOOL CountUpEntryTimer_020c0850(int index, TimedEntryOwner *owner)
{
    TimedEntry *entry = &owner->entries[index];
    int timer = entry->timer;

    if (timer == entry->limit - entry->step) {
        return FALSE;
    }
    timer += entry->step;
    if (entry->velocity < 0) {
        entry->active = entry->step - 1;
    }
    if (timer > entry->limit - entry->step) {
        entry->timer = entry->limit - entry->step;
    } else {
        entry->timer = timer;
    }
    func_ov097_020c08b4(entry->handle, owner);
    return TRUE;
}
