#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageWalker {
    u8 pad_000[0x28c];
    u16 cellIndex : 11;
    u16 entryGroup : 3;
    u16 extra : 2;
    u8 pad_28E[0x32];
    VecFx32 position;
} StageWalker;

extern u16 FindNearestStageEntry_02099328(const VecFx32 *target);
extern void SyncStageEntryPosition_02098fbc(u32 id, VecFx32 *outPosition);

void SyncNearestEntryPosition_0208f6bc(StageWalker *walker, int unused, VecFx32 *outPosition)
{
    if (FindNearestStageEntry_02099328(&walker->position) != 0) {
        SyncStageEntryPosition_02098fbc(walker->entryGroup, outPosition);
    }
}
