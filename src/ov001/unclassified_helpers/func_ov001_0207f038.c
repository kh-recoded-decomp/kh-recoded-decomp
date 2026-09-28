#include "nitro/types.h"

extern void *func_ov001_0207f028(void);
extern u32 func_ov001_0207f4b4(void *node, u32 param2);

u32 func_ov001_0207f038(u32 param1, u32 param2)
{
    void *node;

    node = func_ov001_0207f028();
    if (node != 0) {
        return func_ov001_0207f4b4(node, param2);
    }
    return 0;
}
