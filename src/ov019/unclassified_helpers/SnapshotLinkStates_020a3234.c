#include "nitro/types.h"

typedef struct LinkSnapshot {
    u32 linkValue;
    u32 groupId;
    u16 flags;
    u8 state;
    u8 pad_0b;
} LinkSnapshot;

typedef struct Actor {
    u8 pad_00[0x3c];
    u32 linkValue;
    u8 pad_40[0x4f - 0x40];
    u8 state : 3;
    u8 stateHigh : 5;
    u8 pad_50[0x5a - 0x50];
    u16 flags;
    u8 pad_5c[0x64 - 0x5c];
    u32 groupId;
} Actor;

typedef struct LinkOwner {
    u8 pad_00[0x3e];
    u16 linkCount;
} LinkOwner;

LinkSnapshot *AllocEffectBufferSlot_020872f0(LinkOwner *owner, u32 size);
Actor *func_ov001_0208635c(LinkOwner *owner, int index);

void SnapshotLinkStates_020a3234(LinkOwner *owner)
{
    LinkSnapshot *snapshots = AllocEffectBufferSlot_020872f0(owner, owner->linkCount * sizeof(LinkSnapshot));
    int i;
    for (i = 0; i < owner->linkCount; i++) {
        LinkSnapshot *snapshot = &snapshots[i];
        Actor *link = func_ov001_0208635c(owner, i);
        snapshots[i].linkValue = link->linkValue;
        snapshot->flags = link->flags;
        snapshot->state = link->state;
        snapshot->groupId = link->groupId;
    }
}
