#include "nitro/types.h"

extern u32 GetBoundedEntryField();
extern u32 SetActorHealthClamped();

void RestorePrimaryActorHealth(void) {
    s32 entry = GetBoundedEntryField(0);
    SetActorHealthClamped(entry, *(u16 *)(*(s32 *)(entry + 0x1d4) + 4));
}
