#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PlayerEntry PlayerEntry;

struct PlayerEntry {
    u8 pad_000[0x214];
    void (*applyVelocity)(PlayerEntry *entry, VecFx32 *velocity);
};

typedef struct {
    u8 pad_00[0x6c];
    VecFx32 velocity;
} LaunchSource;

extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern PlayerEntry *GetBoundedEntryField_0206db5c(int index);

BOOL ApplyScaledVelocityToPlayer_020a10c4(void *unused, void *unused2, LaunchSource *source)
{
    VecFx32 velocity;
    VecFx32 scaled = source->velocity;
    PlayerEntry *entry;

    ScaleVecFx32InPlace_0204a5e4(&scaled, 0x385);
    velocity = scaled;
    entry = GetBoundedEntryField_0206db5c(0);
    if (entry->applyVelocity != NULL) {
        entry->applyVelocity(entry, &velocity);
    }
    return FALSE;
}
