#include "nitro/types.h"

extern void *GetFieldObjectClassAtIndex(void);
extern u32 GetStridedBufferEntry(void *node, u32 param2);

u32 GetFieldObjectByClassAndIndex(u32 param1, u32 param2)
{
    void *node;

    node = GetFieldObjectClassAtIndex();
    if (node != 0) {
        return GetStridedBufferEntry(node, param2);
    }
    return 0;
}
