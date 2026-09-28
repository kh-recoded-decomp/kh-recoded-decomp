#include "nitro/types.h"

extern u32 g_manager_020a049c;

/* Bounds-checked indexed lookup into manager records */
u32 GetBoundedEntryField_0206db5c(int index)
{
    if (index >= *(int *)(g_manager_020a049c + 0x7c)) {
        return 0;
    }
    return *(u32 *)(g_manager_020a049c + index * 0x28 + 8);
}
