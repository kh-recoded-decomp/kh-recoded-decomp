#include "nitro/types.h"

typedef struct PartyState {
    u8 pad_00[0xb6];
    s16 groupId;
} PartyState;

typedef struct PartyMember {
    u8 pad_00[0x10];
    int memberIndex;
} PartyMember;

extern PartyState *data_ov001_020a049c;
extern u32 IsGroupMemberActive_020a8d1c(u32 groupId, int index);

void DropInactiveGroupMember_0206d02c(PartyMember *member)
{
    PartyState *party = data_ov001_020a049c;

    if (member->memberIndex >= 0 && !IsGroupMemberActive_020a8d1c(party->groupId, member->memberIndex)) {
        member->memberIndex = -1;
    }
}
