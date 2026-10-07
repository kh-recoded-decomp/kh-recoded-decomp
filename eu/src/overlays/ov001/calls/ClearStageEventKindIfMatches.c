#include "src/overlays/ov001/StageEventCommand.h"

extern void func_ov001_02095904(StageEventCommand *command, u32 kind);

void ClearStageEventKindIfMatches(StageEventCommand *command, u32 kind)
{
    if (command->kind == kind) {
        func_ov001_02095904(command, 0);
    }
}
