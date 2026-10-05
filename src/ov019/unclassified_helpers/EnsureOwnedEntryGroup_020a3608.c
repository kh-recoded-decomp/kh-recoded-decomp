#include "nitro/types.h"

typedef struct EntryGroupDesc {
    const void *resource;
    s32 slotCount;
    s32 mode;
    BOOL fixedSlots;
    u32 reserved;
} EntryGroupDesc;

typedef struct Actor {
    u8 pad_00[0x64];
    s16 groupId;
} Actor;

extern const u8 data_ov019_020a3690[];
void ZeroBytes0x14_020a8adc(void *obj);
int func_ov021_020a89a8(EntryGroupDesc *desc);

void EnsureOwnedEntryGroup_020a3608(Actor *self)
{
    EntryGroupDesc desc;
    if (self->groupId == -1) {
        ZeroBytes0x14_020a8adc(&desc);
        desc.slotCount = 1;
        desc.mode = 1;
        desc.fixedSlots = FALSE;
        desc.resource = data_ov019_020a3690;
        self->groupId = func_ov021_020a89a8(&desc);
    }
}
