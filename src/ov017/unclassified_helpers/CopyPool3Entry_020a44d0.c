#include "nitro/types.h"

typedef struct PoolEntry {
    u32 words[3];
} PoolEntry;

extern PoolEntry *GetPool3Entry_020a41e4(void *owner, int index);

void CopyPool3Entry_020a44d0(PoolEntry *dest, void *owner, int index)
{
    *dest = *GetPool3Entry_020a41e4(owner, index);
}
