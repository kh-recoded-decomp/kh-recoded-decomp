#include "nitro/types.h"

typedef struct StageEventCommand {
    u8 pad_00[0xc];
    u8 kind;
} StageEventCommand;

extern void func_ov001_020958dc(StageEventCommand *command, u32 kind);

void ClearStageEventKindIfMatches_020958e4(StageEventCommand *command, u32 kind)
{
    if (command->kind == kind) {
        func_ov001_020958dc(command, 0);
    }
}
