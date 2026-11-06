#include "nitro/types.h"

typedef struct OverlayFactoryContext {
    u8 pad_000[0xe8];
    u32 unk_0e8;
} OverlayFactoryContext;

extern OverlayFactoryContext *gManagedActorGlobals;

u32 GetPendingWorldEntryData(void)
{
    if (gManagedActorGlobals == 0) {
        return 0;
    }
    return gManagedActorGlobals->unk_0e8;
}
