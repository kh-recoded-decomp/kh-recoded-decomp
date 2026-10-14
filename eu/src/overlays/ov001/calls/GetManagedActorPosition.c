#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 reserved00[0xbc];
    VecFx32 position;
} ManagedActorRecord;

extern u32 GetBoundedEntryField(int index);

VecFx32 *GetManagedActorPosition(int index)
{
    ManagedActorRecord *actor = (ManagedActorRecord *)GetBoundedEntryField(index);

    if (actor != NULL) {
        return &actor->position;
    }
    return NULL;
}
