#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    s8 slotId;
    u8 pad_03[0x2d];
    u16 animChannel;
    s16 animDelay;
    u8 pad_34[0x120];
} SlotEntry;

typedef struct {
    u8 pad_00[8];
    SlotEntry *entries;
    u8 pad_0C[9];
    u8 entryCount;
} SlotGroup;

typedef struct {
    u8 pad_00[0x84];
    SlotGroup *group;
} SlotOwner;

extern void func_ov021_020aafc4(SlotGroup *group, int arg);
extern int Anim_GetFrame_0202f4a0(u16 *channel, int index);
extern void func_ov021_020ab2f0(SlotEntry *entry, int mode);

void UpdateSlotGroupEntries_020d3f1c(int unused, SlotOwner *owner, int arg)
{
    SlotGroup *group = owner->group;
    SlotEntry *entry;
    int index;

    func_ov021_020aafc4(group, arg);
    for (index = 0; index < group->entryCount; index++) {
        entry = &group->entries[index];
        if (entry->slotId != -1 && entry->animDelay == 0
            && Anim_GetFrame_0202f4a0(&entry->animChannel, (u16)index) == 0) {
            func_ov021_020ab2f0(entry, 1);
        }
    }
}
