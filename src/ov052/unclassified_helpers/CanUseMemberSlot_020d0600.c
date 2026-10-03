#include "nitro/types.h"

typedef struct {
    u8 pad0[0x3d];
    s8 kind;
} MemberInfo;

typedef struct {
    u8 pad0[0x50];
    MemberInfo *info;
} Member;

extern unsigned int GetMemberValue_020ad878(int *container, int index);
extern Member *GetMemberByIndex_020adaac(int *container, int index);
extern BOOL IsCountBelowLimit_020ae728(MemberInfo *counter);

BOOL CanUseMemberSlot_020d0600(int entity, int index)
{
    BOOL result = TRUE;
    Member *member;
    switch (GetMemberValue_020ad878((int *)(entity + 0x1070), index)) {
    case 1:
        if (*(int *)(entity + 0x1078) != 0) {
            result = FALSE;
        }
        break;
    case 2:
        member = GetMemberByIndex_020adaac((int *)(entity + 0x1070), index);
        result = IsCountBelowLimit_020ae728(member->info);
        if (result && member->info->kind == 3 && *(int *)(entity + 0x1078) != 0) {
            result = FALSE;
        }
        break;
    case 4:
        if (*(int *)(entity + 0x1078) != 0 && *(int *)(*(int *)(entity + 0x1078) + 4) == 4) {
            result = FALSE;
        }
        break;
    }
    return result;
}
