#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageCategoryOwner {
    u8 category;
} StageCategoryOwner;

#include "src/overlays/ov041/StageResources.h"

extern StageResourceItem *SpawnStageResourceItem(int category, u8 index, u8 animation, const VecFx32 *position,
                                                 BOOL persistent);

/* Spawns an item of the given category (the owner's own category when it is 0) and returns it. */
StageResourceItem *SpawnStageItem(StageCategoryOwner *owner, int category, u8 index, u8 animation,
                                  const VecFx32 *position, BOOL persistent)
{
    if (category == 0) {
        category = owner->category;
    }
    return SpawnStageResourceItem(category, index, animation, position, persistent);
}
