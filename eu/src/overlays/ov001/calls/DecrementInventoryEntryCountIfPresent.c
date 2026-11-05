#include "nitro/types.h"

extern u32 DecrementByteCounter();
extern u32 GetScriptInventoryEntryCount();

void DecrementInventoryEntryCountIfPresent(u16 *value) {
    s32 result = GetScriptInventoryEntryCount(*value);
    if (result != 0) {
        DecrementByteCounter(*value);
    }
}
