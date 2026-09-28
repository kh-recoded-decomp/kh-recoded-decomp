#include "nitro/types.h"

extern void ReleaseResourceAndDetach_0202eee8(u8 *object);

void ReleaseNestedObjectAt0x30_020aaac8(u8 *obj)
{
    ReleaseResourceAndDetach_0202eee8(obj + 0x30);
}
