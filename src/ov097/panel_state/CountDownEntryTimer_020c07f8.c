#include "nitro/types.h"

typedef struct {
    int handle;
    int step;
    u8 pad_08[4];
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

BOOL CountDownEntryTimer_020c07f8(int index, TimedEntryOwner *owner)
{
    TimedEntry *entry = &owner->entries[index];
    int remaining;

    if (entry->timer == 0) {
        return FALSE;
    }
    remaining = entry->timer - entry->step;
    if (entry->velocity < 0) {
        entry->active = 0;
    }
    if (remaining < 0) {
        entry->timer = 0;
    } else {
        entry->timer = remaining;
    }
    func_ov097_020c08b4(entry->handle, owner);
    return TRUE;
}
