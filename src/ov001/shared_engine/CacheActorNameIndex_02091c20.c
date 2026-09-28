#include "nitro/types.h"

extern u16 func_ov001_02091248(void *actor, const char *name);

void CacheActorNameIndex_02091c20(u8 *actor, const char *name)
{
    *(u16 *)(actor + 0x33a) = func_ov001_02091248(actor, name);
}
