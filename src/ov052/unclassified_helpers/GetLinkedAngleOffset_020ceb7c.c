#include "nitro/types.h"

u16 GetLinkedAngleOffset_020ceb7c(int entity)
{
    return *(u16 *)(*(int *)(entity + 0x230) + 0x80) - 0x8000;
}
