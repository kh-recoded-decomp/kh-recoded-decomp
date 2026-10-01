#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[0x52];
    u8 kind;
} Actor;

extern BOOL IsDestroyed_020a31f8(Actor *self);
extern Actor *FindFirstLiveLink_020a2128(Actor *actor);
extern Actor *FindLiveNextLink_020a20e0(Actor *actor);

BOOL IsLeadLink_020a2168(Actor *self)
{
    Actor *entry;
    Actor *lead;
    BOOL found;

    if (!IsDestroyed_020a31f8(self)) {
        entry = FindFirstLiveLink_020a2128(self);
        lead = entry;
        found = FALSE;
        while (entry != NULL) {
            u8 kind = entry->kind;
            if (kind == 1 || kind == 10) {
                lead = entry;
                break;
            }
            if (!found && kind != 2) {
                found = TRUE;
                lead = entry;
            }
            entry = FindLiveNextLink_020a20e0(entry);
        }
        if (lead == self) {
            return TRUE;
        }
    }
    return FALSE;
}
