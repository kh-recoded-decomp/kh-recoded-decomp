#include "nitro/types.h"

extern void VEC_Add(u32 value, void *dest, void *src);

/* Updates a field in place */
void func_ov052_020ccfa0(int entity, u32 value)
{
    VEC_Add(value, (void *)(entity + 0x9c8), (void *)(entity + 0x9c8));
}
