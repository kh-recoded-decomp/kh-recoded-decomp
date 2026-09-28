#include "nitro/types.h"

extern void func_01ff9e0c(u32 value, void *dest, void *src);

/* Updates a field in place */
void func_ov052_020ccf80(int entity, u32 value)
{
    func_01ff9e0c(value, (void *)(entity + 0x9c8), (void *)(entity + 0x9c8));
}
