#include "nitro/types.h"

typedef struct ScriptCommand {
    u8 pad_00[0xc];
    u8 type;
    u8 pad_0d[3];
    s16 groupId;
    u16 targetId;
} ScriptCommand;

typedef struct ScriptRunner {
    u16 targetKind;
    u16 targetId;
} ScriptRunner;

typedef struct GroupMember {
    u8 pad_000[0x1d0];
    ScriptRunner runner;
    u8 pad_1d4[0x28a - 0x1d4];
    u16 unk_28A_0 : 9;
    u16 scriptRunning : 1;
    u16 unk_28A_10 : 6;
} GroupMember;

extern GroupMember *func_ov001_0209c040(s16 groupId);
extern void *GetStageObjectHandle_0209c0c4(u32 id);
extern int func_ov021_020b4bdc(ScriptRunner *runner, int slot);

int RunLeaderScriptSlotCommand_0209387c(ScriptCommand *command)
{
    GroupMember *leader = func_ov001_0209c040(command->groupId);

    GetStageObjectHandle_0209c0c4(command->targetId);
    leader->scriptRunning = 1;
    if (func_ov021_020b4bdc(&leader->runner, 5) != 4) {
        return 0;
    }
    if (command->type == 8) {
        leader->scriptRunning = 0;
        return 0;
    }
    leader->scriptRunning = 0;
    return 3;
}
