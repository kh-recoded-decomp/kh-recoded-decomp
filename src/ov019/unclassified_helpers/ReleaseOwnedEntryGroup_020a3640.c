#include "nitro/types.h"

typedef struct Actor {
    u8 pad_00[0x64];
    s16 groupId;
} Actor;

void func_ov021_020a8a68(int groupId);

void ReleaseOwnedEntryGroup_020a3640(Actor *self)
{
    if (self->groupId != -1) {
        func_ov021_020a8a68(self->groupId);
        self->groupId = -1;
    }
}
