#include "src/overlays/ov001/StageEventCommand.h"

extern void SetStageEventKindWrapper(StageEventCommand *command, u32 kind);

void ClearStageEventKindIfMatches(StageEventCommand *command, u32 kind)
{
    if (command->kind == kind) {
        SetStageEventKindWrapper(command, 0);
    }
}
