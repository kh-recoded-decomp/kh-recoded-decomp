#include "nitro/types.h"

typedef struct {
    s8 active;
    u8 pad_01[3];
    u16 flags;
    u8 pad_06[0x106];
    s32 target;
    u8 pad_110[0x28];
} GroupSlot;

typedef struct {
    GroupSlot *slots;
    s32 slotCount;
    s16 groupId;
} EntryGroup;

extern EntryGroup *FindEntryGroupById_020a8810(int groupId);

void SetGroupSlotTarget_020a8ea8(int groupId, int index, s32 target)
{
    EntryGroup *group = FindEntryGroupById_020a8810(groupId);
    GroupSlot *slot;

    if (group == NULL) {
        return;
    }
    slot = &group->slots[index];
    if (slot->active == 0) {
        return;
    }
    if (target >= 0) {
        slot->target = target;
        slot->flags |= 0x100;
    } else {
        slot->flags &= ~0x100;
    }
}
