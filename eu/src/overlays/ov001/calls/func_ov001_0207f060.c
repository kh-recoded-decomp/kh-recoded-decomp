#include "nitro/types.h"

extern void *func_ov001_0207f050(void);
extern u32 GetStridedBufferEntry(void *node, u32 param2);

u32 func_ov001_0207f060(u32 param1, u32 param2)
{
    void *node;

    node = func_ov001_0207f050();
    if (node != 0) {
        return GetStridedBufferEntry(node, param2);
    }
    return 0;
}
