#include "nitro/types.h"

typedef struct {
    int id;
    u8 pad4[0x3c];
    s16 level;
} Member;

typedef struct {
    Member **members;
} MemberList;

extern int data_ov052_020d20c0[];
extern int FindMemberIndexById_020ad894(MemberList *list, int id);
extern int GetConsumableSlotUses_020504b4(int index);
extern void func_ov052_020d0ec0(int entity, int level, int id, int index, int flag);

void UseFirstAvailableMember_020cc8bc(int entity)
{
    int i;
    for (i = 0; i < 2; i++) {
        int index = FindMemberIndexById_020ad894((MemberList *)(entity + 0x1070), data_ov052_020d20c0[i]);
        if (index != -1 && GetConsumableSlotUses_020504b4(index) != 0) {
            Member *member = (*(Member ***)(entity + 0x1070))[index];
            func_ov052_020d0ec0(entity, member->level, member->id, index, 0);
            return;
        }
    }
}
