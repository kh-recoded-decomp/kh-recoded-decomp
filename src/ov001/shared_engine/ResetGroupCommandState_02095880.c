#include "nitro/types.h"

typedef struct GroupCommand {
    s32 state;
    u16 resetPending : 1;
    u16 unk_04_1 : 15;
    u8 pad_06[0x10 - 0x06];
    u16 groupId;
} GroupCommand;

extern void *data_ov001_0209e464[];
extern void *func_ov001_0209c040(s16 groupId);
extern void func_ov001_020958dc(GroupCommand *command, int mode);
extern void func_ov001_02090f00(void *leader);
extern void func_ov001_020925bc(GroupCommand *command, s32 state);

void ResetGroupCommandState_02095880(GroupCommand *command)
{
    void *leader;

    if (command->resetPending && command->groupId != 0) {
        leader = func_ov001_0209c040((s16)command->groupId);
        if (command->state >= 12 || data_ov001_0209e464[command->state] != NULL) {
            func_ov001_020958dc(command, 0);
            func_ov001_02090f00(leader);
            func_ov001_020925bc(command, 6);
            command->resetPending = 0;
        }
    }
}
