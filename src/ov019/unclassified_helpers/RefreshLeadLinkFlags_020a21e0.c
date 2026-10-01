#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[0x4f];
    u8 unkBits : 6;
    u8 isLead : 1;
    u8 unkBit7 : 1;
} Actor;

extern Actor *FindFirstLiveLink_020a2128(Actor *actor);
extern Actor *FindLiveNextLink_020a20e0(Actor *actor);
extern BOOL IsLeadLink_020a2168(Actor *self);

void RefreshLeadLinkFlags_020a21e0(Actor *actor)
{
    Actor *entry = FindFirstLiveLink_020a2128(actor);
    if (entry == NULL) {
        entry = FindLiveNextLink_020a20e0(actor);
    }
    if (entry == NULL) {
        return;
    }
    do {
        entry->isLead = IsLeadLink_020a2168(entry) ? TRUE : FALSE;
        entry = FindLiveNextLink_020a20e0(entry);
    } while (entry != NULL);
}
