#include "nitro/types.h"

typedef struct PartyMember {
    u8 pad_0000[0x1f8];
    void (*onReset)(struct PartyMember *member, int a, int b);
    u8 pad_01fc[0x75c - 0x1fc];
    void *controller;
    u8 pad_0760[0x9ac - 0x760];
    u64 stateFlags;
    u8 pad_09b4[0x10ec - 0x9b4];
    void (*setActive)(struct PartyMember *member, BOOL active);
} PartyMember;

extern PartyMember *GetBoundedEntryField_0206db5c(int index);
extern void func_ov058_020d6a78(PartyMember *member);

BOOL RefreshPartyMemberStates_0208ee80(void)
{
    int i;

    for (i = 1; i < 3; i++) {
        PartyMember *member = GetBoundedEntryField_0206db5c(i);
        if (member != NULL) {
            func_ov058_020d6a78(member);
            if ((member->stateFlags & 0x800) == 0 && member->controller != NULL) {
                if (member->onReset != NULL) {
                    member->onReset(member, 0, 0);
                }
                member->setActive(member, TRUE);
            }
        }
    }
    return TRUE;
}
