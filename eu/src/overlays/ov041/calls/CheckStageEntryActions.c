#include "nitro/types.h"
#include "src/overlays/ov041/StageEntryRender.h"

extern BOOL func_ov041_020c2cac(StageEntry *entry);

/* Runs func_ov041_020c2cac (a check over its actions) on the entry at an index. */
BOOL CheckStageEntryActions(u8 entryIndex)
{
    return func_ov041_020c2cac(&gMovieContextState->stageWork->entries[entryIndex]);
}
